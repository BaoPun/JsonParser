#include "./Json.hpp"


// Helper functions
string parseJsonObject(JsonObject*&, string, stack<char>&);
string parseJsonList(JsonObject*&, string, string, stack<char>&);
string parseJsonKey(string&);
void trimLeadingTrailingSpaces(string&);
string parseJsonValue(JsonObject*&, const string&, string&, bool);


int main(){
    /*
    // Test custom string
    String str("ICANT KEKW whatashame");
    cout << str.substr(6, 100) << endl;
    cout << "Pre concatentation: " << str << endl;
    String more(" MYMAP it's time");
    str += more;
    cout << "Post concatenation with string objects: " << str << endl;
    str += " xdd";
    cout << "Post concatenation with strings: " << str << endl;
    str += '!';
    cout << "Post concatenation with a char: " << str << endl;
    {
        String another;
        another = str;
        another += " WTF";
        cout << another << endl;
    }
    String copy(str);
    cout << copy << endl;
    */

    // Variables
    string filename;
    ifstream fin;
    stack<char> symbols;
    stringstream ss;
    JsonObject* Json = new JsonObject();
    
    // Ask for a valid json file, and keep asking until a valid json file was given.
    cout << "Enter a json file to parse: ";
    cin >> filename;
    fin.open(filename);
    while(!fin){
        cout << "Error, file is invalid.  Enter a json file to parse: ";
        cin >> filename;
        fin.open(filename);
    }
    
    // Read the entire file and send into a stringstream
    while(!fin.eof()){
        // First, read the entire string from the file
        string line;
        getline(fin, line);

        // Second, trim all leading and trailing white spaces
        trimLeadingTrailingSpaces(line);

        // Third, send the entire string contents into the string stream
        ss << line;
    }
    fin.close();
    

    // Now, begin the json parsing
    string json;
    getline(ss, json);
    //cout << "Json contents: " << json << endl << endl;
    bool is_complete = true;
    try{
        // Either starts as an object or as a list
        if(json.front() == '{')
            json = parseJsonObject(Json, json, symbols);
        else if(json.front() == '[')
            json = parseJsonList(Json, json, "ICANT KEKW whatashame", symbols);
        else
            throw InvalidJsonFormatException("Json format is invalid.  Expected json to start with either [ or {"); 
        //cout << boolalpha << endl << "Has the json successfully been parsed? " << (json == "" && symbols.empty()) << endl;
        if(!(json == "" && symbols.empty()))
            throw InvalidJsonFormatException("Json format is invalid.");
    }
    catch(InvalidJsonFormatException e){
        cout << e.what() << endl;
        is_complete = false;
    }

    // What does the json look like?
    if(is_complete)
        cout << *Json << endl;
    
    // Prior to closing the program, deallocate the Json
    delete Json;

    return 0;
}

void trimLeadingTrailingSpaces(string& str){
    // Trim any leading spaces
    while(!str.empty() && (str.front() == ' ' || str.front() == '\t'))
        str = str.substr(1);

    // Trim any trailing spaces
    while(!str.empty() && (str.back() == ' ' || str.back() == '\t' || str.back() == '\n'))
        str.pop_back();
}

