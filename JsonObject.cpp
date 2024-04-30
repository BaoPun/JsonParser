#include "./JsonObject.hpp"

JsonObject::JsonObject(){
}


JsonObject::~JsonObject(){
    for(map<string, vector<JsonObject*>>::iterator it = this->list_obj.begin(); it != this->list_obj.end(); it++){
        for(size_t i = 0; i < it->second.size(); i++){
            if(it->second.at(i) != nullptr){
                delete it->second.at(i);
                it->second.at(i) = nullptr;
            }
        }
    }
    this->list_obj.clear();

    for(map<string, JsonObject*>::iterator it = this->obj.begin(); it != this->obj.end(); it++){
        if(it->second != nullptr){
            delete it->second;
            it->second = nullptr;
        }
    }
    this->obj.clear();

    for(map<string, vector<JsonNode*>>::iterator it = this->list_nodes.begin(); it != this->list_nodes.end(); it++){
        for(size_t i = 0; i < it->second.size(); i++){
            if(it->second.at(i) != nullptr){
                it->second.at(i)->clear();
                delete it->second.at(i);
                it->second.at(i) = nullptr;
            }
        }
    }
    this->list_nodes.clear();

    for(size_t i = 0; i < this->nodes.size(); i++){
        if(this->nodes.at(i) != nullptr){
            this->nodes.at(i)->clear();
            delete this->nodes.at(i);
            this->nodes.at(i) = nullptr;
        }
    }
    this->nodes.clear();
}

void JsonObject::add_obj(string key, JsonObject* obj){
    this->obj[key] = obj;
}

void JsonObject::add_node(JsonNode* node){
    this->nodes.push_back(node);
}

void JsonObject::add_to_node_list(string key, JsonNode* value){
    this->list_nodes[key].push_back(value);
}

void JsonObject::add_to_obj_list(string key, JsonObject* value){
    this->list_obj[key].push_back(value);
}

ostream& operator<<(ostream& os, const JsonObject& jo){
    // First, iterate through all the nodes.
    if(!jo.nodes.empty()){
        cout << "Key-value pairs: " << endl;
        for(size_t i = 0; i < jo.nodes.size(); i++){
            if(jo.nodes.at(i)->get_is_value()){
                jo.nodes.at(i)->print_node();
            }
        }
        cout << endl;
    }

    // Then, iterate through the list of nodes.
    if(!jo.list_nodes.empty()){
        cout << "Node List contents: " << endl;
        for(map<string, vector<JsonNode*>>::const_iterator it = jo.list_nodes.begin(); it != jo.list_nodes.end(); it++){
            for(size_t i = 0; i < it->second.size(); i++){
                it->second.at(i)->print_node();
            }
        }
    }

    // Then, iterate through the objects.
    if(!jo.obj.empty()){
        cout << "Nested objects: " << endl;
        for(map<string, JsonObject*>::const_iterator it = jo.obj.begin(); it != jo.obj.end(); it++){
            os << it->first << ":\n" << *it->second << endl << endl;
        }
    }

    // Then, iterate through the list of objects
    if(!jo.list_obj.empty()){
        cout << "Object List contents: " << endl;
        for(map<string, vector<JsonObject*>>::const_iterator it = jo.list_obj.begin(); it != jo.list_obj.end(); it++){
            cout << "Key: " << it->first << ", ";
            for(size_t i = 0; i < it->second.size(); i++){
                cout << *it->second.at(i) << endl;
            }
        }
    }

    

    

    return os;
}

