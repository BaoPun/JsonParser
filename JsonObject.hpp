#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "./JsonStringValue.hpp"
#include "./JsonValue.hpp"

class JsonObject{
    private:
        map<string, JsonObject*> obj;
        vector<JsonNode*> nodes;
        map<string, vector<JsonNode*>> list_nodes;
        map<string, vector<JsonObject*>> list_obj;

    public:
        JsonObject();
        ~JsonObject();

        void add_obj(string, JsonObject*);
        void add_node(JsonNode*);
        void add_to_node_list(string, JsonNode*);
        void add_to_obj_list(string, JsonObject*);


        friend ostream& operator<<(ostream&, const JsonObject&);
};

#endif