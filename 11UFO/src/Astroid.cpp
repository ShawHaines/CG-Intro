#include "Astroid.h"
#include "geometry.h"

#include <GL/freeglut.h>
// in order to use M_PI
#define _USE_MATH_DEFINES
#include <math.h>


static double orbitWidth = 0.1;
static int slices = 50;
static double dt = 0.015;
extern GLdouble view[16];

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
    glMultMatrixd(view);
    glColor3dv(color);
    glutSolidTorus(orbitWidth, radius, slices, slices);
    glPopMatrix();
    return 0;
}

Astroid::Astroid(double r, double orbitR, double _period, double nx, double ny,
                 double nz)
    : radius(r), phi(0), period(_period), orbit(orbitR, nx, ny, nz) {
    setColor(1.0, 0, 0, 1.0);
}

int Astroid::display() {
    // Assuming that the MODEL matrix has already been set to the center of the orbit.
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
    // now our origin is in the center of the orbit, and the z axis is aligned with the normal of the orbit.
    orbit.display();
    // the angle is defined in degrees...
    glRotated(degrees(phi), 0, -1, 0);
    glTranslated(orbit.radius, 0, 0);
    glColor3dv(color);
    glPushMatrix();
    glMultMatrixd(view);
    glutSolidSphere(radius, slices, slices);
    glPopMatrix();
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
