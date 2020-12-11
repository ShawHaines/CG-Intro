#pragma once
#include <GL/glut.h>

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