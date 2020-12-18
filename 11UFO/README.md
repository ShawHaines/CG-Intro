# UFO

## Requirements

* Program using 2 modeling techniques in today’s class to uild the shape of your dream car, namely
  * Surface Modeling
    - Parametric Surfaces
    - Polygonal Meshes
  * Advanced Geometric Modeling
    - Constructive Solid Geometry
    - Grammar-Based
      * L-system
      * Shape Grammar
    - Subdivision
    - Sweeping
* Compare the strengths and weaknesses of the techniques you use.
* Render your car in the same viewer as in the solar system assignment.
* No appearance specification needed, just the shape.
* Bonus (10%):
    - Use 3 modeling techniques

## Install

run the .exe file in the directory, or use CMake to build.

## Conclusion

使用了2种对象表达方法，分别是
* Polygonal Meshes
* Sweeping.

### Polygonal Meshes

以OOP的形式完整实现了 Face-Vertex Meshes，形式与.obj文件格式相同，并且可以使用`Mesh::output()`函数将定义的网格以.obj文件格式输出到文件。

详见[Model.h](./include/Model.h)

模型的类似球的多面体就是用多边形网格生成的。

```C++
int sphere(Mesh& target, double radius, GLint stacks, GLint slices);
```
函数位于文件 [UFO.cpp](./src/UFO.cpp)

### Sweeping

基于多边形网格，实现了简单的根据路径和多边形生成多边形网格。

图中的圆柱形、六边形薄片军事利用此方法生成。

### 优缺点比较

多边形网格
* 优点
  * 十分标准而且通用的格式，表示方法直接
  * 建模较为直观
* 缺点
  * 语法较为繁琐
  * 生成法向量的操作开销大(本项目实现了编写程序自动生成)

Sweeping
* 优点
  * 可以用模式化的方法生成大量柱状物品、薄板等常用形状。
  * 多边形形状指定较为灵活
  * 相当于在多边形网格上多了一层抽象，编写好程序后调用语法更简洁。
* 缺点
  * 曲线的Sweeping 实现较为困难
  * 描述曲线的方程对数学要求较高，不适用于复杂的曲线(如NURB)。