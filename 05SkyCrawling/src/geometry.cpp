#include "geometry.h"

double dot(const Vector& v1, const Vector& v2) {
    double sum = 0;
    for (int i = 0; i < 3; i++) sum += v1.end[i] * v2.end[i];
    return sum;
}
double Vector::dot(const Vector& v) const { return ::dot(*this, v); }

double Vector::norm() const { return this->dot(*this); }
double norm(const Vector& v) { return v.norm(); }

bool Vector::isZero(){
    // const double eps = 1e-9;
    if (norm() < 1e-9) return true;
        else return false;
}

Vector cross(const Vector& v1, const Vector& v2) {
    double x, y, z;
    x = v1.end[1] * v2.end[2] - v1.end[2] * v2.end[1];
    y = v2.end[0] * v2.end[2] - v1.end[2] * v2.end[0];
    z = v1.end[0] * v2.end[1] - v1.end[1] * v2.end[0];
    return Vector(x, y, z);
}

int Vector::normalize() {
    if (isZero()) return 0;
    double length = norm();
    for (int i = 0; i < 3; i++) end[i] /= length;
    return 0;
}