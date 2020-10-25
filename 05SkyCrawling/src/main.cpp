#include <GL/freeglut.h>
#include <stdlib.h>
#include <iostream>
// #include <Windows.h> // actually glut deals with it already.
#include "geometry.h"
#include "Astroid.h"

using namespace std;

/**
 * Convention: the screen axis is x,y (right, down direction)
 * z axis is perpendicular to the screen plane, whose direction is determined by
 * the right hand rule.
 * */

static Point eye = {0.0, 0.0, 100.0};
static Point focus = {0.0, 0.0, 0.0};
// for mouse clicking
static int x_0;
static int y_0;

// angle of viewing.
static GLdouble angle = 60.0;
// angle range and steps.
static GLdouble angleStep = 5.0, angleMin = 5.0, angleMax = 120.0;

// Field of view parameters.
static GLdouble aspect = 16.0 / 9.0, zNear = 5.0, zFar = 1000.0;

static Astroid* sun=NULL;

// add stars to the solar system. The only root of the tree is a sun.
int addStars(){
    sun=new Astroid(10,0,1e6);
    auto earth=new Astroid(2.5,30,10);
    auto moon = new Astroid(1,5,5);
    auto jupyter= new Astroid(5,50,60);
    // planets
    sun->satellites.push_back(earth);
    sun->satellites.push_back(jupyter);
    // satellites
    earth->satellites.push_back(moon);
    return 0;
}

void solarDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // seems that gluLookAt should be applied first.
    gluLookAt(eye[0], eye[1], eye[2], focus[0], focus[1], focus[2], 0.0, -1.0,
              0.0);
    sun->display();
    glPopMatrix();
    glutSwapBuffers();
}

// set lighting to make the scene nicer.
void init() {
    // defining the color and position of light source.
    GLfloat ambient[] = {1.0, 1.0, 0.1, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {-80.0, 50.0, 25.0, 1.0};
    //选择光照模型
    GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat local_view[] = {0.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    //设置环境光
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //设置漫射光
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    //设置光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    //启动光照
    glEnable(GL_LIGHTING);
    //启用光源
    glEnable(GL_LIGHT0);
}

int move(Point& p, GLdouble dx, GLdouble dy, GLdouble dz) {
    p[0] += dx;
    p[1] += dy;
    p[2] += dz;
    cout << "(" << p[0] << ", " << p[1] << ", " << p[2] << " )" << endl;
    return 0;
}

// void display(void) {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glMatrixMode(GL_MODELVIEW);
//     glPushMatrix();
//     glLoadIdentity();
//     // seems that gluLookAt should be applied first.
//     gluLookAt(eye[0], eye[1], eye[2], focus[0], focus[1], focus[2], 0.0, -1.0,
//               0.0);
//     glColor3f(1.0, 1.0, 1.0);
//     // default is 1.0 width.
//     glLineWidth(1.0);
//     // glRectf(-25.0, -25.0, 25.0, 25.0);
//     glutSolidCube(25.0);
//     glTranslated(50.0, 0.0, -100.0);
//     glutSolidSphere(10.0, 50, 50);

//     glPopMatrix();

//     glutSwapBuffers();
// }

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, aspect, zNear, zFar);
    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    // gluLookAt(eye[0],eye[1],eye[2],focus[0],focus[1],focus[2],0.0,0.0,1.0);
    // glPopMatrix();
}

void timer(){
    sun->revolution();
    glutPostRedisplay();
    Sleep(100);
}

// mouse event, triggered when mouse was clicked.
void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            x_0 = x;
            y_0 = y;
            break;
        default:
            break;
    }

    // switch (button) {
    //     case GLUT_LEFT_BUTTON:
    //         if (state == GLUT_DOWN) glutIdleFunc(spinDisplay);
    //         break;
    //     case GLUT_RIGHT_BUTTON:
    //         if (state == GLUT_DOWN) glutIdleFunc(NULL);
    //         break;
    //     default:
    //         break;
    // }
    // glutPostRedisplay();
    return;
}

// keyboard event callback.
void keyPressed(unsigned char key, int mouseX, int mouseY) {
    GLdouble x = 0, y = 0, z = 0;
    GLdouble step = 10.0;
    switch (key) {
        case 'a':
            x = -step;  // go leftward is x minus.
            break;
        case 'd':
            x = step;
            break;
        case 'w':
            z = -step;
            break;
        case 's':
            z = step;
            break;
        case 'j':  // vim style keymap for up.
            y = step;
            break;
        case 'k':
            y = -step;
            break;
    }
    cout << "eye   ";
    move(eye, x, y, z);
    glutPostRedisplay();
}

// Mouse motion event, triggered when a mouse key is pressed and mouse is
// moving.
void mouseMove(int x, int y) {
    int dx = x - x_0;
    int dy = y - y_0;

    x_0 = x;
    y_0 = y;
    cout << "focus ";
    move(focus, dx, dy, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // don't use gluLookAt, thorough implementation of self frame.
    // gluLookAt(eye[0],eye[1],eye[2],focus[0],focus[1],focus[2],0.0,1.0,0.0);

    // be careful with the sign.
    glRotated(dx, 0.0, -1.0, 0.0);
    glRotated(dy, 1.0, 0.0, 0.0);
    glPopMatrix();
    glutPostRedisplay();
    return;
}

void mouseWheel(int wheel, int direction, int x, int y) {
    printf("wheel: %d, direction: %d, x:%d, y:%d\n", wheel, direction, x, y);
    switch (direction) {
        case -1:  // zoom out
            if (angle - angleStep >= angleMin) angle -= angleStep;
            break;
        case +1:
            if (angle + angleStep <= angleMax) angle += angleStep;
            break;
        default:
            break;
    }
    cout << "angle: " << angle << endl;
    glMatrixMode(GL_PROJECTION);  // remember to overwrite the original one...
    glLoadIdentity();
    gluPerspective(angle, aspect, zNear, zFar);
    glutPostRedisplay();
    return;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffer.
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    addStars();
    glutDisplayFunc(solarDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyPressed);
    glutMouseWheelFunc(mouseWheel);
    // glutTimerFunc(100,timer,0);
    glutIdleFunc(timer);
    glutMainLoop();
    return 0;
}