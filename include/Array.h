// Copyright 2022 Caleb Magruder

#pragma once

#include <string>

#include "Variant.h"

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
