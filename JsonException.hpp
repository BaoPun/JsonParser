#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include "./String.hpp"

// Classes, including CustomExceptions
class InvalidJsonFormatException : public runtime_error{
    public:
        InvalidJsonFormatException(const char* what) : runtime_error(what){}
};

#endif