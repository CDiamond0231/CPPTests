//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Vector3 (h)
//             Author: Christopher A
//             Date: June 17, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Please implement the standard functionality required from a 3 element 
//      vector for a math library. The design should be object oriented and 
//      protect its data members from public access. Please support simple 
//      operations on the vector such as addition, subtraction, multiplication 
//      and division as well as dot and cross product.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef __VECTOR3_H_
#define __VECTOR3_H_


#ifndef EPSILON
#define EPSILON 0.0000001
#endif


#include <iostream>



class Vector3
{
public:
    Vector3();
    Vector3(float _x, float _y);
    Vector3(float _x, float _y, float _z);

    float GetX() const;
    float GetY() const;
    float GetZ() const;
    const Vector3& SetX(float _x);
    const Vector3& SetY(float _y);
    const Vector3& SetZ(float _z);

    float Dot(const Vector3& _other) const;
    Vector3 Cross(const Vector3& _other) const;
    float Magnitude() const;
    float MagnitudeSqr() const;
    const Vector3& Normalise();
    Vector3 Normalised() const;

    // ~~~ Operators ~~~
    Vector3 operator + () const;
    Vector3 operator - () const;
    Vector3 operator + (const Vector3& _other) const;
    Vector3 operator - (const Vector3& _other) const;
    Vector3 operator * (float _scalar) const;
    Vector3 operator / (float _scalar) const;
    Vector3& operator += (const Vector3& _other);
    Vector3& operator -= (const Vector3& _other);
    Vector3& operator *= (float _scalar);
    Vector3& operator /= (float _scalar);
    bool operator == (const Vector3& _other) const;
    bool operator != (const Vector3& _other) const;
    Vector3 operator * (float _scalar);


private:
    float m_x;
    float m_y;
    float m_z;
};


// Stream insertion operator for printing Vector3
std::ostream& operator << (std::ostream& _os, const Vector3& _vec);


#endif  //  __VECTOR3_H_