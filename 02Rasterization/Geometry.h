#pragma once
#include <vector>

class Point{
public:
    int x,y;
    Point(int _x=0,int _y=0):x(_x),y(_y){};
    Point(double _x,double _y):x(int(_x+0.5)),y(int(_y+0.5)){};
    friend Point operator+(const Point& p1,const Point& p2);
    friend Point operator-(const Point& p1, const Point& p2);
};


typedef std::vector<Point> Polygon;