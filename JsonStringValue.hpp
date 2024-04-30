#ifndef JSON_STRING_VALUE_H
#define JSON_STRING_VALUE_H

#include "./JsonNode.hpp"

class JsonStringValue : public JsonNode{
private:
    String value;
public:
    JsonStringValue();
    JsonStringValue(string, String);
    ~JsonStringValue();

    String get_value() const;
    void set_value(String);
    void print_node() const;
    void clear();
};

#endif