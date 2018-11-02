#include "polyplane.hpp"

/*
 * (0,0)    (1,0)
 *   0---1---2
 *   \   \   \
 *   |\  |\  |
 *   | \ | \ |
 *   |  \|  \|
 *   3---4---5
 *   \   \   \
 *   |\  |\  |
 *   | \ | \ |
 *   |  \|  \|
 *   6---7---8
 *   \   \   \
 *   |\  |\  |
 *   | \ | \ |
 *   |  \|  \|
 *   9--10--11
 * (0,1)   (1,1)
 *
 */

#include <iostream>
using namespace std;

PolyPlane::PolyPlane(int32_t nofVerticesX, int32_t nofVerticesY)
{
    if (nofVerticesX < 2 || nofVerticesY < 2)
    {
        cout << "Number of vertices in the X and Y direction must be greater than 1." << endl;
        return;
    }
    
    int32_t nofVertices = nofVerticesX * nofVerticesY;
    numVertices = nofVertices;
    /**
     * 1. How many triangles are in a nofVerticesX * nofVerticesY mesh?
     */
    int32_t nofTriangles = (nofVerticesX - 1) * 2 * (nofVerticesY - 1);
    numTriangles = nofTriangles;
    
    vertices = new Vertex[nofVertices];
    indices = new Triangle[nofTriangles];
    
    /**
     * 2. Generate a list of vertices with coordinates in the interval (0, 0) to (1, 1). (see drawing above)
     */
    for (int32_t y = 0; y < nofVerticesY; ++y)
    {
        for(int32_t x = 0; x < nofVerticesX; ++x)
        {
            int32_t index = nofVerticesX * y + x;
            
            Vertex vertex;
            // Normalize the x and y coordinate and set it as the respective vertex position
            vertex.x = (float)x/(float)(nofVerticesX - 1);
            vertex.y = (float)y/(float)(nofVerticesY - 1);
            vertex.z = 0.0f;
            vertices[index] = vertex;
        }
    }    
    
    /**
     * 3. Generate indices to draw triangles in clockwise order. e.g. (0,1,4),(0,4,3),(1,2,5),(1,5,4),...
     */
    
    // Step through the vertex grid and build 2 triangles per cell
    int triIndex = 0;
    for (int32_t y = 0; y < nofVerticesY - 1; ++y)
    {
        for (int32_t x = 0; x < nofVerticesX - 1; ++x)
        {
            int32_t indexOfVert = nofVerticesX * y + x;
            // build 2 triangles with vert index arranged in clockwise order
            indices[triIndex].a = indexOfVert;
            indices[triIndex].b = indexOfVert + 1;
            indices[triIndex].c = indexOfVert + nofVerticesX + 1;
            indices[triIndex + 1].a = indexOfVert;
            indices[triIndex + 1].b = indexOfVert + nofVerticesX + 1;
            indices[triIndex + 1].c = indexOfVert + nofVerticesX;
            triIndex += 2;
        }
    }
    
//    //Output
//    for (int i = 0; i < nofVertices; i++)
//    {
//        Vertex v = vertices[i];
//        std::cout << "(" << v.x << "," << v.y << ") ";
//        if(i % nofVerticesX == (nofVerticesX - 1))
//        {
//            std::cout << std::endl;
//        }
//    }
//    
//    cout << endl;
//    
//    for (int i = 0; i < nofTriangles; i++)
//    {
//        Triangle triangle = indices[i];
//        std::cout << "[" << triangle.a << " " << triangle.b << " " << triangle.c << "] ";
//        if((i) % nofVerticesX == (nofVerticesX - 1))
//        {
//            std::cout << std::endl;
//        }
//    }
//    
//    cout << endl;
}

PolyPlane::~PolyPlane()
{
    delete[] vertices;
    delete[] indices;
}
