//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Generic Vector Template (h)
//             Author: Christopher A
//             Date: June 22, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Building upon the Vector3 class that we created previously, implement a 
//      generic (also called ‘templated’) Vector class that can represent a vector
//      in any N-dimensional space. In addition, the type values of xyzw should be
//      assignable to any primitive type as part of the generic implementation.
// 
//      For Example:
//      - Vector2Int    -> Vector<2, int>    (x & y values are both typeof(int))
//      - Vector3Double -> Vector<3, double> (xyz values are typeof(double))
//      - Vector4Float  -> Vector<4, float>  (xyzw values are typeof(float))
//      
//      The dimension N should be a template parameter. It should support:
//      - A constructor that takes N components. Example:
//          - Vector<2, float> vec2Float(1.0f, 2.0f);
//          - Vector<2> vec2Int(3, 4);
//              - Value types(x & y) are typeof(int) despite not being explicitly 
//                assigned due to both parameters being typeof(int)
//      - Default construction to a zero vector.
//      - Basic element access(e.g. operator []).
//      - Vector addition(operator +).
//      - Vector subtraction(operator -).
//      - Scalar multiplication(operator *).
//      - Magnitude()
//      - MagnitudeSqr()
//      - Normalised()
//      - Dot product(Dot()).
//      - Cross product for 3D specifically, using template specialisation or static_assert.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef EPSILON
#define EPSILON 0.0000001
#endif

#include <iostream>
#include <array>


template <int N, typename T = float>
class Vector;


// Stream insertion operator for printing Vector3; forward declaration for 'friend' keyword later.
template <int N, typename T>
std::ostream& operator << (std::ostream& _os, const Vector<N, T>& _vec);



template <int N, typename T>
class Vector 
{
public:

    // @brief Default constructor: Initializes all components to zero
    Vector();

    // @brief Variadic template constructor: Initializes with up to N arguments
    // Extra arguments are ignored, missing arguments are filled with zero.
    template <typename... Args>
    explicit Vector(Args... _args);

    T GetX() const;
    T GetY() const;
    T GetZ() const;
    T GetW() const;

    Vector& SetX(const T& _val);
    Vector& SetY(const T& _val);
    Vector& SetZ(const T& _val);
    Vector& SetW(const T& _val);

    // ~~~ Operators ~~~
    T& operator [] (int _index);
    const T& operator [] (int _index) const;

    Vector operator + () const;
    Vector operator - () const;

    Vector operator + (const Vector& _other) const;
    Vector operator - (const Vector& _other) const;

    Vector operator * (T _scalar) const;
    Vector operator / (T _scalar) const;

    Vector& operator += (const Vector& _other);
    Vector& operator -= (const Vector& _other);
    Vector& operator *= (T _scalar);
    Vector& operator /= (T _scalar);

    bool operator == (const Vector& _other) const;
    bool operator != (const Vector& _other) const;

    // ~~~ Vector Functions ~~~
    T Dot(const Vector& _other) const;
    T Magnitude() const;
    T MagnitudeSqr() const;
    Vector& Normalise();
    Vector Normalised() const;
    Vector<N, T> Cross(const Vector<N, T>& _other) const;

    // ~~~ Friend Declarations for Global Operators ~~~
    template <int M, typename U>
    friend std::ostream& operator << (std::ostream& _os, const Vector<M, U>& _vec);


private:
    std::array<T, N> m_components;
};

