#include <GL/freeglut.h>
#include <stdlib.h>

#include <iostream>
// #include <Windows.h> // actually glut deals with it already.
#include "Astroid.h"
#include "Texture.h"
#include "geometry.h"

using namespace std;

/**
 * Convention: the screen axis is x,y (right, up direction)
 * z axis is perpendicular to the screen plane, whose direction is determined by
 * the right hand rule.
 * */

// for mouse clicking.
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
static GLdouble initPos[] = {0, 0, 15};
static GLdouble view[16];
// Texture numbers in GL
static GLuint sunTexture, environmentTexture, jupiterTexture, saturnTexture,
    earthTexture, mercuryTexture, moonTexture;
// ----------------------function declarations----------------------------

static void init();
// set lighting to make the scene nicer.
static void setLighting();
static void setMaterial();
static void setPosition(GLdouble* position);
static void setTexture();
// extern GLint loadTexture(char* fileName);
// add stars to the solar system. The only root of the tree is a sun.
static int addAstroids();
static void solarDisplay();
// draw auxilary axes.
static void drawUVSquare(double sideLength, GLuint texture);
// supppose currently at the center of the cubic box.
static void drawBox(double sideLength = 1);
static void drawAxis();
extern void drawUFO();

// interface callbacks

void reshape(int w, int h);
void timer(int value);
// mouse event, triggered when mouse was clicked.
static void mouse(int button, int state, int x, int y);
// mouse motion event, triggered when a mouse key is pressed and mouse is
// moving.
void mouseMove(int x, int y);
void mouseWheel(int wheel, int direction, int x, int y);
// keyboard event callback.
static void keyPressed(unsigned char key, int mouseX, int mouseY);

// -----------------------------------------------------------------------

int addAstroids() {
    sun = new Astroid(10, 1e6, 100, Orbit(0));
    // normal co-planar orbit test case.
    auto earth = new Astroid(2.5, 10, 1, Orbit(30, 0, 1, 0));
    // non-coplanar orbit test, satellite.
    auto moon = new Astroid(1, 5, 1e6, Orbit(5, 0, -10, 1));
    auto jupiter = new Astroid(5, 60, 1, Orbit(75, 1, 5, 0));
    auto mercury = new Astroid(1.5, 15, 1, Orbit(20, 0.1, 1, 0));
    auto saturn = new Astroid(3.5, 55, 100);
    // saturn ring is a satellite with 0 size...
    auto saturnRing = new Astroid(0, 1e6, 1e6, Orbit(5, 1, -5, 1));
    // planets
    sun->satellites.push_back(earth);
    sun->satellites.push_back(jupiter);
    sun->satellites.push_back(mercury);
    sun->satellites.push_back(saturn);
    // satellites
    earth->satellites.push_back(moon);
    saturn->satellites.push_back(saturnRing);
    // style setting.
    earth->setColor(0, 0, 1, 1);
    earth->texture = earthTexture;
    mercury->setColor(1.0, 0.5, 0.0, 1);
    mercury->texture = mercuryTexture;
    moon->setColor(0.8, 0.8, 0.8, 1);
    moon->texture = moonTexture;
    jupiter->setColor(189 / 255.0, 158 / 255.0, 125 / 255.0, 1);
    jupiter->texture = jupiterTexture;
    saturn->setColor(189 / 255.0, 158 / 255.0, 125 / 255.0, 1);
    saturn->texture = saturnTexture;
    sun->setColor(1, 1, 0.8, 1);
    sun->texture = sunTexture;
    sun->emission = true;
    return 0;
}

void drawBox(double sideLength) {
    // vertex coordinates for 6 faces. (+x is front, +z is top) Order: front,
    // back, left, right, top, bottom.
    GLdouble v[24][3] = {{1, 1, 1},  {1, 1, -1},  {1, -1, -1},  {1, -1, 1},
                         {-1, 1, 1}, {-1, -1, 1}, {-1, -1, -1}, {-1, 1, -1},
                         {1, -1, 1}, {1, -1, -1}, {-1, -1, -1}, {-1, -1, 1},
                         {1, 1, 1},  {-1, 1, 1},  {-1, 1, -1},  {1, 1, -1},
                         {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1},
                         {1, 1, -1}, {-1, 1, -1}, {-1, -1, -1}, {1, -1, -1}};
    // box divided.
    GLdouble vt[24][2] = {{1, 2}, {1, 1}, {0, 1}, {0, 2}, {2, 2}, {3, 2},
                          {3, 1}, {2, 1}, {4, 2}, {4, 1}, {3, 1}, {3, 2},
                          {1, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 2}, {0, 2},
                          {0, 3}, {1, 3}, {1, 1}, {1, 0}, {0, 0}, {0, 1}};
    GLdouble cx = 1 / 4.0, cy = 1 / 3.0;
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    GLint oldTexture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture);
    glBindTexture(GL_TEXTURE_2D, environmentTexture);
    glBegin(GL_QUADS);
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 3; j++) v[i][j] *= sideLength / 2.0;
        vt[i][0] *= cx;
        vt[i][1] *= cy;
        glTexCoord2dv(vt[i]);
        glVertex3dv(v[i]);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, oldTexture);
    glDisable(GL_TEXTURE_2D);
    return;
}

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

