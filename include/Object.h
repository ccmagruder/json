// Copyright 2023 Caleb Magruder

#pragma once

#include "Variant.h"

// Contains object map of variants of different types,
// lookup by map key
// Example:
//    Objective o("{\"pi\",\"3.14\",\"str\",\"Hello World!\"}");
//    std::cout << std::string(o["str"]);
class Object{
 public:
        explicit Object(std::string buffer);
        explicit operator std::string() const;
        friend std::ostream& operator << (std::ostream& os, const Object& obj);
        bool operator==(const Object& other) const;
        bool contains(const std::string& key) const;
        Variant& operator[](std::string key);
        const Variant& operator[](std::string key) const;
        size_t size() { return map.size(); }
 protected:
        std::map<std::string, Variant> map;
};
