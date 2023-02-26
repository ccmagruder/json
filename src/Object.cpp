// Copyright 2022 Caleb Magruder

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Array.h"
#include "Object.h"
#include "Variant.h"

#define __MAX_ITEMS__ 64

Object::Object(std::string buffer) {
    buffer.erase(0, 1);  // Remove '{'
    buffer.erase(buffer.size()-1, 1);  // Remove '}'

    if (buffer.size() == 0)
        return;

    size_t ldelim = 0;
    size_t rdelim = 0;
    for (ptrdiff_t i = 0; i < __MAX_ITEMS__; i++) {
        assert(buffer[ldelim] == '"');  // Check left delim

        rdelim = buffer.find('"', ldelim+1);  // Find right delim
        assert(buffer[rdelim] == '"');  // Check right delim
        std::string key = buffer.substr(ldelim+1, rdelim-ldelim-1);
        assert(buffer[rdelim+1] == ':');  // Check colon

        ldelim = rdelim + 2;
        // skip ahead to ']' if array
        if (buffer[ldelim] == '[') {
            rdelim = buffer.find(']', ldelim);
        } else if (buffer[ldelim] == '{') {
            // skip ahead if object
            rdelim = buffer.find('}', ldelim);
        }
        rdelim = buffer.find(",", rdelim);

        map[key] = Variant(buffer.substr(ldelim, rdelim-ldelim));
        if (rdelim == std::string::npos || rdelim + 1 >= buffer.size()) {
            return;
        }
        assert(buffer[rdelim] == ',');
        ldelim = rdelim + 1;
    }

    std::clog << "readObject stopped reading after 20 pairs";
}

Object::operator std::string() const {
    std::ostringstream buffer;
    buffer << *this;
    return buffer.str();
}

std::ostream& operator << (std::ostream& os, const Object& obj) {
    os << "{";
    std::map<std::string, Variant>::const_iterator i;
    for (i = obj.map.begin(); i != obj.map.end(); i++) {
        if (i != obj.map.begin()) os << ",";
        os << i->first << ":" << i->second;
    }
    os << "}";
    return os;
}

bool Object::operator==(const Object& other) const {
    if (map.size() != other.map.size()) return false;
    std::map<std::string, Variant>::const_iterator j = other.map.begin();
    std::map<std::string, Variant>::const_iterator i;
    for (i = map.begin(); i != map.end(); i++) {
        if (*i != *j) return false;
        j++;
    }
    return true;
}

bool Object::contains(const std::string& key) const {
    return map.contains(key);
}

Variant& Object::operator[](std::string key) {
    return map[key];
}

const Variant& Object::operator[](std::string key) const {
    return map.at(key);
}
