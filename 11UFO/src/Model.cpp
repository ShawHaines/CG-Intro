#include "Model.h"

int Face::display() const {
    glBegin(GL_POLYGON);
    glNormal3dv(&(this->normal.end[0]));
    for (auto p = this->begin(); p != this->end(); p++) {
        auto vertex = *(*p);
        glVertex3d(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
    return 0;
}

int Mesh::display() const {
    for (auto p = f.begin(); p != f.end(); p++) {
        p->display();
    }
    return 0;
}

int Mesh::faceSize() const { return f.size(); }

int Mesh::vertexSize() const { return v.size(); }