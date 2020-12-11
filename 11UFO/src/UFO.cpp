#include "GL/freeglut.h"
#include "math.h"
// #include "Astroid.h"
// #include "geometry.h"

/**
 * draws one hexagonal plane on the xy plane, centered at the origin.
 * Side length of the hexagon is given.
 * */
void wing(GLdouble sideLength=1.5){
    const GLdouble root3=sqrt(3);
    // all scaled by factor 2 for the convenience of representations.
    GLdouble vertices[6][2]={
        {1,root3},
        {2,0},
        {1,-root3},
        {-1,-root3},
        {-2,0},
        {-1,root3}
    };
    for (int i=0;i<6;i++) for (int j=0;j<2;j++)
        vertices[i][j]*=sideLength/2.0;
    glColor3d(1,1,1);
    glBegin(GL_POLYGON);
    for (int i=0;i<6;i++)
        glVertex2dv(vertices[i]);
    glEnd();
    return;
}

void drawUFO(){
    GLdouble offset[]={0,0,0};
    const int slices=50;
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslated(offset[0],offset[1],offset[2]);
    glColor3d(1,1,1);
    glutSolidSphere(1.0,slices,slices);
    glPushMatrix();
    GLdouble cylinderHeight=4;
    glTranslated(0,0,-cylinderHeight/2);
    glutSolidCylinder(0.5,cylinderHeight,slices,slices);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,-cylinderHeight/2);
    wing(1.5);
    glTranslated(0,0,cylinderHeight);
    wing(1.5);
    glPopMatrix();

    glPopMatrix();
}
