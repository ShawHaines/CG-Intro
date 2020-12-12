#pragma once
#include <GL/freeglut.h>
#include "geometry.h"
#include <vector>
#include <list>

// TODO: Wrap them up in OOP style. Add some properties such as color, normal, etc.

// stores the coordinates.
typedef Point Vertex;

class Node;
class Mesh;

typedef Node* pNode;
typedef Mesh* pMesh;
typedef Vertex* pVertex;
// stores the index of points.
class Face:public std::list<pVertex>{
public:
    Face(){};
    int display()const;
};

class Mesh{
public:
    Mesh(){};
    // vertex list, allows random access.
    std::vector<Vertex> v;
    // face list, 
    std::list<Face> f;
    // display in OpenGL viewport.
    int display() const;
    // write into obj format into some file. TODO: Haven't implemented
    int output() const{return 0;}
    // returns the number of vertices.
    int vertexSize() const;
    // returns the number of faces.
    int faceSize() const;
private:
};

// forms a tree structure.
class Node {
   public:
    Node(){};
    pNode parent = NULL;
    std::list<pNode> children;
    pMesh mesh = NULL;

   private:
    // tranformation matrix from the parent node
    TransformationMatrix T;
};