string parseJsonObject(JsonObject*& Json, string json, stack<char>& symbols){
    // Ignore all leading spaces
    trimLeadingTrailingSpaces(json);

    // The first character of the json string should be a {.
    // If not, then stop.
    if(json.empty())
        throw InvalidJsonFormatException("Json format is invalid.  There is no content.");
    if(json.front() != '{')
        throw InvalidJsonFormatException("Json format is invalid.  It does not start with an opening curly brace.");
    symbols.push(json.front());
    
    // Process the key up until the end of the space ("key": )
    string key;
    bool is_comma = true;
    int pos = 0;

    while(is_comma){
        try{
            json = json.substr(1);

            // Ignore all leading spaces
            trimLeadingTrailingSpaces(json);

            key = parseJsonKey(json);

            // Ignore all leading spaces
            trimLeadingTrailingSpaces(json);

            // Either process a nested object, a list, or a value.
            if(json.at(pos) == '{'){
                JsonObject* newJson = new JsonObject();
                json = parseJsonObject(newJson, json, symbols);
                Json->add_obj(key, newJson);
            }
            else if(json.at(pos) == '['){
                json = parseJsonList(Json, json, key, symbols);
            }
            else
                json = parseJsonValue(Json, key, json, false);
            is_comma = (json.at(0) == ',');
            if(is_comma){
                pos++;
                while(json.at(pos) == ' ')
                    pos++;
                json = json.substr(pos - 1);
                pos = 0;
            }
        }
        catch(InvalidJsonFormatException e){
            cout << e.what() << endl;
            return json;
        }
    }

    // Ignore all leading spaces
    trimLeadingTrailingSpaces(json);

    if(symbols.top() != '{'/* || json.at(pos) != '}'*/)
        throw InvalidJsonFormatException("Json format is invalid.  The found symbol at the top is not {.");
    symbols.pop();
    json = json.substr(1);
    
    return json;
}

string parseJsonList(JsonObject*& Json, string json, string key, stack<char>& symbols){
    // The first character of the json string should be a [.
    // If not, then stop.
    if(json.empty())
        throw InvalidJsonFormatException("Json format is invalid.  There is no content.");
    if(json.front() != '[')
        throw InvalidJsonFormatException("Json format is invalid.  It does not start with an opening curly brace.");
    symbols.push(json.front());

    bool is_comma = true;
    int pos = 0;

    while(is_comma){
        try{
            json = json.substr(1);

            // Ignore all leading spaces
            trimLeadingTrailingSpaces(json);

            // What kind of value?
            // Either process a nested object, a list, or a value.
            if(json.at(pos) == '{'){
                JsonObject* newJson = new JsonObject();
                json = parseJsonObject(newJson, json, symbols);
                Json->add_to_obj_list(key, newJson);
            }
            else if(json.at(pos) == '['){
                json = parseJsonList(Json, json, key, symbols);
            }
            else if(json.at(pos) == ']')
                break;
            else
                json = parseJsonValue(Json, key, json, true);
            is_comma = (json.at(0) == ',');
            if(is_comma){
                pos++;
                while(json.at(pos) == ' ')
                    pos++;
                json = json.substr(pos - 1);
                pos = 0;
            }
        }
        catch(InvalidJsonFormatException e){
            cout << e.what() << endl;
            return json;
        }
    }

    // Ignore all leading spaces
    trimLeadingTrailingSpaces(json);

    if(symbols.top() != '[' || json.at(pos) != ']')
        throw InvalidJsonFormatException("Json format is invalid.  The found symbol at the top is not [.");

    symbols.pop();
    json = json.substr(1);  

    return json;
}

/**
 * @brief Extract the key from the json string, and move the json string forward.
 * 
 * @param json - the current json strong
 * @return string - the key extracted
 */
string parseJsonKey(string& json){
    // The second character of the json string should be a quotation.  If not, then stop.
    if(json.front() != '\"')
        throw InvalidJsonFormatException("Json format is invalid.  There is no quotation following the opening curly brace.");

    // Continue processing until we see another quotation
    // This is our key.  
    string key;
    int pos = 0;
    while(pos < json.length() && json.at(++pos) != '\"')
        key += json.at(pos);
    json = json.substr(++pos);

    while(!json.empty() && json.front() == ' ')
        json = json.substr(1);
    pos = 0;
    // After processing the first key, we should see a : followed by a space. 
    // If not, this is not a valid json
    if(pos >= json.length() || json.at(pos) != ':') {
        cout << "Invalid json: " << json.substr(pos) << endl;
        throw InvalidJsonFormatException("Json format is invalid.  There is no \": \" after the key was read.");
    }
    pos++;
    while(json.at(pos) == ' ')
        pos++;
    json = json.substr(pos);
    return key;
}

/**
 * @brief Parse through the json values, assuming that it is either a string, a number, or a boolean.
 * 
 * @param json - the current json string.
 */
