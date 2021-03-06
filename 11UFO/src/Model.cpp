#include "Model.h"
#include "Eigen/Core"

typedef Eigen::Matrix<GLdouble,4,4> Matrix4;
typedef Eigen::Matrix<GLdouble,4,1> Vector4;

Vector4 v4(const Vector& v){
    Vector4 newV;
    for (int i=0;i<3;i++) newV[i]=v[i];
    return newV;
}

/**
 * compromised version, get the current glMatrix and compute the coordinates of vertices.
 * TODO: implement Node and transformations(Huge amount of work),
 * then rewrite the function with Node.
 * */
int Mesh::output(std::ostream& out) const{
    static int index=0;
    GLdouble T[16];
    // get the current model_view matrix.
    glGetDoublev(GL_MODELVIEW_MATRIX,T);
    Matrix4 M;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        // Note that OpenGL is column order.
            M(i,j)=T[i*4+j];
    out << "o "<<index++<<std::endl;
    for (auto p=this->v.begin();p!=this->v.end();p++){
        out << "v";
        auto newV=M*v4(Vector(*p));
        for (int i=0;i<3;i++) out<<" "<<newV[i];
        out<<std::endl;
    }
    for (auto p=this->f.begin();p!=this->f.end();p++){
        out << "f";
        for (auto v=p->begin();v!=p->end();v++){
            Vertex& v1=*(*v);
            const Vertex& head=this->v[0];
            // FIXME: Very ugly and confusing code! Is there any better way?
            out << " " << (&v1 - &(head))/sizeof(Vertex);
        }
        out<<std::endl;
    }
    return 0;
}

void Face::push_back(const Vertex& v) {
    list::push_back(std::make_shared<Vertex>(v));
}

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

int Face::update() {
    // not enough vertices.
    if (this->size() < 3) return -1;
    Vector v[3];
    int i = 0;
    // Use the first three sample vertices and cross product to construct the
    // normal.
    for (auto p = this->begin(); i < 3; i++, p++) {
        v[i] = Vector(*(*p));
        if (i > 0) v[i] = v[i] - v[0];
    }
    this->normal = cross(v[1], v[2]).normalized();
}

Face& Face::updated() {
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