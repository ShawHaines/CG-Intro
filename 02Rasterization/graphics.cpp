#include "graphics.h"
#include <iostream>
#include <algorithm>
#include <string.h>

Canvas::Canvas(int w, int h) : Width(w), Height(h) {
    data = new unsigned char[Width * Height * 3];
    memset(data,0,sizeof(unsigned char)*Width*Height*3);
}

Canvas::~Canvas() { delete[] data; }

int Canvas::drawLine(const Point& start, const Point& end) {
    // TODO: minimize the space usage in drawVector()
    // make sure start is on the left side of right.
    if (start.x > end.x) return drawLine(end, start);
    auto l = drawVector(end - start);
    for (auto p : l) scatter(p + start);
    return 0;
}

int Canvas::drawOutline(const std::vector<Point>& points) {
    for (auto i = points.begin() + 1; i != points.end(); i++)
        this->drawLine(*(i - 1), *i);
    this->drawLine(points.back(), points.front());
    return 0;
}

int Canvas::fillPolygon(const std::vector<Point>& points) {
    int minIndex = 0, maxIndex = 0;
    for (auto i = points.begin(); i != points.end(); i++) {
        if (points[minIndex].y > i->y) minIndex = i - points.begin();
        if (points[maxIndex].y < i->y) maxIndex = i - points.begin();
    }

    return 0;
}

std::vector<Point> Canvas::drawVector(const Point& p) {
    // special case dealing, ensure they are in the first octant.
    if (p.y < 0) {
        auto l = drawVector(Point(p.x, -p.y));
        for (auto& each : l) each.y = -each.y;
        return l;
    }
    if (p.y > p.x) {  // slope is bigger than 1.
        auto l = drawVector(Point(p.y, p.x));
        for (auto& each : l) std::swap(each.x, each.y);
        return l;
    }
    std::vector<Point> l;
    l.reserve(p.x + 1);
    if (p.y == 0) {  // horizontal line
        for (int x = 0; x <= p.y; x++) l.push_back(Point(x, 0));
        return l;
    }
    int dx = p.x, dy = p.y, P = 2 * dy - dx;
    l.push_back(Point(0, 0));
    for (int x = 1, y = 0; x <= dx; x++) {
        if (P > 0) {
            y += 1;
            P = P + dy << 1 - dx << 1;
        } else
            P = P + dy << 1;
        l.push_back(Point(x, y));
    }
    return l;
}

// -----------------private functions---------------------

int Canvas::scatter(const Point& p, const Color& color) {
    // be careful about a boundary check!
    if (p.x>=Width||p.x<0||p.y<0||p.y>=Height)
        return 0;
    int i = (p.y*Width+p.x) * 3;
    data[i] = color.r;
    data[i + 1] = color.g;
    data[i + 2] = color.b;
    return 0;
}

int Canvas::show(const char* fileName) {
    FILE* fp;
    fp = fopen(fileName, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", Width, Height);
    fwrite(data, Width*Height*3, 1, fp);
    fclose(fp);
    return 0;
}