// Copyright 2022 Caleb Magruder

#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <list>
#include <string>
#include <vector>

class Array;
class Object;

// Variant type contains array, bool, double, nulltype, object, or string
// Example:
//    Variant v("3.14");
//    fprintf("v = %1.2e\n',double(v));
class Variant{
 public:
       enum Type {ARRAY, BOOL, DOUBLE, NULLTYPE, OBJECT, STRING};

       // Default constructor
       Variant() = default;

       // Initialize variant by parsing string
       explicit Variant(std::string s);
       explicit Variant(int i) : _d(i), _type(DOUBLE) {}
       Variant(Type type, double d) : _d(d), _type(DOUBLE) {
       assert(type == DOUBLE);
       }

       // Equality operator with variant types
       bool operator==(const Array& a) const;
       bool operator==(const bool b) const;
       bool operator==(const double d) const;
       bool operator==(const Object& o) const;
       bool operator==(std::nullptr_t ptr) const;
       bool operator==(const std::string s) const;
       bool operator==(const char* s) const;
       bool operator==(const Variant& other) const;

       // Inequality Operator
       template<typename T>
       bool operator!=(const T& other) const {
       return !(*this == other);
       }

       // Explicit cast
       explicit operator std::shared_ptr<Array>() const;
       explicit operator bool() const;
       explicit operator double() const;
       explicit operator ptrdiff_t() const;
       explicit operator std::shared_ptr<Object>() const;
       operator std::string() const;

       // Serialize
       friend std::ostream& operator << (std::ostream& os, const Variant& v);

        // Array index operator (invalid for other types)
       Variant& operator[](const ptrdiff_t i);

       // Array index operator (invalid for other types)
       const Variant& operator[](const ptrdiff_t i) const;

       // Object map loopkup operator (invalid for other types)
       Variant& operator[](const std::string key);

       // Object map loopkup operator (invalid for other types)
       const Variant& operator[] (const std::string key) const;

       Type _type;

 private:
        // Underlying data structures, shared pointers only
        // allocated when initialized with that type
        std::shared_ptr<Array> _a;
        bool _b;
        double _d;
        std::shared_ptr<Object> _o;
        std::string _s;
};

#include "Array.h"
#include "Object.h"
