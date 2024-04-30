#ifndef JSON_VALUE_CPP
#define JSON_VALUE_CPP
#include "./JsonValue.hpp"

template <class T>
JsonValue<T>::JsonValue() : JsonNode(){

}

template <class T>
JsonValue<T>::JsonValue(string key, T value) : JsonNode(key, true){
    this->set_value(value);
}

template <class T>
T JsonValue<T>::get_value() const{
    return this->value;
}

template <class T>
void JsonValue<T>::set_value(T value){
    this->value = value;
}

template <class T>
void JsonValue<T>::print_node() const{
    cout << boolalpha << this->get_key() << ": " << this->get_value() << endl;
}

template <class T>
void JsonValue<T>::clear(){
    
}

#endif