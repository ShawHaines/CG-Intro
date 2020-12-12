#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include "GL/freeglut.h"
// #include "Astroid.h"
// #include "geometry.h"

/**
 * cylinder(), signature is all the same with
 * glutSolidCylinder( double radius, double height, GLint slices, GLint stacks);
 * */

void cylinder(double radius, double height, GLint slices, GLint stacks) {
    // TODO: Use Bresenham algorithm.
    glBegin(GL_QUAD_STRIP);
    GLdouble step = M_PI * 2 / slices, angle = 0;
    typedef GLdouble v2[2];
    v2* vertices = NULL;
    vertices = (v2*)calloc(slices,sizeof(GLdouble)*2);
    // up face
    glBegin(GL_POLYGON);
    // FIXME: Turns out you need to appoint normals to generate a proper
    // shading.
    glNormal3d(0,0,1);//be careful of the signs!
    for (int i = 0; i < slices; i++, angle += step) {
        vertices[i][0] =radius*cos(angle);
        vertices[i][1] =radius*sin(angle);
        glVertex3d(vertices[i][0], vertices[i][1], height);
    }
    glEnd();
    // bottom face
    glBegin(GL_POLYGON);
    // FIXME: Note that in order to have a correct front/ back side, you should arrange the vertices in reverse order.
    glNormal3d(0,0,-1);// normal seems to ignore the signs.
    for (int i = slices-1; i >=0; i--)
        glVertex2dv(vertices[i]);
    glEnd();

    // draw the lateral facets
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < slices; i++) {
        // FIXME: be careful of the order! See OpenGL manual.
        glVertex3d(vertices[i][0], vertices[i][1], height);
        glVertex2dv(vertices[i]);
        // normal
        glNormal3d(vertices[i][0],vertices[i][1],0);
    }
    glEnd();
    free(vertices);
    return;
}

/**
 * draws one hexagonal plane on the xy plane, centered at the origin.
 * Side length of the hexagon is given.
 * */
void wing(GLdouble sideLength = 1.5) {
    const GLdouble root3 = sqrt(3);
    // all scaled by factor 2 for the convenience of representations.
    GLdouble vertices[6][2] = {{1, root3},   {2, 0},  {1, -root3},
                               {-1, -root3}, {-2, 0}, {-1, root3}};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 2; j++) vertices[i][j] *= sideLength / 2.0;
    glColor3d(1, 1, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) glVertex2dv(vertices[i]);
    glEnd();
    return;
}

void drawUFO() {
    GLdouble offset[] = {0, 0, 0};
    const int slices = 50;
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslated(offset[0], offset[1], offset[2]);
    glColor3d(1, 1, 1);
    // TODO: rewrite my own version of glutSolidCylinder, sphere, etc,
    // so that it can save the points and faces as obj.
    glutSolidSphere(1.0, slices, slices);
    // drawing symmetric shapes loop
    glPushMatrix();
    for (int i = 0; i < 2; i++) {
        GLdouble cylinderHeight = 4;
        cylinder(0.5, cylinderHeight / 2, slices, slices);
        glPushMatrix();
        
        glPushMatrix();
        glTranslated(0, 0, cylinderHeight / 2);
        // wing(1.5);
        glPopMatrix();

        // reflection about the xy-plane.
        glScaled(1, 1, -1);
    }
    glPopMatrix();

    glTranslated(3, 0, 0);
    glutSolidCylinder(0.5, 2.0, slices, slices);
    glTranslated(3,0,0);
    cylinder(0.5,2.0,slices,slices);
    glPopMatrix();

    glPopMatrix();
}
