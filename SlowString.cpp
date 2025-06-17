//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Slow String (cpp)
//             Author: Christopher A
//             Date: June 17, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//    This class recreates the std::string functionality.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <stdexcept>
#include "SlowString.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Public
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SlowString::SlowString()
    : m_data(nullptr), m_capacity(0), m_length(0)
{
    Allocate(nullptr); // Empty String
}

SlowString::SlowString(const char* _s)
    : m_data(nullptr), m_capacity(0), m_length(0)
{
    Allocate(_s);
}

SlowString::SlowString(const SlowString& _other)
    : m_data(nullptr), m_capacity(0), m_length(0)
{
    Allocate(_other.m_data);
}

SlowString::~SlowString()
{
    delete[] m_data;
    m_data = nullptr;
}


const char& SlowString::At(size_t _index) const
{
    if (_index >= m_length)
        throw std::out_of_range("SlowString::At: index out of range");

    return m_data[_index];
}

const char& SlowString::Front() const
{
    return At(0);
}

const char& SlowString::Back() const
{
    return At(m_length - 1);
}

const char* SlowString::c_str() const
{
    return m_data;
}


// --- Capacity ---
size_t SlowString::Size() const
{
    return m_length;
}

size_t SlowString::Capacity() const
{
    return m_capacity;
}

bool SlowString::IsEmpty() const
{
    return m_length == 0;
}

void SlowString::Reserve(size_t _capacity)
{
    if (_capacity < m_length + 1)
    {
        _capacity = m_length + 1; // Min: Current Length + Null Terminator
    }

    char* new_data = new char[_capacity];
    if (m_data != nullptr)
    {
        strcpy_s(new_data, _capacity, m_data);
        delete[] m_data;
    }

    m_data = new_data;
    m_capacity = _capacity;
}

// --- Modifiers ---
void SlowString::Clear()
{
    m_data[0] = '\0';
    m_length = 0;
    m_capacity = 1; // capacity for null terminator
}

SlowString& SlowString::Append(const char* _s)
{
    if (_s == nullptr || _s[0] == '\0')
    {
        return *this;
    }

    size_t sLength = std::strlen(_s);
    if (m_length + sLength + 1 > m_capacity)
    {
        Reserve(m_length + sLength + 1); // +1 Null Terminator
    }

    strcat_s(m_data, sLength, _s);
    m_length += sLength;
    return *this;
}

SlowString& SlowString::Append(const SlowString& _str)
{
    return Append(_str.m_data);
}

SlowString& SlowString::Append(char _c)
{
    char c[2];
    c[0] = _c;
    c[1] = '\0';
    return Append(c);
}

SlowString SlowString::Substring(size_t _fromIndex, size_t _characterCount) const
{
    if (_fromIndex > m_length)
    {
        throw std::out_of_range("SlowString::Substring: pos out of range");
    }

    if (_fromIndex + _characterCount > m_length || _characterCount == (size_t)(-1))
    {
        _characterCount = m_length - _fromIndex;
    }

    SlowString sub;
    sub.Reserve(_characterCount + 1);
    strncpy_s(sub.m_data, m_length - _fromIndex, m_data + _fromIndex, _characterCount);
    sub.m_data[_characterCount] = '\0';
    sub.m_length = _characterCount;
    sub.m_capacity = _characterCount + 1;
    return sub;
}

// --- Operators ---
const char& SlowString::operator [] (size_t _index) const
{
    return m_data[_index];
}

SlowString& SlowString::operator = (const SlowString& _other)
{
    if (this == &_other)
    {
        return *this;
    }

    Allocate(_other.m_data);
    return *this;
}

SlowString& SlowString::operator = (const char* _s)
{
    Allocate(_s);
    return *this;
}

SlowString& SlowString::operator += (const SlowString& _other)
{
    return Append(_other.m_data);
}

SlowString& SlowString::operator += (const char* _s)
{
    return Append(_s);
}

bool SlowString::operator == (const SlowString& _other) const
{
    return std::strcmp(m_data, _other.m_data) == 0;
}

bool SlowString::operator == (const char* _s) const
{
    return std::strcmp(m_data, _s) == 0;
}

bool SlowString::operator != (const SlowString& _other) const
{
    return std::strcmp(m_data, _other.m_data) != 0;
}

bool SlowString::operator != (const char* _s) const
{
    return std::strcmp(m_data, _s) != 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Private
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SlowString::Allocate(const char* _s)
{
    if (m_data != nullptr)
    {
        delete[] m_data;
    }

    if (_s == nullptr)
    {
        m_length = 0;
        m_capacity = 1; // For Null Terminator
        m_data = new char[m_capacity];
        m_data[0] = '\0';
    }
    else
    {
        m_length = std::strlen(_s);
        m_capacity = m_length + 1; // + 1 for Null Terminator
        m_data = new char[m_capacity];
        strcpy_s(m_data, m_capacity, _s);
    }
}