#include <GL/freeglut.h>
#include <stdlib.h>

#include <iostream>
// #include <Windows.h> // actually glut deals with it already.
#include "Astroid.h"
#include "geometry.h"

using namespace std;

/**
 * Convention: the screen axis is x,y (right, down direction)
 * z axis is perpendicular to the screen plane, whose direction is determined by
 * the right hand rule.
 * */

// static Point eye = {0.0, 0.0, 100.0};
// static Point focus = {0.0, 0.0, 0.0};
// for mouse clicking
static int x_0;
static int y_0;

// Field of view parameters.
static GLdouble aspect = 16.0 / 9.0, zNear = 5.0, zFar = 1000.0;
// view angle of perspective projection.
static GLdouble angle = 60.0;
// angle range and steps.
static GLdouble angleStep = 5.0, angleMin = 5.0, angleMax = 120.0;

// time refresh rate, in milliseconds.
static unsigned int interval = 15;

// viewing angle, measured in degrees.
static GLdouble roll = 0, pitch = 0, yaw = 0;
static GLdouble coeRoll = 0, coePitch = 0.1,
                coeYaw = 0.1;  // we don't consider roll for now.
// allowed pitch range. Yaw don't have such problems.
static GLdouble pitchMin = -87, pitchMax = 87;

// star.
static Astroid* sun = NULL;
static GLdouble initPos[]={0,0,100};

// add stars to the solar system. The only root of the tree is a sun.
int addAstroids() {
    sun = new Astroid(10, 0, 1e6);
    // normal co-planar orbit test case.
    auto earth = new Astroid(2.5, 30, 10, 0, 1, 0);
    // non-coplanar orbit test, satellite.
    auto moon = new Astroid(1, 5, 5, 0, -10, 1);
    auto jupyter = new Astroid(5, 75, 60, 1, 5, 0);
    auto mercury = new Astroid(1.5, 20, 15, 0.1, 1, 0);
    auto saturn = new Astroid(3.5, 55, 100);
    // saturn ring is a satellite with 0 size...
    auto saturnRing = new Astroid(0, 5, 1e6, 1, -5, 1);
    // planets
    sun->satellites.push_back(earth);
    sun->satellites.push_back(jupyter);
    sun->satellites.push_back(mercury);
    sun->satellites.push_back(saturn);
    // satellites
    earth->satellites.push_back(moon);
    saturn->satellites.push_back(saturnRing);
    // style setting.
    earth->setColor(0, 0, 1, 1);
    mercury->setColor(0.4, 0.4, 0.4, 1);
    moon->setColor(0.8, 0.8, 0.8, 1);
    jupyter->setColor(189 / 255.0, 158 / 255.0, 125 / 255.0, 1);
    saturn->setColor(189 / 255.0, 158 / 255.0, 125 / 255.0, 1);
    sun->setColor(1, 0, 0, 1);
    return 0;
}

// draw auxilary axes.
void drawAxis() {
    glBegin(GL_LINES);
    GLfloat originalLineWidth;
    glGetFloatv(GL_LINE_WIDTH, &originalLineWidth);
    glLineWidth(500000.0);
    glColor3d(1, 0, 0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(100.0, 0.0, 0.0);  // x axis.
    glColor3d(0, 1, 0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 100.0, 0.0);  // y axis.
    glColor3d(0, 0, 1);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 100.0);  // z axis.
    glLineWidth(originalLineWidth);
    glEnd();
    return;
}

extern void drawUFO();

void solarDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    drawAxis();
    drawUFO();
    // seems that gluLookAt should be applied first. Even if you don't 
    // declare it, the system will automatically adopt a gluLookAt(0,0,0, 0,0,-1, 0,1,0)
    gluLookAt(0, 0, 0, 0, 0, 100, 0.0, -1.0, 0.0);

    sun->display();
    glPopMatrix();
    glutSwapBuffers();
}


void setPosition(GLdouble* position){
    glMatrixMode(GL_MODELVIEW);
    glTranslated(-position[0],-position[1],-position[2]);
    return;
}

// set lighting to make the scene nicer.
void init() {
    // reflexibility
    GLfloat mat_specular[] = {0.633, 0.727811, 0.633,
                              0.001};       // mirror reflex coefficient
    GLfloat mat_shininess[] = {0.2 * 128};  // highlight
    GLfloat mat_ambient[] = {0.0215, 0.175, 0.0215, 1.0};
    GLfloat mat_diffuse[] = {0.0757, 0.614, 0.07568, 1.0};
    GLfloat light_position[] = {0, 50, 0, 0.0};  // lighting position (1,1,1).
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat Light_Model_Ambient[] = {0.2, 0.2, 0.2, 1.0};  // ambiant light.

    glClearColor(0.0, 0.0, 0.0, 0.0);  // background color
    glShadeModel(GL_SMOOTH);

    // Material properties.
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // lighting.
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   // Diffusing light
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  // Specular light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
                   Light_Model_Ambient);  // ambient light.

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      // Enable light#0
    glEnable(GL_DEPTH_TEST);  // Enable Depth test.

    // This setting looks much nicer.
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    setPosition(initPos);
}

int move(Point& p, GLdouble dx, GLdouble dy, GLdouble dz) {
    p[0] += dx;
    p[1] += dy;
    p[2] += dz;
    cout << "(" << p[0] << ", " << p[1] << ", " << p[2] << " )" << endl;
    return 0;
}

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

void timer(int value) {
    sun->revolution();
    glutPostRedisplay();
    // use this tricky method to refresh repeatedly. Hopefully it will not block
    // the threads.
    glutTimerFunc(interval, timer, 0);
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

    return;
}

// keyboard event callback.
void keyPressed(unsigned char key, int mouseX, int mouseY) {
    GLdouble x = 0, y = 0, z = 0;
    GLdouble step = 1.0;
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
        case 'j':  // vim style keymap for down.
            y = step;
            break;
        case 'k':
            y = -step;
            break;
    }
    glMatrixMode(GL_MODELVIEW);
    glTranslated(-x, -y, -z);
    glutPostRedisplay();
}

// Mouse motion event, triggered when a mouse key is pressed and mouse is
// moving.
void mouseMove(int x, int y) {
    double dYaw = (x - x_0) * coeYaw;
    double dPitch = (y - y_0) * coePitch;
    x_0 = x;
    y_0 = y;
    yaw += dYaw;
    pitch += dPitch;
    if (pitch >= pitchMax || pitch <= pitchMin) {
        pitch -= dPitch;
        dPitch = 0;
    }
    while (yaw >= 360) yaw -= 360;
    glMatrixMode(GL_MODELVIEW);
    // be careful with the signs!
    glRotated(dYaw, 0.0, -1.0, 0.0);
    glRotated(dPitch, 1.0, 0.0, 0.0);
    glutPostRedisplay();
    return;
}

void mouseWheel(int wheel, int direction, int x, int y) {
    printf("wheel: %d, direction: %d, x:%d, y:%d\n", wheel, direction, x, y);
    switch (direction) {
        case +1:  // zoom out
            if (angle - angleStep >= angleMin) angle -= angleStep;
            break;
        case -1:
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
    addAstroids();
    glutDisplayFunc(solarDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyPressed);
    glutMouseWheelFunc(mouseWheel);
    // glutTimerFunc(100,timer,0);
    glutTimerFunc(interval, timer, 0);
    glutMainLoop();
    return 0;
}