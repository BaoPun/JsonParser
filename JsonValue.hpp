#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include "./JsonNode.hpp"

template <class T>
class JsonValue : public JsonNode{
private:
    T value{};

public:
    JsonValue();
    JsonValue(string, T);

    T get_value() const;
    void set_value(T);
    void print_node() const;
    void clear();

};

#include "./JsonValue.cpp"
#endif