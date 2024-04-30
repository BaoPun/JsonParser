#include "./JsonNode.hpp"

JsonNode::JsonNode(){
    this->set_key("");
    this->is_value = true;
}

JsonNode::JsonNode(string key, bool is_value){
    this->set_key(key);
    this->is_value = is_value;
}

bool JsonNode::get_is_value() const{
    return this->is_value;
}

string JsonNode::get_key() const{
    return this->key;
}

void JsonNode::set_key(string key){
    this->key = key;
}

void JsonNode::print_node() const{
    cout << "HUHH" << endl;
}