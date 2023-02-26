// Copyright 2023 Caleb Magruder

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Variant.h"

#define __MAX_ITEMS__ 64

Variant::Variant(std::string s) {
    // Remove preceding spaces
    while (s[0] == ' ') {
        s.erase(0, 1);
    }

    // Remove postceding spaces
    while (s[s.size()-1] == ' ') {
        s.erase(s.size()-1, 1);
    }

    // Detect number in string
    if (s[0] == '[') {
        _type = ARRAY;
        _a = std::make_shared<Array>(s);
    } else if (s == "true" || s == "True" || s == "TRUE") {
        _type = BOOL;
        _b = true;
    } else if (s == "false" || s == "False" || s == "FALSE") {
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
    } else if (s[0] == '\"') {
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

bool Variant::operator==(const int i) const {
    if (_type != DOUBLE) return false;
    return _d == static_cast<double>(i);
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
