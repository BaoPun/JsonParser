#ifndef JSON_NODE_H
#define JSON_NODE_H

#include "./JsonException.hpp"

class JsonNode{
private:
    string key;
    bool is_value;

public:
    JsonNode();
    JsonNode(string, bool = false);;

    bool get_is_value() const;
    string get_key() const;
    void set_key(string);

    virtual void print_node() const = 0;
    virtual void clear() = 0;
};

#endif