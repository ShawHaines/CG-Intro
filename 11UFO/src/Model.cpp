#include "Model.h"

int Face::display() const {
    glBegin(GL_POLYGON);
    glNormal3dv(&(this->normal[0]));
    for (auto p = this->begin(); p != this->end(); p++) {
        auto vertex = *(*p);
        glVertex3d(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
    return 0;
}

int Face::update(){
    // not enough vertices.
    if (this->size()<3) return -1;
    Vector v[3];
    int i=0;
    // Use the first three sample vertices and cross product to construct the normal.
    for (auto p=this->begin();i<3;i++,p++){
        v[i]=Vector(*(*p));
        if (i>0) v[i]=v[i]-v[0];
    }
    this->normal=cross(v[1],v[2]).normalized();
}

Face& Face::updated(){
    this->update();
    return (*this);
}

int Mesh::display() const {
    for (auto p = f.begin(); p != f.end(); p++) {
        p->display();
    }
    return 0;
}

int Mesh::faceSize() const { return f.size(); }

int Mesh::vertexSize() const { return v.size(); }