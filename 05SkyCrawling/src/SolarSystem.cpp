#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "GL/glut.h"
// #include "glut.h"
// #include "stdafx.h"

//行星
static GLfloat rot0 = 30.0;
static GLfloat rot1 = 0.0;
static GLfloat rot2 = 0.0;
static GLfloat rot3 = 0.0;
static GLfloat rot4 = 0.0;
static GLfloat rot5 = 0.0;
static GLfloat rot6 = 0.0;
static GLfloat rot7 = 0.0;
static GLfloat rot8 = 0.0;

//卫星
static GLfloat rot9 = 0.0;
static GLfloat rot10 = 0.0;
static GLfloat rot11 = 0.0;

//初始化
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glShadeModel(GL_FLOAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glPushMatrix();

    //绘制太阳
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(2.0, 32, 32);

    //绘制地球
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 5.0, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置地球公转速度
    glRotatef(rot0, 0.0, 1.0, 0.0);

    //设置地球半径
    glTranslatef(5.0, 0.0, 0.0);

    //设置地球自转速度
    glRotatef(rot1, 0.0, 1.0, 0.0);

    //绘制地球
    glutSolidSphere(0.4, 32, 32);

    //绘制地球的卫星—月亮
    glColor3f(0.5, 0.6, 0.5);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置月亮公转速度
    glRotatef(rot9, 0.0, 1.0, 0.0);

    //设置月亮公转半径
    glTranslatef(0.6, 0.0, 0.0);

    //绘制月亮
    glutSolidSphere(0.1, 10, 8);
    glPopMatrix();

    //绘制水星
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 2.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置水星公转速度
    glRotatef(rot1, 0.0, 1.0, 0.0);

    //设置水星公转半径
    glTranslatef(2.5, 0.0, 0.0);

    //设置水星自转
    glRotatef(rot3, 0.0, 1.0, 0.0);

    //绘制水星
    glutSolidSphere(0.2, 32, 32);
    glPopMatrix();

    //绘制金星
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 3.4, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置金星公转速度
    glRotatef(rot2, 0.0, 3.0, 0.0);

    //设置金星公转半径
    glTranslatef(3.4, 0.0, 0.0);

    //设置金星自转
    glRotatef(rot0, 0.0, 1.0, 0.0);

    //绘制金星
    glutSolidSphere(0.3, 32, 32);
    glPopMatrix();

    //绘制火星
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 6.6, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置火星公转速度
    glRotatef(rot3, 0.0, 4.0, 0.0);
    //设置火星公转半径
    glTranslatef(6.6, 0.0, 0.0);
    //设置火星自转
    glRotatef(rot7, 0.0, 2.0, 0.0);
    //绘制火星
    glutSolidSphere(0.5, 32, 32);
    glPopMatrix();

    //绘制木星
    glPushMatrix();
    glColor3f(2.0, 0.1, 1.0);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 8.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);
    //设置木星公转速度
    glRotatef(rot4, 0.0, 0.4, 0.0);
    //设置木星公转半径
    glTranslatef(8.5, 0.0, 0.0);
    //设置木星自转
    glRotatef(rot3, 0.0, 0.3, 0.0);
    //绘制木星
    glutSolidSphere(1.0, 32, 32);

    //绘制木星卫星--木卫1
    glColor3f(0.4, 0.3, 0.5);
    //抵消地球自转影响
    // glRotatef(-rot1, 0.0, 1.0, 0.0);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置木卫1公转速度
    glRotatef(rot10, 0.0, 1.0, 0.0);
    //设置木卫1公转半径
    glTranslatef(1.3, 0.0, 0.0);
    //绘制木卫1
    glutSolidSphere(0.1, 10, 8);

    //绘制木星卫星-木卫2
    glColor3f(0.5f, 0.5f, 0.5f);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //绘制木卫2公转速度
    glRotatef(rot11, 0.0, 1.0, 0.0);
    //绘制木卫2公转半径
    glTranslatef(1.2, 0.0, 0.0);
    //绘制木卫2
    glutSolidSphere(0.08, 10, 8);
    glPopMatrix();

    //绘制土星
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);

    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 12.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);
    //设置土星公转速度
    glRotatef(rot5, 0.0, 0.4, 0.0);
    //设置土星公转半径
    glTranslatef(12.5, 0.0, 0.0);
    //设置土星自转
    glRotatef(rot3, 0.0, 0.3, 0.0);
    //绘制土星
    glutSolidSphere(0.85, 32, 32);

    //绘制土星光环
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.1, 1.25, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);

    glutSolidTorus(0.07, 1.65, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glPopMatrix();
    glPopMatrix();

    //绘制天王星
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 15.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置天王星公转速度
    glRotatef(rot6, 0.0, 0.4, 0.0);
    //设置天王星公转半径
    glTranslatef(15.5, 0.0, 0.0);
    //设置天王星自转
    glRotatef(rot1, 0.0, 0.03, 0.0);
    //绘制天王星
    glutSolidSphere(0.15, 32, 32);
    glPopMatrix();

    //绘制海王星
    glPushMatrix();
    glColor3f(0.0, 0.0, 8.0);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 17.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //设置海王星公转速度
    glRotatef(rot7, 0.0, 0.4, 0.0);
    //设置海王星公转半径
    glTranslatef(17.5, 0.0, 0.0);
    //设置海王星自转
    glRotatef(rot3, 0.0, 0.3, 0.0);
    //绘制海王星
    glutSolidSphere(0.145, 32, 32);
    glPopMatrix();

    //绘制冥王星
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    //绘制辅助轨道
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.02, 19.5, 10, 64);
    glRotatef(-90, 1.0, 0.0, 0.0);
    //设置冥王星公转速度
    glRotatef(rot8, 0.0, 0.4, 0.0);
    //设置冥王星公转半径
    glTranslatef(19.5, 0.0, 0.0);
    //设置冥王星自转
    glRotatef(rot2, 0.0, 0.3, 0.0);
    //绘制冥王星
    glutSolidSphere(0.145, 32, 32);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void idle() {
    rot0 += 0.1;
    if (rot0 >= 360.0) rot0 -= 360.0;

    rot1 += 0.416;
    if (rot1 >= 360.0) rot1 -= 360.0;

    rot2 += 0.1631;
    if (rot2 >= 360.0) rot2 -= 360.0;

    rot3 += 0.053;
    if (rot3 >= 360.0) rot3 -= 360.0;

    rot4 += 0.0083;
    if (rot4 >= 360.0) rot4 -= 360.0;

    rot5 += 0.0034;
    if (rot5 >= 360.0) rot5 -= 360.0;

    rot6 += 0.0119;
    if (rot6 >= 360.0) rot6 -= 360.0;

    rot7 += 0.00069;
    if (rot7 >= 360.0) rot7 -= 360.0;

    rot8 += 0.0008;
    if (rot8 >= 360.0) rot8 -= 360.0;

    rot9 += 1.0;
    if (rot9 >= 360.0) rot9 -= 360.0;

    rot10 += 0.005;
    if (rot10 >= 360.0) rot10 -= 360.0;

    rot11 += 0.01;
    if (rot11 >= 360.0) rot11 -= 360.0;

    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, (char**)argv);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Solar System");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}