// Copyright 2022 Caleb Magruder

#pragma once

#include <string>

#include "Variant.h"

// JSON API
class JSON : public Object {
 public:
        explicit JSON(std::string fileName);
 private:
        // Parse file
        std::string __load(std::string fileName);
};
