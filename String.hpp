#ifndef STRING_HPP
#define STRING_HPP

/*#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <stack>
#include <exception>
#include <iomanip>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using std::map;
using std::stack;
using std::exception;
using std::runtime_error;
using std::out_of_range;
using std::boolalpha;

/**
 * @brief Custom String class since std::string gave memory leaks while processing strings with spaces.
 * @brief May add more to this depending on what other string methods are needed.
 * 
 */
class String{
private:
    char* _c_str;
    int _size;
    int _capacity;

    void resize();

public:
    String(int = 20);
    String(const char*);
    String(const String&);
    ~String();

    int size();
    int capacity();
    char at(int);

    // Operator overloads
    String& operator=(const String&);
    String& operator+=(const String&);
    String& operator+=(const char*);
    String& operator+=(const char&);


    // String methods
    String substr(int, int = -1);


    void clear();
    void allocate(int = 20);
    void deallocate();


    // Friend function to overload the String class's ability to directly output to stream
    friend ostream& operator<<(ostream&, const String&);
};

#endif