#include <iostream>
// #if defined(_WIN32) || defined(WIN32)
// #include <windows.h>
// #endif
#include "GL/glut.h"

/**
 * handy shortcut, convert a hex integer into color set.
 * */
void glColor1i(GLuint c) {
    GLubyte r, g, b;
    r = (c / 0x10000);
    g = (c / 0x100 % 0x100);
    b = c % 0x100;
    // glColor3f(1.0 * r / 0x100, 1.0 * g / 0x100, 1.0 * b / 0x100);
    glColor3ub(r,g,b);
}

// void display(void) {

//     glClear(GL_COLOR_BUFFER_BIT);
//     glBegin(GL_POLYGON);
//     glVertex3f(2.0, 4.0, 0.0);
//     glVertex3f(8.0, 4.0, 0.0);
//     glVertex3f(8.0, 6.0, 0.0);
//     glVertex3f(2.0, 6.0, 0.0);
//     glEnd();
//     glFlush();

// }

/**
 * Draw the national flag of Jordan. Reference in ./img/Flag_of_Jordan.svg.
 * */
void jordanFlag(void) {
    // Convention: Always counter-clockwise, order of drawing MATTERS.

    // black background.
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    // green rectangle.
    glColor1i(0x007a3d);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(0, 1680);
    glVertex2i(10080, 1680);
    glVertex2i(10080, 0);
    glEnd();
    // white rectangle.
    glBegin(GL_POLYGON);
    glColor1i(0xffffff);
    glVertex2i(0, 1680);
    glVertex2i(0, 3360);
    glVertex2i(10080, 3360);
    glVertex2i(10080, 1680);
    glEnd();
    // red triangle.
    glBegin(GL_TRIANGLES);
    glColor1i(0xce1126);
    glVertex2i(0, 0);
    glVertex2i(0, 5040);
    glVertex2i(5040, 2520);
    glEnd();
    // white hexagon star.
    // glBegin(GL_LINE_LOOP);
    // glColor1i(0xffffff);
    // GLint x = 1557, y = 2880;
    // glVertex2i(x, y);
    // glVertex2i(x += -78, y += -198);
    // glVertex2i(x += -203, y += 62);
    // glVertex2i(x += 106, y += -184);
    // glVertex2i(x += -176, y += -120);
    // glVertex2i(x += 211, y += -32);
    // glVertex2i(x += -16, y += -212);
    // glVertex2i(x += 156, y += 144);
    // glVertex2i(x += 157, y += -144);
    // glVertex2i(x += -16, y += 212);
    // glVertex2i(x += 210, y += 32);
    // glVertex2i(x += -175, y += 120);
    // glVertex2i(x += 106, y += 184);
    // glVertex2i(x += -203, y += -62);
    // glEnd();
    // in order to fill...
    glBegin(GL_TRIANGLE_FAN);
    glColor1i(0xffffff);
    glVertex2i(1557,2520);
    GLint x = 1557, y = 2880;
    glVertex2i(x, y);
    glVertex2i(x += -78, y += -198);
    glVertex2i(x += -203, y += 62);
    glVertex2i(x += 106, y += -184);
    glVertex2i(x += -176, y += -120);
    glVertex2i(x += 211, y += -32);
    glVertex2i(x += -16, y += -212);
    glVertex2i(x += 156, y += 144);
    glVertex2i(x += 157, y += -144);
    glVertex2i(x += -16, y += 212);
    glVertex2i(x += 210, y += 32);
    glVertex2i(x += -175, y += 120);
    glVertex2i(x += 106, y += 184);
    glVertex2i(x += -203, y += -62);
    // the last one...
    glVertex2i(1557,2880);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1008, 504);
    glutCreateWindow("flag of Jordan");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // What does this one do? How large do you want your canvas to be?
    glOrtho(0.0, 10080, 0.0, 5040, -1.0, 1.0);
    glutDisplayFunc(jordanFlag);
    glutMainLoop();
    return 0;
}
