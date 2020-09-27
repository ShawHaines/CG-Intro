#include "ellipse.h"
// #define _USE_MATH_DEFINES
#include <cmath>


Polygon ellipse(const double a, const double b,const Point& center,
                                             const double theta) {
    double cosine = std::cos(theta), sine = std::sin(theta);
    double R[4] = {cosine, -sine, sine, cosine};
    const int SLICES = 100;
    const double PI = 3.14159265358979323846264338327950288,dphi = PI / SLICES;
    
    cosine = std::cos(dphi);
    sine = std::sin(dphi);
    double A[4] = {cosine,-a/b*sine,b/a*sine,cosine},M[4];
    // Matrix Multiplication. B=R A (R.T)
    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++){
            M[i*2+j]=0;
            for (int k=0;k<2;k++)
                for (int l=0;l<2;l++)
                    M[i*2+j]+=R[i*2+l]*A[l*2+k]*R[j*2+k];
        }

    Polygon points;
    points.reserve(SLICES);

    double x=a*R[0],y=a*R[2];
    points.push_back(Point(x,y)+center);
    for (double phi=0;phi<2*PI;phi+=dphi){
        x=M[0]*x+M[1]*y;
        y=M[2]*x+M[3]*y;
        points.push_back(Point(x,y)+center);
    }
    return points;
}