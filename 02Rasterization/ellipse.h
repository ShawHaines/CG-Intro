#pragma once
#include <vector>

#include "Geometry.h"
// #include <utility>
/** draw an outline of an ellipse with given half axis length a and b
 * respectively, theta is the angle between its longer axis and x axis in
 * radians. Returns: a list of integer points as its polygonal approximate.
 * */
Polygon ellipse(const double a, const double b, const Point& center,
                const double theta = 0);
