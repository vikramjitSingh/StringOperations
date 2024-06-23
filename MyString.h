#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

template<typename CharT>
class MyBasicString {
private:
    CharT* __data;
    size_t __length;
    size_t __size;
    const size_t __buffer = 10;


public:
    // Constructor with no arguments
    MyBasicString() : __data(new CharT[1]) {
        __data[0] = '\0';
        __length = 0;
        __size = 0;

    }

    // Constructor with a character array
    MyBasicString(const char* source) {
        if (source == nullptr) {
            __data = new CharT[1];
            __data[0] = '\0';
        } else {
            __length = std::strlen(source);
            __size = __length + __buffer;
            __data = new CharT[__size];
            strcpy(__data, source);
        }
    }

    // Copy constructor
    MyBasicString(const MyBasicString& source) {
        __data = new CharT[source.size()];
        strcpy(__data, source.c_str());
        __length = source.length();
        __size = source.size();
    }

    // Move constructor
    MyBasicString(MyBasicString&& source) {

        if(__length > 0) {
            delete [] __data;
        }
        __data = source.c_str();
        __length = source.length();
        __size = source.size();

        source.release();
    }

    // Destructor
    ~MyBasicString() {
        delete[] __data;
        __data = nullptr;
        __length = 0;
        __size = 0;
    }

    /*  helper functions */

    void clear () {
        if (__data != nullptr) {
            CharT *temp = __data;

            while (*__data != '\0') {
                *__data = '\0';
                __data++;
            }

            __data = temp;
            __length = strlen(__data);
        }
    }
    void release() {
        __data = nullptr;
        __length = 0;
        __size = 0;
    }

    // Get size
    size_t size() const {
        return __size;
    }

    // Get length
    size_t length() const {
        return __length;
    }

    // Get naked __data pointer
    CharT* c_str() const {
        return __data;
    }

    // Print
    void print() const {
        std::cout << __data << std::endl;
    }

    /* string manipulations */

    // Concatenate
    MyBasicString operator+(const MyBasicString& source) const {
        size_t tempSize = __length + source.length() + __buffer;
        CharT* temp = new CharT[tempSize];

        if (__data != nullptr && (*__data != '\0')) {
            std::strcpy(temp, __data);
        }

        std::strcat(temp, source.c_str());
        MyBasicString result(temp);
        delete[] temp;
        return result;
    }

    // append
    MyBasicString append(const MyBasicString& source) {

        if (__size <= __length + strlen(source.c_str())) {
            size_t newSize = __length + source.length() + __buffer;
            CharT* temp = new CharT[newSize];
            std::strcpy(temp, __data);
            std::strcat(temp, source.c_str());
            delete[] __data;
            __data = temp;
            __length = std::strlen(__data);
            __size = newSize;
        }
        else {
            //copy new string after the __length position
            std::strcpy(__data, source.c_str());
            __length += __length + source.length();
        }

        return this;
    }

    // prepend
    MyBasicString prepend(const MyBasicString& source) {

        size_t newSize = __length + source.length() + __buffer;
        CharT* temp = new CharT[newSize];
        std::strcat(temp, source.c_str());
        std::strcpy(temp, __data);
        delete[] __data;
        __data = temp;
        __length = std::strlen(__data);
        __size = newSize;

        return this;
    }

    // Compare
    bool operator==(const MyBasicString& source) const {
        return std::strcmp(__data, source.c_str()) == 0;
    }

    // Access character by index
    CharT& operator[] (int index) const {
        if (index < __length)
            return __data[index];
        else
            throw std::out_of_range("Index out of bounds");
    }

};

typedef MyBasicString<char> MyString;


#endif // MYSTRING_H
