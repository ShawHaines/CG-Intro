#pragma once
#include <GL/freeglut.h>
#include <vector>

class Point: public std::vector<GLdouble>{
public:
    Point(GLdouble x=0,GLdouble y=0, GLdouble z=0):Point::vector(3){
        (*this)[0]=x;
        (*this)[1]=y;
        (*this)[2]=z;
    };
};

class Vector{
   public:
    Point end;
    // default is a unit vector, just to avoid 0 norm.
    Vector(GLdouble x=0, GLdouble y=0, GLdouble z=1):end(x,y,z){};
    Vector(Point& p):end(p){};

    const GLdouble& operator[](int i) const;
    GLdouble& operator[](int i);
    
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