void solarDisplay() {
    // 1 stands for point light, while 0 stands for directional source.
    GLfloat sun_light[4] = {0, 0, 0, 1};
    // directional light from the upper y direction.
    GLfloat global_light[4] = {0, 1, 0, 0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    drawAxis();

    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    drawBox(1000);
    glPopMatrix();

    // drawUFO();
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light);
    glLightfv(GL_LIGHT1, GL_POSITION, global_light);
    sun->display();
    glPopMatrix();
    glutSwapBuffers();
}

void setPosition(GLdouble* position) {
    glMatrixMode(GL_MODELVIEW);
    glTranslated(-position[0], -position[1], -position[2]);
    return;
}

void setLighting() {
    GLfloat light_position[] = {0, 0, 0,
                                1};  // lighting position, 1 for point source
    GLfloat white_light[] = {1., 1., 1., 1.0};             // white...
    GLfloat weak_light[] = {0.1, 0.1, 0.1, 1.0};           // weaker than white.
    GLfloat Light_Model_Ambient[] = {0.1, 0.1, 0.1, 1.0};  // ambient light.

    // light#0 is the light from the sun.
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   // Diffusing light
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  // Specular light
    // light#1 is a directional source from above.
    glLightfv(GL_LIGHT1, GL_DIFFUSE, weak_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, weak_light);

    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        Light_Model_Ambient);  // ambient light. Set all over the scene.

    glEnable(GL_LIGHTING);  // Enable lighting.
    glEnable(GL_LIGHT0);    // Enable light#0
    glEnable(GL_LIGHT1);
}

void setMaterial() {
    // reflexibility
    GLfloat mat_specular[] = {0.633, 0.727811, 0.633,
                              0.001};       // mirror reflex coefficient
    GLfloat mat_shininess[] = {0.2 * 128};  // highlight
    GLfloat mat_ambient[] = {0.0215, 0.175, 0.0215, 1.0};
    GLfloat mat_diffuse[] = {0.0757, 0.614, 0.07568, 1.0};
    GLfloat mat_emission[] = {0.1, 0.1, 0.1, 1};
    // Material properties.
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // glMaterialfv(GL_FRONT,GL_EMISSION, mat_emission);

    glEnable(GL_COLOR_MATERIAL);
    // This setting looks much nicer. Have ambient and diffuse material property
    // track the current color.
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void setTexture() {
    // glEnable(GL_TEXTURE_2D);
    // load texture, note that it's relative to the executable.
    std::string folder = "./img/texture/";
    sunTexture = loadTexture(folder + "sun.png");
    jupiterTexture = loadTexture(folder + "jupiter.png");
    saturnTexture = loadTexture(folder + "saturn.png");
    earthTexture = loadTexture(folder + "earth.png");
    moonTexture = loadTexture(folder + "moon.png");
    mercuryTexture = loadTexture(folder + "mercury.png");
    environmentTexture = loadTexture(folder + "starmap.png");
    return;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // background color
    glShadeModel(GL_SMOOTH);
    // This line of code activates wireframe mode.
    // glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_DEPTH_TEST);  // Enable Depth test.

    setLighting();
    setMaterial();
    setTexture();
    addAstroids();
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
    // FIXME: You need to insert the matrix into the foremost section of the
    // transformation.
    glGetDoublev(GL_MODELVIEW_MATRIX, view);
    glLoadIdentity();
    glTranslated(-x, -y, -z);
    glMultMatrixd(view);
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
    // FIXME: You need to insert the matrix into the foremost section of the
    // transformation.
    glMatrixMode(GL_MODELVIEW);
    glGetDoublev(GL_MODELVIEW_MATRIX, view);
    glLoadIdentity();
    // be careful with the signs!
    glRotated(dYaw, 0.0, 1.0, 0.0);
    glRotated(dPitch, 1.0, 0.0, 0.0);
    glMultMatrixd(view);
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
    // register callback functions.
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