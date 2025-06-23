//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Generic Vector Template (cpp)
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
#include "GenericVectorTemplate.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Constructors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// @brief Default constructor: Initializes all components to zero
template <int N, typename T>
Vector<N, T>::Vector()
{
    m_components.fill((T)0);
}

// @brief Variadic template constructor: Initializes with up to N arguments
// Extra arguments are ignored, missing arguments are filled with zero.
template <int N, typename T>
template <typename... Args>
Vector<N, T>::Vector(Args... _args) 
    : m_components()
{
    const int ArgsCount = sizeof...(_args);
    static_assert(ArgsCount <= N, "Too many arguments for Vector constructor. Exceeds component dimensions.");
    std::array<T, ArgsCount> tempArgs = { static_cast<T>(_args)... };
    for (int i = 0; i < ArgsCount; ++i)
    {
        m_components[i] = tempArgs[i];
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Getters / Setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <int N, typename T>
T Vector<N, T>::GetX() const
{
    if (N < 1)
    {
        std::cerr << "Cannot `GetX`, Component Count does not meet requirements (i.e: this is not a Vector1+)" << std::endl;
        return (T)0;
    }
    return (*this)[0];
}

template <int N, typename T>
T Vector<N, T>::GetY() const
{
    if (N < 2)
    {
        std::cerr << "Cannot `GetY`, Component Count does not meet requirements (i.e: this is not a Vector2+)" << std::endl;
        return (T)0;
    }
    return (*this)[1];
}

template <int N, typename T>
T Vector<N, T>::GetZ() const
{
    if (N < 3)
    {
        std::cerr << "Cannot `GetZ`, Component Count does not meet requirements (i.e: this is not a Vector3+)" << std::endl;
        return (T)0;
    }
    return (*this)[2];
}

template <int N, typename T>
T Vector<N, T>::GetW() const
{
    if (N < 4)
    {
        std::cerr << "Cannot `GetW`, Component Count does not meet requirements (i.e: this is not a Vector4+)" << std::endl;
        return (T)0;
    }
    return (*this)[3];
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::SetX(const T& _val)
{
    if (N < 1)
    {
        std::cerr << "Cannot `SetX`, Component Count does not meet requirements (i.e: this is not a Vector1+)" << std::endl;
        return *this;
    }
    (*this)[0] = _val;
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::SetY(const T& _val)
{
    if (N < 2)
    {
        std::cerr << "Cannot `SetY`, Component Count does not meet requirements (i.e: this is not a Vector2+)" << std::endl;
        return *this;
    }
    (*this)[1] = _val;
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::SetZ(const T& _val)
{
    if (N < 3)
    {
        std::cerr << "Cannot `SetZ`, Component Count does not meet requirements (i.e: this is not a Vector3+)" << std::endl;
        return *this;
    }
    (*this)[2] = _val;
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::SetW(const T& _val)
{
    if (N < 4)
    {
        std::cerr << "Cannot `SetW`, Component Count does not meet requirements (i.e: this is not a Vector4+)" << std::endl;
        return *this;
    }
    (*this)[3] = _val;
    return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Operators
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <int N, typename T>
T& Vector<N, T>::operator [] (int _index)
{
    if (_index >= N)
    {
        throw std::out_of_range("Vector::operator []: index out of bounds");
    }
    return m_components[_index];
}


template <int N, typename T>
const T& Vector<N, T>::operator [] (int _index) const
{
    if (_index >= N)
    {
        throw std::out_of_range("Vector::operator [] : index out of bounds");
    }
    return m_components[_index];
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator + () const
{
    return *this;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator - () const
{
    Vector result;
    for (int i = 0; i < N; ++i)
    {
        result.m_components[i] = - m_components[i];
    }
    return result;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator + (const Vector& _other) const
{
    Vector result;
    for (int i = 0; i < N; ++i)
    {
        result.m_components[i] = m_components[i] + _other.m_components[i];
    }
    return result;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator - (const Vector& _other) const
{
    Vector result;
    for (int i = 0; i < N; ++i)
    {
        result.m_components[i] = m_components[i] - _other.m_components[i];
    }
    return result;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator * (T _scalar) const
{
    Vector result;
    for (int i = 0; i < N; ++i)
    {
        result.m_components[i] = m_components[i] * _scalar;
    }
    return result;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::operator / (T _scalar) const
{
    if (std::abs(_scalar) < EPSILON)
    {
        std::cerr << "Vector::operator / (): Division by zero." << std::endl;
        return Vector(); // Return Vector.Zero
    }

    Vector result;
    for (int i = 0; i < N; ++i)
    {
        result.m_components[i] = m_components[i] / _scalar;
    }
    return result;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::operator += (const Vector& _other)
{
    for (int i = 0; i < N; ++i)
    {
        m_components[i] += _other.m_components[i];
    }
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::operator -= (const Vector& _other)
{
    for (int i = 0; i < N; ++i)
    {
        m_components[i] -= _other.m_components[i];
    }
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::operator *= (T _scalar)
{
    for (int i = 0; i < N; ++i)
    {
        m_components[i] *= _scalar;
    }
    return *this;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::operator /= (T _scalar)
{
    if (std::abs(_scalar) < EPSILON)
    {
        std::cerr << "Vector::operator /= (): Division by zero." << std::endl;
        return *this;
    }
    for (int i = 0; i < N; ++i)
    {
        m_components[i] /= _scalar;
    }
    return *this;
}

template <int N, typename T>
bool Vector<N, T>::operator == (const Vector& _other) const
{
    for (int i = 0; i < N; ++i)
    {
        if (std::abs(m_components[i] - _other.m_components[i]) > 0.0f)
        {
            return false;
        }
    }
    return true;
}

template <int N, typename T>
bool Vector<N, T>::operator != (const Vector& _other) const
{
    return (*this == _other) == false;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Vector Functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <int N, typename T>
T Vector<N, T>::Dot(const Vector& _other) const
{
    T sum = (T)0;
    for (int i = 0; i < N; ++i)
    {
        sum += m_components[i] * _other.m_components[i];
    }
    return sum;
}

template <int N, typename T>
T Vector<N, T>::Magnitude() const
{
    T magSqr = MagnitudeSqr();
    T mag = static_cast<T>( std::sqrt(magSqr) );
    return mag;
}

template <int N, typename T>
T Vector<N, T>::MagnitudeSqr() const
{
    T magSqr = (T)0;
    for (int i = 0; i < N; ++i)
    {
        magSqr += m_components[i] * m_components[i];
    }
    return magSqr;
}

template <int N, typename T>
Vector<N, T>& Vector<N, T>::Normalise()
{
    T mag = Magnitude();
    if (std::abs(mag) < EPSILON)
    {
        return *this; // Vector.zero
    }
    return *this /= mag;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::Normalised() const
{
    T mag = Magnitude();
    if (std::abs(mag) < EPSILON)
    {
        return Vector(); // Vector.Zero
    }
    return *this / mag;
}

template <int N, typename T>
Vector<N, T> Vector<N, T>::Cross(const Vector<N, T>& _other) const
{
    // Can't use static_assert as it prevents compilation outside of this cpp file.
    // Instead throw an error when invoked outside of a 3D Vector
    throw std::exception("Cross product can only be invoked on Vector3 handlers (Both LHS & RHS)");
    return Vector<N, T>();
}

// My compiler is not playing nice with a generic `template <typename T>` so I need to overload it like this instead...
Vector<3, float> Vector<3, float>::Cross(const Vector<3, float>& _other) const
{
    return Vector<3, float>(m_components[1] * _other.m_components[2] - m_components[2] * _other.m_components[1],
                            m_components[2] * _other.m_components[0] - m_components[0] * _other.m_components[2],
                            m_components[0] * _other.m_components[1] - m_components[1] * _other.m_components[0]);
}

Vector<3, double> Vector<3, double>::Cross(const Vector<3, double>& _other) const
{
    return Vector<3, double>(m_components[1] * _other.m_components[2] - m_components[2] * _other.m_components[1],
                             m_components[2] * _other.m_components[0] - m_components[0] * _other.m_components[2],
                             m_components[0] * _other.m_components[1] - m_components[1] * _other.m_components[0]);
}

Vector<3, int> Vector<3, int>::Cross(const Vector<3, int>& _other) const
{
    return Vector<3, int>(m_components[1] * _other.m_components[2] - m_components[2] * _other.m_components[1],
                          m_components[2] * _other.m_components[0] - m_components[0] * _other.m_components[2],
                          m_components[0] * _other.m_components[1] - m_components[1] * _other.m_components[0]);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Global Operators
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <int N, typename T>
std::ostream& operator << (std::ostream& _os, const Vector<N, T>& _vec)
{
    _os << "(";
    for (size_t i = 0; i < N; ++i)
    {
        _os << _vec.m_components[i];
        if (i < (N - 1))
        {
            _os << ", ";
        }
    }
    _os << ")";
    return _os;
}



// Disable Warning 'No suitable definition provided for explicit template instantiation request.' This is intentional
#pragma warning ( push )
#pragma warning ( disable : 4661 )
template class Vector<1, float>;
template class Vector<2, float>;
template class Vector<3, float>;
template class Vector<4, float>;
template class Vector<1, double>;
template class Vector<2, double>;
template class Vector<3, double>;
template class Vector<4, double>;
template class Vector<1, int>;
template class Vector<2, int>;
template class Vector<3, int>;
template class Vector<4, int>;
#pragma warning ( pop )