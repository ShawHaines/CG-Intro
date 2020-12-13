#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include "GL/freeglut.h"
#include "Model.h"
// #include "Astroid.h"
// #include "geometry.h"

/**
 * cylinder(Mesh& target, double radius, double height, GLint slices, GLint
 * stacks=0); apart from the target Mesh, arguments is all the same with
 * glutSolidCylinder( double radius, double height, GLint slices, GLint stacks);
 * */
int cylinder(Mesh& target, double radius, double height, GLint slices,
             GLint stacks = 0) {
    // TODO: Use Bresenham algorithm.
    GLdouble step = M_PI * 2 / slices, angle = 0;
    auto& v = target.v;
    int size = v.size();
    int newSize = size + slices * 2;
    // reserve slices*2 vertices of space.
    v.reserve(newSize);
    int i, j;
    // add vertices. top first.
    for (i = 0, angle = 0; i < slices; i++, angle += step) {
        v.push_back(Vertex(radius * cos(angle), radius * sin(angle), height));
    }
    for (i = 0, angle = 0; i < slices; i++, angle += step) {
        v.push_back(Vertex(radius * cos(angle), radius * sin(angle), 0));
    }

    // add facets.
    auto& f = target.f;
    // top facet
    Face topFacet;
    for (i = size; i < size + slices; i++)
        topFacet.push_back(std::make_shared<Vertex>(v[i]));
    f.push_back(topFacet.updated());
    // bottom facet
    Face bottomFacet;
    for (i = newSize - 1; i >= size + slices; i--)
        // reverse order so that the outward direction is correct.
        bottomFacet.push_back(std::make_shared<Vertex>(v[i]));
    f.push_back(bottomFacet.updated());
    // lateral facets
    for (i = 0; i < slices; i++) {
        j = (i + 1) % slices;
        Face lateralFacet;
        // Note the arrangement in certain order to keep the outward direction
        // correct.
        lateralFacet.push_back(std::make_shared<Vertex>(v[i + size]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[i + size + slices]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[j + size + slices]));
        lateralFacet.push_back(std::make_shared<Vertex>(v[j + size]));
        f.push_back(lateralFacet.updated());
    }
    return 0;
}

/**
 * sphere(Mesh& target, double radius, GLint slices, GLint stacks);
 * stacks is for latitudinal \theta and slices is slices for longitudinal \phi
 * */
int sphere(Mesh& target, double radius, GLint stacks, GLint slices) {
    auto& v = target.v;
    auto& f = target.f;
    GLdouble phiStep = 2 * M_PI / slices, thetaStep = M_PI / stacks;
    auto size = v.size();
    // vertices are indexed in such order: theta 0-pi, phi 0-2pi,
    // north and south poles are placed in the last.
    auto newSize = (stacks - 1) * slices + 2 + size;
    v.reserve(newSize);
    for (int j = 1; j < stacks; j++)
        for (int i = 0; i < slices; i++) {
            auto theta = j * thetaStep;
            auto phi = i * phiStep;
            v.push_back(Point(radius * cos(phi) * sin(theta),
                              radius * sin(phi) * sin(theta),
                              radius * cos(theta)));
        }
    // first the north pole, then the south
    v.push_back(Point(0, 0, radius));
    v.push_back(Point(0, 0, -radius));
    // add facets.
    // connected to the north pole.
    for (int i = 0; i < slices; i++) {
        int j = (i + 1) % slices;
        Face face;
        // again note the order to maintain a correct outward direction.
        face.push_back(v[newSize - 2]);
        face.push_back(v[i + size]);
        face.push_back(v[j + size]);
        f.push_back(face.updated());
    }
    // stackwise add facets in the middle.
    for (int j = 1; j < stacks; j++)
        for (int i = 0; i < slices; i++) {
            int k = (i + 1) % slices;
            Face face;
            // note the outward direction!
            face.push_back(v[(j - 1) * slices + i]);
            face.push_back(v[j * slices + i]);
            face.push_back(v[j * slices + k]);
            face.push_back(v[(j - 1) * slices + k]);
            f.push_back(face.updated());
        }
    // connected to the south pole.
    for (int i = 0; i < slices; i++) {
        int j = (i + 1) % slices;
        Face face;
        // again note the order to maintain a correct outward direction.
        face.push_back(v[newSize - 1]);
        face.push_back(v[j + newSize - slices]);
        face.push_back(v[i + newSize - slices]);
        f.push_back(face.updated());
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
    glTranslated(-3, 0, 0);
    Mesh mesh;
    cylinder(mesh, 0.5, 2.0, slices, 0);
    sphere(mesh, 0.8, slices, slices);
    mesh.display();
    glPopMatrix();

    glPopMatrix();
}
