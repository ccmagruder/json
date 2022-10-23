// Copyright 2022 Caleb Magruder

#include <iostream>
#include <fstream>

#include "JSON.h"
#include "Variant.h"

JSON::JSON(std::string fileName):Object(__load(fileName)) {}

std::string JSON::__load(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("File [" + fileName + "] does not exit.");
    }

    // Read file into buffer, removing newline characters
    std::string buffer;
    while (!file.eof()) {
        std::string line;
        getline(file, line);
        buffer += line;
    }

    // Erase whitespace ' '
    size_t index = buffer.find(' ');
    while (index != std::string::npos) {
        buffer.erase(index, 1);
        index = buffer.find(' ');
    }

    if (buffer[0] != '{') {
        std::runtime_error("json file must be of the form {...}");
    }

    assert(buffer.size() > 0);
    assert(buffer[buffer.size()-1] == '}');
    return buffer;
}
