#pragma once
#include <GL/freeglut.h>
#include <vector>

typedef GLdouble Point[3];

class Vector {
   public:
    Point end;
    Vector(GLdouble x, GLdouble y, GLdouble z) {
        end[0] = x;
        end[1] = y;
        end[2] = z;
    };
    Vector(Point& p) {
        for (int i = 0; i < 3; i++) end[i] = p[i];
    };
    double norm() const;
    double dot(const Vector& v) const;
    int normalize();
    bool isZero();
};

Vector cross(const Vector& v1, const Vector& v2);

double dot(const Vector& v1, const Vector& v2);
double norm(const Vector& v);
// Vector normalized(Vector& v);

class Quaternion:public std::vector<GLdouble>{
public:
    Quaternion(GLdouble x=0,GLdouble y=0, GLdouble z=0, GLdouble w=1): std::vector<GLdouble>(4){
        this->push_back(x);
        this->push_back(y);
        this->push_back(z);
        this->push_back(w);
    };
    // apply the local rotation matrix to OpenGL. TODO: Havent' implemented.
    int rotate(){};
};

class TransformationMatrix{
public:
    TransformationMatrix(){
        for (int i=0;i<4;i++) t[i][i]=1;
    }
    GLdouble t[4][4]{0}; //new way of initializing
};