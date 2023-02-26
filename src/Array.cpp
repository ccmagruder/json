// Copyright 2023 Caleb Magruder

#include <iostream>
#include <sstream>
#include <string>

#include "Array.h"

#define __MAX_ITEMS__ 64

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
