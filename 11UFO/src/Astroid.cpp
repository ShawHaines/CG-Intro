#include "Astroid.h"
#include "geometry.h"

#include <GL/freeglut.h>
// in order to use M_PI
#define _USE_MATH_DEFINES
#include <math.h>


static double orbitWidth = 0.1;
static int slices = 50;
static double dt = 0.015;

// converts radians to degrees.
double degrees(double rad) { return rad * 180.0 / M_PI; }

Orbit::Orbit(double r, double nx, double ny, double nz)
    : radius(r), normal(nx, ny, nz) {
    normal.normalize();
    setColor(1.0, 1.0, 1.0, 1.0);
};

int Orbit::display() {
    // lazy way... note that the default Torus is given around the z axis.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glColor3dv(color);
    glutSolidTorus(orbitWidth, radius, slices, slices);
    glPopMatrix();
    return 0;
}

Astroid::Astroid(double r, double orbitR, double _period, double nx, double ny,
                 double nz)
    : radius(r), phi(0), period(_period), orbit(orbitR, nx, ny, nz), emission(false),texture(0){
    setColor(1.0, 0, 0, 1.0);
}

int Astroid::display() {
    // Assuming that the MODEL matrix has already been set to the center.
    glMatrixMode(GL_MODELVIEW);
    // get the plane by rotating according to a cross product.
    Vector upVector(0, -1, 0);
    auto axis = cross(upVector, orbit.normal);
    axis.normalize();
    glPushMatrix();
    if (!axis.isZero()) {
        double angle = degrees(acos(orbit.normal.dot(upVector)));
        glRotated(angle, axis.end[0], axis.end[1], axis.end[2]);
    }
    orbit.display();
    // the angle is defined in degrees...
    glRotated(degrees(phi), 0, -1, 0);
    glTranslated(orbit.radius, 0, 0);
    glColor3dv(color);
    if (emission){
        GLfloat oldEmission[4],newEmission[4];
        double rate=0.9;
        for (int i=0;i<4;i++) newEmission[i]=color[i]*rate;

        glGetMaterialfv(GL_FRONT,GL_EMISSION,oldEmission);
        glMaterialfv(GL_FRONT,GL_EMISSION,newEmission);
        if (texture>0){
            // bind texture.
            glEnable(GL_TEXTURE_2D);
            GLint oldTexture;
            glGetIntegerv(GL_TEXTURE_BINDING_2D,&oldTexture);
            glBindTexture(GL_TEXTURE_2D,texture);
            GLUquadric* sphere=gluNewQuadric();
            gluQuadricTexture(sphere,GLU_TRUE);
            gluSphere(sphere,radius,slices,slices);
            glBindTexture(GL_TEXTURE_2D,oldTexture);
            glDisable(GL_TEXTURE_2D);
        } else glutSolidSphere(radius,slices,slices);
        glMaterialfv(GL_FRONT,GL_EMISSION,oldEmission);
    } else{
        if (texture > 0) {
            // bind texture.
            glEnable(GL_TEXTURE_2D);
            GLint oldTexture;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture);
            glBindTexture(GL_TEXTURE_2D, texture);
            GLUquadric* sphere = gluNewQuadric();
            gluQuadricTexture(sphere, GLU_TRUE);
            gluSphere(sphere, radius, slices, slices);
            glBindTexture(GL_TEXTURE_2D, oldTexture);
            glDisable(GL_TEXTURE_2D);
        } else
            glutSolidSphere(radius, slices, slices);
    }
    for (auto i = satellites.begin(); i != satellites.end(); i++) {
        (*i)->display();
    }
    glPopMatrix();
    return 0;
}

int Astroid::revolution() {
    phi += 2 * M_PI * dt / period;
    if (phi > 2 * M_PI) phi -= (2 * M_PI);
    for (auto i = satellites.begin(); i != satellites.end(); i++) {
        (*i)->revolution();
    }
    return 0;
}

int Orbit::setColor(double r, double g, double b, double a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
    return 0;
}

int Astroid::setColor(double r, double g, double b, double a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
    return 0;
}
