//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             3D Rendering Triangle List (h)
//             Author: Christopher A
//             Date: June 16, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//    Please use the C++ STL vector class to make a triangle list class, for use 
//      in 3d drawing. For each triangle please store 3 vertex positions, 3 colours, 
//      and 1 face normal.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <iostream>
#include <vector>
#include "Vector3.h"

#ifndef __3D_TRIANGLE_LIST_H_
#define __3D_TRIANGLE_LIST_H_



struct Color
{
    float r, g, b;

    Color() : r(1.0f), g(1.0f), b(1.0f) { }
    Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }
};

struct Triangle
{
    Vector3 vertices[3];
    Color colors[3];
    Vector3 faceNormal;

    Triangle()
    {
    }

    Triangle(const Vector3& _v1, const Vector3& _v2, const Vector3& _v3,
            const Color& _c1, const Color& _c2, const Color& _c3,
            const Vector3& _normal)
    {
        vertices[0] = _v1;
        vertices[1] = _v2;
        vertices[2] = _v3;
        colors[0] = _c1;
        colors[1] = _c2;
        colors[2] = _c3;
        faceNormal = _normal;
    }
};

class TriangleList
{
public:

    void AddTriangle(const Vector3& _v1, const Vector3& _v2, const Vector3& _v3,
                        const Color& _c1, const Color& _c2, const Color& _c3,
                        const Vector3& _normal)
    {
        m_triangles.emplace_back(_v1, _v2, _v3, _c1, _c2, _c3, _normal);
    }

    size_t Count() const
    {
        return m_triangles.size();
    }

    void Clear()
    {
        m_triangles.clear();
    }

    const Triangle& GetTriangle(size_t _index) const
    {
        if (_index >= m_triangles.size())
        {
            throw std::out_of_range("TriangleList::GetTriangle: index out of range");
        }
        return m_triangles[_index];
    }

private:
    std::vector<Triangle> m_triangles;
};



#endif  //  __3D_TRIANGLE_LIST_H_