
#include "MyString.h"


int main() {
    MyString defaultString; // Default constructor

    MyString hello("Hello"); // Constructor with a character array

    MyString moved(std::move(hello)); // Move constructor
    moved.print();

    MyString world(" World");

    MyString combined = moved + world;
    combined.print();


    MyString error = hello + world;
    error.print();

    return 0;
}
