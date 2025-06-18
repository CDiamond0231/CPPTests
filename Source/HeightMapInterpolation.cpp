//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Height Map Interpolation (cpp)
//             Author: Christopher A
//             Date: June 18, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Given that you have a 2 dimensional array of height values (say 10x10)
//		that represent a height field. Assume that the distance between each
//		height point in X and Y is 1 and that from the grid we form a
//		triangulated mesh such that for each set of 4 grid points
//		A=(x,y), B=(x+1,y) C=(x+1,y+1), and D=(x,y+1)
//		
//		There are two triangles ABC and ACD (so they are seperated by the line
//		x=y in the local coordinate system of the grid). Explain how you would
//		find the *exact* height of an arbitrary point x,y on this mesh.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <iostream>
#include <vector>
#include "Vector3.h"


float GetHeightAtPoint(const std::vector<std::vector<float>>& _heightMap, float _x, float _y)
{
    if (_heightMap.empty() || _heightMap[0].empty())
    {
        std::cerr << "Error: height_map is empty." << std::endl;
        return -1.0f;
    }

    size_t num_cols = _heightMap.size();
    size_t num_rows = _heightMap[0].size();

    // Checking we're within bounds
    if (_x < 0.0f || _x >= (num_cols - 1)
        || _y < 0.0f || _y >= (num_rows - 1))
    {
        std::cerr << "Query point (" << _x << ", " << _y << ") is outside mesh boundaries." << std::endl;
        return -1.0f;
    }

    // 1. Retrieve the Vector3 coordinates of the four corners of the cell from 'height_map' :
    //     - First floor X & Y to get bounds : int floorX, floorY = (int)x, (int)y
    //     - Vector3 vA = (floorX, floorY, height_map[floorX, floorY])
    //     - Vector3 vB = (floorX + 1, floorY, height_map[floorX + 1, floorY])
    //     - Vector3 vC = (floorX + 1, floorY + 1, height_map[floorX + 1, floorY + 1])
    //     - Vector3 vD = (floorX, floorY + 1, height_map[floorX, floorY + 1])
    // I am assuming grid is bound to whole units per edge, thus we are flooring x & y to get the bound points.
    // e.g: xy(1.5f, 2.75f) gives bounds of (1, 2, 2, 3)
    int flooredX = (int)_x;
    int flooredY = (int)_y;
    Vector3 vA(flooredX,      flooredY,     _heightMap[flooredX][flooredY]);
    Vector3 vB(flooredX + 1,  flooredY,     _heightMap[flooredX][flooredY + 1]);
    Vector3 vC(flooredX + 1,  flooredY + 1, _heightMap[flooredX + 1][flooredY + 1]);
    Vector3 vD(flooredX,      flooredY + 1, _heightMap[flooredX + 1][flooredY]);


    // 2. Calculate the point's local coordinates within the cell.
    //     - float normX = x - floorX;
    //     - float normY = y - floorY;
    //     - If y <= x: The point is within Triangle vA, vB, vC
    //     - Else: The point is within Triangle vA, vC, vD
    //     - Hereafter referred to as p1, p2, p3 (point 1, 2, 3) respectively
    Vector3 p1, p2, p3;
    float normX = _x - flooredX;
    float normY = _y - flooredY;
    if (normY <= normX)
    {
        p1 = vA;
        p2 = vB;
        p3 = vC;
    }
    else 
    {
        p1 = vA;
        p2 = vC;
        p3 = vD;
    }


    // 3. Planar Interpolation :
    //     - Calculate the plane's normal vector
    //         - Vector3 normal = (p2 - p1) X (p3 – p1)
    //     - Calculate the plane equation constant :
    //         - Float scalar = −(normal.x * p1.x + normal.y * p1.y + normal.z * p1.z)
    //         - Error Condition : normal.z == 0 ? “Triangle is vertical”
    //     - Float heightResult : = -(normal.x * x + normal.y * y + scalar) / normal.z
    Vector3 edge1 = p2 - p1;
    Vector3 edge2 = p3 - p1;
    Vector3 normal = edge1.Cross(edge2);

    if (std::abs(normal.GetZ()) < EPSILON)
    {
        std::cerr << "Triangle is vertical with given points (" << _x << ", " << _y << ")." << std::endl;
        return -1.0f;
    }

    float scalar = -(normal.GetX() * p1.GetX() + normal.GetY() * p1.GetY() + normal.GetZ() * p1.GetZ());
    float heightResult = -(normal.GetX() * _x + normal.GetY() * _y + scalar) / normal.GetZ();
    return heightResult;
}
