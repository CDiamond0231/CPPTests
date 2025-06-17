//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Slow String (h)
//             Author: Christopher A
//             Date: June 17, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//    Please fill in the rest of the C++ 'slow_string' class written below. Try 
//      to replicate the STL string class's functionality as much as possible. 
//      This question is to test how good you are at encapsulating the C standard 
//      library functions such as strXXX. 
//
//      class slow_string
//      {
//          char* data;
//      public:
//          ...
//      }
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef     __SLOW_STRING_H_
#define     __SLOW_STRING_H_



class SlowString
{
public:
    SlowString();
    SlowString(const char* _s);
    SlowString(const SlowString& _other);
    ~SlowString();


    const char& At(size_t _index) const;
    const char& Front() const;
    const char& Back() const;
    const char* c_str() const;


    // --- Capacity ---
    size_t Size() const;
    size_t Capacity() const;
    bool IsEmpty() const;
    void Reserve(size_t _capacity);

    // --- Modifiers ---
    void Clear();

    SlowString& Append(const char* _s);
    SlowString& Append(const SlowString& _str);
    SlowString& Append(char _c);

    SlowString Substring(size_t _fromIndex = 0, size_t _characterCount = -1) const;

    // --- Operators ---
    const char& operator [] (size_t _index) const;

    SlowString& operator = (const SlowString& _other);
    SlowString& operator = (const char* _s);

    SlowString& operator += (const SlowString& _other);
    SlowString& operator += (const char* _s);

    bool operator == (const SlowString& _other) const;
    bool operator == (const char* _s) const;

    bool operator != (const SlowString& _other) const;
    bool operator != (const char* _s) const;


private:
    char* m_data;
    size_t m_capacity;
    size_t m_length;

    void Allocate(const char* _s);
};



#endif  //  __SLOW_STRING_H_