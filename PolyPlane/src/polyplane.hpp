#ifndef polyplane_hpp
#define polyplane_hpp

#include <stdio.h>

struct Vertex {
    Vertex() = default;
    Vertex(float _x, float _y) : x(_x), y(_y) {};
    
    float x;
    float y;
    float z;
};

struct Triangle {
    Triangle() = default;
    Triangle(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};
    
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

class PolyPlane
{
public:
    PolyPlane(int nofVerticesX, int nofVerticesY); // constructor
    ~PolyPlane(); //destructor
    Vertex *vertices;
    Triangle *indices;
    int numVertices;
    int numTriangles;
};
#endif
