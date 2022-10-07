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

// Contains array vector of variants of the same type,
// lookup by integer index
// Example:
//    Array a("[4,3.14,1]");
//    fprintf("a[1] = %1.2e\n",a[1]); /* prints 3.14 */
class Array{
 public:
        explicit Array(std::string buffer);
        explicit operator std::string() const;
        friend std::ostream& operator << (std::ostream& os, const Array& a);
        bool operator==(const Array& other) const;
        Variant& operator[](ptrdiff_t i) {
            assert(i < list.size());
            return list[i];
        }
        const Variant& operator[](ptrdiff_t i) const {
            assert(i < list.size());
            return list[i];
        }
        size_t size() { return list.size(); }
 private:
        std::vector<Variant> list;
};

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
