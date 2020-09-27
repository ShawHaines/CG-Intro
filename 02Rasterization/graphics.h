#pragma once
#include <vector>
// #include <string>
#include "Geometry.h"

class Color {
public:
    Color(unsigned char _r = 255, unsigned char _g = 255, unsigned char _b = 255)
        : r(_r), g(_g), b(_b) {};
    int r, g, b;
};

class Canvas {
   public:
    Canvas(int w, int h);
    ~Canvas();
    int Width, Height;
    /**
     * Draw a straight line using Bresenham's Algorithm.
     * */
    int drawLine(const Point& start, const Point& end);
    /**
     * Draw the oulines of a sequence of points.
     * Pixels are expressed as an array.
     * */
    int drawOutline(const Polygon& points);
    int fillPolygon(const Polygon& points);
    /**
     * save the picture as fileName.
     * */
    int show(const char* fileName="a.ppm");
   private:
    /**
     * TODO:
     * try using the smart pointers and avoid memory leakage.
     * */
    unsigned char* data;
    int scatter(const Point& p, const Color& color=Color(255,255,255));
    /**
     * draw the vector from (0,0) to p
     * Returns a list of pixels that need to be visited. 
     * */
    std::vector<Point> drawVector(const Point& p);
};

// int drawOutline(Canvas& canvas;const std::vector<Point>& points);