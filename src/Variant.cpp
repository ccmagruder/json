// Copyright 2022 Caleb Magruder

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Variant.h"

#define __MAX_ITEMS__ 64

Variant::Variant(std::string s) {
    // Detect number in string
    if (s[0] == '[') {
        _type = ARRAY;
        _a = std::make_shared<Array>(s);
    } else if (s == "true") {
        _type = BOOL;
        _b = true;
    } else if (s == "false") {
        _type = BOOL;
        _b = false;
    } else if (s[0] >= '0' && s[0] <= '9' || s[0] == '.' || s[0] == '-') {
        _type = DOUBLE;
        _d = std::stod(s);
    } else if (s == "null" || s == "NULL") {
        _type = NULLTYPE;
    } else if (s[0] == '{') {
        _type = OBJECT;
        _o = std::make_shared<Object>(s);
    } else {
        _type = STRING;
        _s = s.substr(1, s.size()-2);
    }
}

bool Variant::operator==(const Array& a) const {
    if (_type != Variant::ARRAY) return false;
    return *_a == a;
}

bool Variant::operator==(const bool b) const {
    if (_type != BOOL) return false;
    return _b == b;
}
bool Variant::operator==(const double d) const {
    if (_type != DOUBLE) return false;
    return _d == d;
}

bool Variant::operator==(const Object& o) const {
    if (_type != Variant::OBJECT) return false;
    return *_o == o;
}

bool Variant::operator==(std::nullptr_t ptr) const {
    if (_type != NULLTYPE) return false;
    return ptr == nullptr;
}

bool Variant::operator==(const std::string s) const {
    if (_type != STRING) return false;
    return _s == s;
}

bool Variant::operator==(const char* s) const {
    if (_type != STRING) return false;
    return _s == std::string(s);
}

bool Variant::operator==(const Variant& other) const {
    if (_type != other._type) return false;
    switch (_type) {
        case ARRAY:
            return *_a == *other._a;
        case BOOL:
            return _b == other._b;
        case DOUBLE:
            return _d == other._d;
        case NULLTYPE:
            return true;
        case OBJECT:
            return true;
        case STRING:
            return _s == other._s;
        default:
            std::runtime_error("Invalid Type!\n");
            exit(1);
    }
}

Variant::operator std::shared_ptr<Array>() const {
    assert(_type == ARRAY);
    return _a;
}

Variant::operator bool() const {
    assert(_type == BOOL);
    return _b;
}

Variant::operator double() const {
    assert(_type == DOUBLE);
    return _d;
}

Variant::operator ptrdiff_t() const {
    assert(_type == DOUBLE);
    return ptrdiff_t(_d);
}

Variant::operator std::shared_ptr<Object>() const {
    assert(_type == OBJECT);
    return _o;
}

Variant::operator std::string() const {
    assert(_type == STRING);
    return _s;
}

std::ostream& operator << (std::ostream& os, const Variant& v) {
    switch (v._type) {
        case Variant::ARRAY :
            os << *(v._a);
            break;
        case Variant::BOOL :
            if (v._b)
                os << "true";
            else
                os << "false";
            break;
        case Variant::DOUBLE :
            os << v._d;
            break;
        case Variant::NULLTYPE :
            os << "null";
            break;
        case Variant::OBJECT :
            os << *(v._o);
            break;
        case Variant::STRING :
            os << "\"" << v._s << "\"";
            break;
        default :
            std::runtime_error("Unknown value type.");
            exit(1);
    }
    return os;
}

Variant& Variant::operator[](const ptrdiff_t i) {
    assert(_type == Variant::ARRAY);
    return (*_a)[i];
}

const Variant& Variant::operator[](const ptrdiff_t i) const {
    assert(_type == Variant::ARRAY);
    return (*_a)[i];
}

Variant& Variant::operator[](const std::string key) {
    assert(_type == Variant::OBJECT);
    return (*_o)[key];
}

const Variant& Variant::operator[](const std::string key) const {
    assert(_type == Variant::OBJECT);
    return (*_o)[key];
}

Array::Array(std::string buffer) {
    buffer.erase(0, 1);  // Remove '['
    buffer.erase(buffer.size()-1, 1);  // Remove ']'

    size_t ldelim = 0;
    size_t rdelim;
    if (buffer.size() == 0)
        return;
    for (ptrdiff_t i = 0; i < __MAX_ITEMS__; i++) {
        rdelim = buffer.find(',', ldelim);
        std::string value = buffer.substr(ldelim, rdelim-ldelim);
        list.push_back(Variant(value));
        if (rdelim == std::string::npos || rdelim + 1 >= buffer.size()) {
            return;
        }
        assert(buffer[rdelim] == ',');
        ldelim = rdelim+1;
    }

    std::clog << "readObject stopped reading after 20 pairs";
}

Array::operator std::string() const {
    std::ostringstream buffer;
    buffer << "[";
    std::vector<Variant>::const_iterator i;
    for (i = list.begin(); i != list.end(); i++) {
        if (i != list.begin()) buffer << ",";
        buffer << *i;
    }
    buffer << "]";
    return buffer.str();
}

std::ostream& operator << (std::ostream& os, const Array& a) {
    os << std::string(a);
    return os;
}

bool Array::operator==(const Array& other) const {
    if (list.size() != other.list.size()) return false;
    std::vector<Variant>::const_iterator j = other.list.begin();
    std::vector<Variant>::const_iterator i;
    for (i = list.begin(); i != list.end(); i++) {
        if (*i != *j) return false;
        j++;
    }
    return true;
}

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
