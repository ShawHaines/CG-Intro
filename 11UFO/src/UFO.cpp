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
    for (int j = 1; j < stacks - 1; j++)
        for (int i = 0; i < slices; i++) {
            int k = (i + 1) % slices;
            Face face;
            // note the outward direction!
            face.push_back(v[(j - 1) * slices + i + size]);
            face.push_back(v[j * slices + i + size]);
            face.push_back(v[j * slices + k + size]);
            face.push_back(v[(j - 1) * slices + k + size]);
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
int wing(Mesh& target, GLdouble sideLength = 1.5, GLdouble thickness=0.1) {
    // a hexagon is approximately a circle...
    return cylinder(target,sideLength,thickness,6);
}

// TODO: write Node... stop registering a mesh for every bloody redisplay!
void drawUFO() {
    static bool first = true;
    GLdouble offset[] = {0, 0, 0};
    const int slices = 50;
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslated(offset[0], offset[1], offset[2]);
    glColor3d(1, 1, 1);

    // only generates them once.
    static Mesh sphereMesh, cylinderMesh, wingMesh;
    GLdouble cylinderHeight = 4.0;
    if (first) {
        sphere(sphereMesh, 1.0, slices, slices);
        cylinder(cylinderMesh, 0.5, cylinderHeight / 2, slices);
        wing(wingMesh, 1.5,0.1);
    }
    sphereMesh.display();
    // drawing symmetric shapes loop
    glPushMatrix();
    for (int i = 0; i < 2; i++) {
        cylinderMesh.display();
        glPushMatrix();
        glTranslated(0, 0, cylinderHeight / 2);
        wingMesh.display();
        glPopMatrix();

        // reflection about the xy-plane.
        glScaled(1, 1, -1);
    }
    glPopMatrix();

    glPopMatrix();
    first = false;
}
