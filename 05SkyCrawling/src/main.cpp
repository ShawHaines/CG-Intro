#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
// #include <Windows.h> // actually glut deals with it already.
#include "geometry.h"
using namespace std;

/** 
 * Convention: the screen axis is x,y (right, down direction)
 * z axis is perpendicular to the screen plane, whose direction is determined by 
 * the right hand rule. 
 * */

static Point eye={0.0,0.0,100.0};
static Point focus={0.0,0.0,0.0};
// for mouse clicking 
static int x_0;
static int y_0;
void init() {
    //定义光源的颜色和位置
    GLfloat ambient[] = {0.5, 0.8, 0.1, 0.1};
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

int move(Point& p,GLdouble dx, GLdouble dy, GLdouble dz){
    p[0]+=dx;
    p[1]+=dy;
    p[2]+=dz;
    cout << "(" << p[0] << ", " << p[1] << ", " << p[2] << " )" << endl;
    return 0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // seems that gluLookAt should be applied first.
    gluLookAt(eye[0], eye[1], eye[2], focus[0], focus[1], focus[2], 0.0, 0.0,
              1.0);
    glColor3f(1.0, 1.0, 1.0);
    // default is 1.0 width.
    glLineWidth(1.0);
    // glRectf(-25.0, -25.0, 25.0, 25.0);
    glutSolidCube(25.0);
    glTranslated(50.0,0.0,-100.0);
    glutSolidSphere(10.0,50,50);

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    gluPerspective(60.0,16.0/9.0,5.0,1000.0);
    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    // gluLookAt(eye[0],eye[1],eye[2],focus[0],focus[1],focus[2],0.0,0.0,1.0);
    // glPopMatrix();
}

// mouse event, triggered when mouse was clicked.
void mouse(int button, int state, int x, int y) {
    
    switch (button)
    {
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
    GLdouble x=0,y=0,z=0;
    GLdouble step=10.0;
    switch (key) {
        case 'a':
            x=-step; // go leftward is x minus.
            break;
        case 'd':
            x=step;
            break;
        case 'w':
            y=step;
            break;
        case 's':
            y=-step;
            break;
        case 'j': // vim style keymap for up.
            z=step;
            break;
        case 'k':
            z=-step;
            break;
    }
    cout << "eye   ";
    move(eye,x,y,z);
    glutPostRedisplay();
}

// Mouse motion event, triggered when a mouse key is pressed and mouse is
// moving.
void mouseMove(int x, int y) {
    int dx = x - x_0;
    int dy = y - y_0;


    x_0=x; y_0=y;
    cout<<"focus ";
    move(focus,dx,dy,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // don't use gluLookAt, thorough implementation of self frame.
    // gluLookAt(eye[0],eye[1],eye[2],focus[0],focus[1],focus[2],0.0,1.0,0.0);

    // be careful with the sign.
    glRotated(dx,0.0,-1.0,0.0);
    glRotated(dy,1.0, 0.0,0.0);
    glPopMatrix();
    glutPostRedisplay();
    return;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffer.
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
    return 0;
}