#pragma once
// TODO: use universal data type like GLint
#include <list>
#include "geometry.h"

class Orbit{
public:
    Orbit(double r,double nx=0,double ny=-1,double nz=0);
    double radius;
    // center of the orbit.
    Point center;
    // normal vector
    Vector normal;
    int display();
private:
    GLdouble color[4];
};

class Astroid{
public:
    Astroid(double r,double orbitR,double period=100);
    double radius;
    Orbit orbit;
    /**
     * displays the astroids in recursive manner.
     * You only have to call the sun.display().
     * */
    int display();
    // calculates revolution also in recursive manner.
    int revolution();
    // list of its satellites.
    std::list<Astroid*> satellites;
    // TODO: Add rotation. For now we omit the rotation axis.
private:
    GLdouble color[4];
    // revolution period, unit is second.
    double period;
    // the anglular position.
    double phi;
};