## Rasterization

Scan Converting an ellipse.

![](./test.ppm)

### Installation

1. Open `Ellipse.sln` in Visual Studio and Generate.
2. Run `Ellipse.exe`.

### Program Input Parameters

`a b cx cy theta`

the sample image's parameter combination is
`150 100 200 150 0.1`

### Code Interface
```C++
// generate a polygon approximation of an ellipse.
Polygon ellipse(const double a, const double b, const Point& center, const double theta=0)
//plot the polygon.
Canvas::drawOutline(const Polygon& polygon)
```