string parseJsonValue(JsonObject*& Json, const string& key, string& json, bool fromList){
    int pos = 0;
    
    // Processing a string.
    if(json.at(pos) == '\"'){
        String value;
        while(json.at(++pos) != '\"')
            value += json.at(pos);
        if(!fromList)
            Json->add_node(new JsonStringValue(key, value));
        else
            Json->add_to_node_list(key, new JsonStringValue(key, value));
        json = json.substr(pos + 1);
    }

    // Processing a number or a boolean
    else if(isalnum(json.at(pos)) || json.at(pos) == '-'){
        bool is_negative = json.at(pos) == '-';
        if(is_negative)
            pos++;
        if(isdigit(json.at(pos))){
            bool is_decimal = false;
            string value(string(1, json.at(pos++)));
            if(is_negative)
                value.insert(value.begin(), '-');
            while(isdigit(json.at(pos)) || json.at(pos) == '.'){
                if(json.at(pos) == '.'){
                    if(!is_decimal)
                        is_decimal = true;
                    else
                        throw InvalidJsonFormatException("Json format is invalid.  There are way too many decimals.");
                }
                value += json.at(pos++);
            }
            if(!fromList){
                if(is_decimal)
                    Json->add_node(new JsonValue<double>(key, stod(value)));
                else
                    Json->add_node(new JsonValue<long long>(key, stoll(value)));
            }
            else{
                if(is_decimal)
                    Json->add_to_node_list(key, new JsonValue<double>(key, stod(value)));
                else
                    Json->add_to_node_list(key, new JsonValue<long long>(key, stoll(value)));
            }
            json = json.substr(pos);
        }
        else if(json.at(pos) == 't'){
            if(is_negative)
                throw InvalidJsonFormatException("Json format is invalid.  There shouldn't be a negative sign.");
            if(pos + 3 >= json.length())
                throw InvalidJsonFormatException("Json format is invalid.  Cannot fully extract the boolean true.");
            if(json.at(pos + 1) == 'r' && json.at(pos + 2) == 'u' && json.at(pos + 3) == 'e'){
                pos += 4;
                if(!fromList)
                    Json->add_node(new JsonValue<bool>(key, true));
                else
                    Json->add_to_node_list(key, new JsonValue<bool>(key, true));
                json = json.substr(pos);
            }
            else
                throw InvalidJsonFormatException("Json format is invalid.  The boolean true was not processable.");
        }
        else if(json.at(pos) == 'f'){
            if(is_negative)
                throw InvalidJsonFormatException("Json format is invalid.  There shouldn't be a negative sign.");
            if(pos + 4 >= json.length())
                throw InvalidJsonFormatException("Json format is invalid.  Cannot fully extract the boolean false.");
            if(json.at(pos + 1) == 'a' && json.at(pos + 2) == 'l' && json.at(pos + 3) == 's' && json.at(pos + 4) == 'e'){   
                pos += 5;
                if(!fromList)
                    Json->add_node(new JsonValue<bool>(key, false));
                else
                    Json->add_to_node_list(key, new JsonValue<bool>(key, false));
                json = json.substr(pos);
            }
            else
                throw InvalidJsonFormatException("Json format is invalid.  The boolean false was not processable.");
        }
        else if(json.at(pos) == 'n'){
            if(is_negative)
                throw InvalidJsonFormatException("Json format is invalid.  There shouldn't be a negative sign.");
            if(pos + 3 >= json.length())
                throw InvalidJsonFormatException("Json format is invalid.  Cannot fully extract the value null.");
            if(json.at(pos + 1) == 'u' && json.at(pos + 2) == 'l' && json.at(pos + 3) == 'l'){
                pos += 4;
                if(!fromList)
                    Json->add_node(new JsonStringValue(key, "null"));
                else
                    Json->add_to_node_list(key, new JsonStringValue(key, "null"));
                json = json.substr(pos);
            }
            else
                throw InvalidJsonFormatException("Json format is invalid.  The value null was not processable.");
        }
    }

    // Any other processing makes this json invalid.
    else
        throw InvalidJsonFormatException("Json format is invalid.  An unexpected character was spotted: ");

    trimLeadingTrailingSpaces(json);
    return json;
}
