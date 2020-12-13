#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include "GL/freeglut.h"
#include "Model.h"
// #include "Astroid.h"
// #include "geometry.h"

/**
 * cylinder(), apart from the target Mesh, arguments is all the same with
 * glutSolidCylinder( double radius, double height, GLint slices, GLint stacks);
 * */

int cylinder(Mesh& target, double radius, double height, GLint slices, GLint stacks=0) {
    // TODO: Use Bresenham algorithm.
    GLdouble step = M_PI * 2 / slices, angle = 0;
    auto &v=target.v;
    int size=v.size();
    int newSize=size+slices*2;
    // reserve slices*2 vertices of space.
    v.reserve(newSize);
    int i,j;
    // add vertices. top first.
    for (i = 0,angle=0; i < slices; i++, angle += step) {
        v.push_back(Vertex(radius*cos(angle),radius*sin(angle),height));
    }
    for (i = 0,angle=0; i < slices; i++, angle += step) {
        v.push_back(Vertex(radius*cos(angle),radius*sin(angle),0));
    }
    
    // add facets.
    auto &f = target.f;
    // top facet
    Face topFacet;
    topFacet.normal=Vector(0,0,1);
    for (i=size;i<size+slices;i++)
        topFacet.push_back(std::make_shared<Vertex>(v[i]));
    f.push_back(topFacet);
    // bottom facet
    Face bottomFacet;
    bottomFacet.normal=Vector(0,0,-1);
    for (i=newSize-1;i>=size+slices;i--) 
    // reverse order so that the outward direction is correct.
        bottomFacet.push_back(std::make_shared<Vertex>(v[i]));
    f.push_back(bottomFacet);
    // lateral facets
    for (i=0;i<slices;i++){
        j=(i+1) % slices;
        Face lateralFacet;
        lateralFacet.normal=Vector(v[i+size][0],v[i+size][1],0);
        // Note the arrangement in certain order to keep the outward direction correct.
        lateralFacet.push_back(std::make_shared<Vertex>(v[i+size]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[i+size+slices]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[j+size+slices]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[j+size]));
        f.push_back(lateralFacet);
    }
    return 0;
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

    // glutSolidSphere(1.0, slices, slices);
    // drawing symmetric shapes loop
    glPushMatrix();
    for (int i = 0; i < 2; i++) {
        GLdouble cylinderHeight = 4;
        // auto newMesh=new Mesh();
        // cylinder(*newMesh, 0.5, cylinderHeight / 2, slices, slices);
        glPushMatrix();
        
        glPushMatrix();
        glTranslated(0, 0, cylinderHeight / 2);
        // wing(1.5);
        glPopMatrix();

        // reflection about the xy-plane.
        glScaled(1, 1, -1);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, 0, 0);
    glutSolidCylinder(0.5, 2.0, slices, slices);
    glTranslated(-3,0,0);
    Mesh mesh;
    cylinder(mesh,0.5,2.0,slices,0);
    mesh.display();
    glPopMatrix();

    glPopMatrix();
}
