#include "./String.hpp"

/**
 * @brief Helper function to resize the array.  
 * @brief Specifically used privately when adding contents.
 * 
 */
void String::resize(){
    // Make a new temp array to store current array contents.
    char* temp = new char[this->_size];
    memset(temp, '\0', this->_size);
    for(int i = 0; i < this->_size; i++)
        temp[i] = this->_c_str[i];

    // Delete the original array, update the capacity, and then reallocate the array with the new capacity
    delete [] this->_c_str;
    this->_capacity *= 2;
    this->_c_str = new char[this->_capacity];
    memset(this->_c_str, '\0', this->_capacity);

    // Finally, copy the contents back and then delete the temp array
    for(int i = 0; i < this->_size; i++)
        this->_c_str[i] = temp[i];
    delete [] temp;

}

/**
 * @brief New String object that takes in a capacity.
 * @brief Also acts as a default constructor if the capacity is not given (default = 20)
 * 
 * @param capacity - capacity of the array (default = 20)
 */
String::String(int capacity){
    this->_size = 0;
    if(capacity <= 5)
        this->_capacity = 20;
    else
        this->_capacity = capacity;
    this->_c_str = new char[this->_capacity];
    memset(this->_c_str, '\0', this->_capacity);
}

/**
 * @brief New String object that will take in a passed in a c string.
 * @brief The capacity of the object will be 2x as long.
 * 
 * @param c_str 
 */
String::String(const char* c_str){
    this->_size = 0;
    while(c_str[this->_size] != '\0')
        this->_size++;
    if(this->_size > 0)
        this->_capacity = this->_size * 2;
    else
        this->_capacity = 10;
    this->_c_str = new char[this->_capacity];
    memset(this->_c_str, '\0', this->_capacity);
    for(int i = 0; i < this->_size; i++)
        this->_c_str[i] = c_str[i];
}

/**
 * @brief Copy constructor of the String object.
 * 
 * @param s 
 */
String::String(const String& s){
    this->_size = s._size;
    this->_capacity = s._capacity;
    this->_c_str = new char[this->_capacity];
    memset(this->_c_str, '\0', this->_capacity);
    for(int i = 0; i < this->_size; i++)
        this->_c_str[i] = s._c_str[i];
}

String::~String(){
    this->deallocate();
}

int String::size(){
    return this->_size;
}

int String::capacity(){
    return this->_capacity;
}

char String::at(int i){
    if(i < 0 || i >= this->_size)
        throw out_of_range("Index out of range for custom at.");
    return this->_c_str[i];
}

String String::substr(int start, int length){
    // Return a new String object
    String newString(this->_capacity);

    // Now, copy the relevant contents.
    int idx = 0;

    // First, make a copy of the string and get the original contents
    char* temp = new char[this->_size + 1];
    memset(temp, '\0', this->_size + 1);
    for(int i = 0; i <= this->_size; i++)
        temp[i] = this->_c_str[i];

    // If length is less than 0, then just focus on start.
    if(length < 0){
        // Now, copy the relevant contents.
        for(int i = start; i < this->_size + start && temp[i] != '\0' && i < this->_capacity; i++)
            newString._c_str[idx++] = temp[i];
    }
    // Otherwise, go from start to length.  
    else{
        // Now, copy the relevant contents.
        for(int i = start; i < length + start && temp[i] != '\0' && i < this->_capacity; i++)
            newString._c_str[idx++] = temp[i];
    }

    // Make sure to deallocate the temp from earlier.
    delete [] temp;

    // Now update the size
    newString._size = idx;
    newString._c_str[newString._size] = '\0';

    return newString;
}

String& String::operator=(const String& str){
    this->deallocate();
    this->_size = str._size;
    this->_capacity = str._capacity;
    this->_c_str = new char[this->_capacity];
    memset(this->_c_str, '\0', this->_capacity);
    for(int i = 0; i < this->_size; i++)
        this->_c_str[i] = str._c_str[i];
    return *this;
}

String& String::operator+=(const String& str){
    // Array might have to be reallocated
    if(this->_c_str == nullptr)
        this->allocate();

    // Do we need to resize?
    while(this->_size + str._size >= this->_capacity)
        this->resize();

    // Add the contents of the string's array to this array
    for(int i = 0; i < str._size; i++)
        this->_c_str[this->_size++] = str._c_str[i];

    return *this;
}

String& String::operator+=(const char* str){
    // Array might have to be reallocated
    if(this->_c_str == nullptr)
        this->allocate();

    // W/o using strlen, determine the size of str.
    int size = 0;
    while(str[size] != '\0')
        size++;

    // Do we need to resize?
    while(this->_size + size >= this->_capacity)
        this->resize();

    // Add the contents of the string's array to this array
    for(int i = 0; i < size; i++)
        this->_c_str[this->_size++] = str[i];

    return *this;
}

String& String::operator+=(const char& c){
    // Array might have to be reallocated
    if(this->_c_str == nullptr)
        this->allocate();
        
    // Do we need to resize?
    if(this->_size + 1 >= this->_capacity)
        this->resize();

    // Add the single character
    this->_c_str[this->_size++] = c;

    return *this;
}

/**
 * @brief Clear the contents of the array. Does not deallocate the array, however.
 * 
 */
void String::clear(){
    memset(this->_c_str, '\0', this->_capacity);
    this->_size = 0;
}

void String::allocate(int capacity){
    if(this->_c_str == nullptr){
        if(capacity <= 5)
            this->_capacity = 20;
        else
            this->_capacity = capacity;
        this->_size = 0;
        this->_c_str = new char[this->_capacity];
    }
}

void String::deallocate(){
    if(this->_c_str != nullptr){
        delete [] this->_c_str;
        this->_c_str = nullptr;
    }
}

// Friend function that overloads the output operator (<<).
// Simply prints the contents of the string.
ostream& operator<<(ostream& os, const String& str){
    for(int i = 0; i < str._size && str._c_str[i] != '\0'; i++)
        os << str._c_str[i];
    return os;
}

