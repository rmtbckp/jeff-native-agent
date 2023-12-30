#include "common.hpp"

#include <algorithm>
#include <locale>

using namespace std;

string jeff::join(list<string> entries, function<string(string, string)> join_lines) {
    return join(entries, string(""), join_lines);
}

string jeff::join(list<string> entries, string start, function<string(string, string)> join_lines) {
    return accumulate(entries.begin(), entries.end(), start, join_lines);
}

string jeff::join(list<bool> entries, function<string(string, string)> join_values) {
    return join(entries, string(""), join_values);
}

string jeff::join(list<bool> entries, string start, function<string(string, string)> join_values) {
    function<string(bool)> transform_values = [](bool b) -> string { return (b == 0) ? "false" : "true";};
    list<string> values;
    transform(entries.begin(), entries.end(), back_inserter(values), transform_values);
    return join(values, start, join_values);
}

wstring jeff::L(const string &str) {
    wstring ret;
    copy(str.begin(), str.end(), back_inserter(ret));
    return ret;
}

string jeff::S(const wstring &str) {
    locale const loc("");
    wchar_t const *from = str.c_str();
    size_t const len = str.size();
    vector<char> buffer(len + 1);
    std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
    return string(&buffer[0], &buffer[len]);
}

string jeff::JNITypeToJavaType(string signature) {
    switch (signature.c_str()[0]) {
        case 'Z': {  /* boolean */
            string value("boolean");
            return value;
        }
        case 'B': {  /* byte */
            return std::string("byte");
        }
        case 'C': {  /* char */
            return std::string("char");
        }
        case 'S': {  /* short */
            return std::string("short");
        }
        case 'I': {  /* int */
            return std::string("int");
        }
        case 'J': {  /* long */
            return std::string("long");
        }
        case 'F': {  /* float */
            return std::string("float");
        }
        case 'D': {  /* double */
            return std::string("double");
        }
        case 'L': {  /* Object */
            signature = signature.substr(1, signature.size() - 2);
            std::replace( signature.begin(), signature.end(), '/', '.');
            return signature;
        }
        default: {
            return std::string("Unknown type");
        }
        
    }
}
/*
inline string jeff::S(const wstring &str) {
    string ret;
    copy(str.begin(), str.end(), back_inserter(ret));
    return ret;
}*/
