#include "geometry.h"

#include <math.h>

double dot(const Vector& v1, const Vector& v2) {
    double sum = 0;
    for (int i = 0; i < 3; i++) sum += v1.end[i] * v2.end[i];
    return sum;
}
double Vector::dot(const Vector& v) const { return ::dot(*this, v); }

double Vector::norm() const { return sqrt(this->dot(*this)); }
double norm(const Vector& v) { return v.norm(); }

bool Vector::isZero() {
    // const double eps = 1e-9;
    if (norm() < 1e-9)
        return true;
    else
        return false;
}

Vector cross(const Vector& v1, const Vector& v2) {
    double x, y, z;
    x = v1.end[1] * v2.end[2] - v1.end[2] * v2.end[1];
    y = v1.end[2] * v2.end[0] - v1.end[0] * v2.end[2];
    z = v1.end[0] * v2.end[1] - v1.end[1] * v2.end[0];
    return Vector(x, y, z);
}

Vector& Vector::normalized(){
    this->normalize();
    return (*this);
}

int Vector::normalize() {
    if (isZero()) return 0;
    double length = norm();
    for (int i = 0; i < 3; i++) end[i] = end[i] / length;
    return 0;
}
// operator implementation.
const GLdouble& Vector::operator[](int i) const { return this->end[i]; }
GLdouble& Vector::operator[](int i) { return this->end[i]; }
Vector Vector::operator-() const {
    return Vector(-(*this)[0], -(*this)[1], -(*this)[2]);
}
Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
Vector operator-(const Vector& v1, const Vector& v2) { return v1 + (-v2); }
Vector operator*(const GLdouble x, const Vector& v) {
    return Vector(x * v[0], x * v[1], x * v[2]);
}
Vector operator*(const Vector& v, const GLdouble x) { return x * v; }