#include "./JsonStringValue.hpp"

JsonStringValue::JsonStringValue(){
    
}

JsonStringValue::JsonStringValue(string key, String value) : JsonNode(key, true){
    this->value = value;
}

JsonStringValue::~JsonStringValue(){
    this->clear();
}

String JsonStringValue::get_value() const{
    return this->value;
}

void JsonStringValue::set_value(String value){
    this->value = value;
}

void JsonStringValue::print_node() const{
    cout << boolalpha << this->get_key() << ": " << this->get_value() << endl;
}

void JsonStringValue::clear(){
    this->value.deallocate();
}
