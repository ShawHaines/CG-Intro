#pragma once
// TODO: use universal data type like GLint
#include <list>

#include "geometry.h"

class Orbit {
   public:
    Orbit(double r, double nx = 0, double ny = -1, double nz = 0);
    double radius;
    // center of the orbit.
    Point center;
    // normal vector
    Vector normal;
    int display();
    int setColor(double r, double g, double b, double a);

   private:
    GLdouble color[4];
};

class Astroid {
   public:
    Astroid(double r, double orbitR, double year = 100, double day = 1,
            double nx = 0, double ny = -1, double nz = 0);
    Astroid(double r, double year, double day, const Orbit& orbit);
    double radius;
    Orbit orbit;
    /**
     * displays the astroids in recursive manner.
     * You only have to call the sun.display().
     * */
    int display();
    // calculates revolution also in recursive manner.
    int revolution();
    int setColor(double r, double g, double b, double a);
    // list of its satellites.
    std::list<Astroid*> satellites;
    bool emission;
    GLuint texture;

   private:
    GLdouble color[4];
    // revolution period, unit is second.
    double year;
    // the revolution angular position.
    double phi;
    // rotational period, unit is second.
    double day;
    // rotational angular position.
    double psi;
};