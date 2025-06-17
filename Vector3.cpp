//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Vector3 (cpp)
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
#include <iostream>
#include "Vector3.h"


#define EPSILON 0.0000001


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Public
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector3::Vector3()
    : m_x(0.0f), m_y(0.0f), m_z(0.0f)
{
}

Vector3::Vector3(float _x, float _y, float _z)
    : m_x(_x), m_y(_y), m_z(_z)
{
}


float Vector3::GetX() const
{
    return m_x;
}

float Vector3::GetY() const
{
    return m_y;
}

float Vector3::GetZ() const
{
    return m_z;
}

const Vector3& Vector3::SetX(float _x)
{
    m_x = _x;
    return *this;
}

const Vector3& Vector3::SetY(float _y)
{
    m_y = _y;
    return *this;
}

const Vector3& Vector3::SetZ(float _z)
{
    m_z = _z;
    return *this;
}

float Vector3::Dot(const Vector3& _other) const
{
    return m_x * _other.m_x + m_y * _other.m_y + m_z * _other.m_z;
}

Vector3 Vector3::Cross(const Vector3& _other) const
{
    return Vector3(m_y * _other.m_z - m_z * _other.m_y,
                    m_z * _other.m_x - m_x * _other.m_z,
                    m_x * _other.m_y - m_y * _other.m_x);
}

float Vector3::Magnitude() const
{
    return std::sqrt( MagnitudeSqr() );
}

float Vector3::MagnitudeSqr() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

const Vector3& Vector3::Normalise()
{
    float mag = Magnitude();
    return *this /= mag;
}

Vector3 Vector3::Normalised() const
{
    float mag = Magnitude();
    if (std::abs(mag) < EPSILON)
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
    return *this / mag;
}


// --- Operators ---
Vector3 Vector3::operator + () const 
{
    return *this;
}

Vector3 Vector3::operator - () const
{
    return Vector3(-m_x, -m_y, -m_z);
}

Vector3 Vector3::operator + (const Vector3& _other) const
{
    return Vector3(m_x + _other.m_x, m_y + _other.m_y, m_z + _other.m_z);
}

Vector3 Vector3::operator - (const Vector3& _other) const
{
    return Vector3(m_x - _other.m_x, m_y - _other.m_y, m_z - _other.m_z);
}

Vector3 Vector3::operator * (float _scalar) const
{
    return Vector3(m_x * _scalar, m_y * _scalar, m_z * _scalar);
}

Vector3 Vector3::operator / (float _scalar) const
{
    if (std::abs(_scalar) < EPSILON)
    {
        std::cerr << "Attempted division by zero\n";
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    return Vector3(m_x / _scalar, m_y / _scalar, m_z / _scalar);
}

Vector3& Vector3::operator += (const Vector3& _other)
{
    m_x += _other.m_x;
    m_y += _other.m_y;
    m_z += _other.m_z;
    return *this;
}

Vector3& Vector3::operator -= (const Vector3& _other)
{
    m_x -= _other.m_x;
    m_y -= _other.m_y;
    m_z -= _other.m_z;
    return *this;
}

Vector3& Vector3::operator *= (float _scalar)
{
    m_x *= _scalar;
    m_y *= _scalar;
    m_z *= _scalar;
    return *this;
}

Vector3& Vector3::operator /= (float _scalar)
{
    if (std::abs(_scalar) < EPSILON)
    {
        std::cerr << "Attempted division by zero\n";
        return *this;
    }

    m_x /= _scalar;
    m_y /= _scalar;
    m_z /= _scalar;
    return *this;
}

bool Vector3::operator == (const Vector3& _other) const
{
    return std::abs(m_x - _other.m_x) < EPSILON
        && std::abs(m_y - _other.m_y) < EPSILON
        && std::abs(m_z - _other.m_z) < EPSILON;
}

bool Vector3::operator != (const Vector3& _other) const
{
    return (*this == _other) == false;
}

Vector3 Vector3::operator * (float _scalar)
{
    return Vector3(m_x * _scalar, m_y * _scalar, m_z * _scalar);
}