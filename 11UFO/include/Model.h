#pragma once
#include <GL/freeglut.h>
#include "geometry.h"
#include <vector>
#include <list>
#include <memory>

// stores the coordinates.
// TODO: Add some properties such as color, etc.
typedef Point Vertex;

class Node;
class Mesh;

typedef std::shared_ptr<Node> pNode;
typedef std::shared_ptr<Mesh> pMesh;
typedef std::shared_ptr<Vertex> pVertex;

// stores the shared pointer of points.
class Face:public std::list<pVertex>{
public:
    // Face():Face::list(){};
    using list::list;
    // automatically calculate the normalized normal vector based on 3 points. 
    int update();
    // returns a reference so that the work can be passed on in a concise grammar.
    Face& updated();
    int display()const;
    // overloaded push_back so that we don't have to write shared_ptr.
    void push_back(const Vertex& v);
    using list::push_back; // I like this grammar!
private:
    Vector normal;
};

class Mesh{
public:
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