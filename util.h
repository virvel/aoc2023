#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

template <typename T>
constexpr void print(const T value) { 
    std::cout << value;
    std::cout << std::endl; 
    return;
}
template <typename T, typename... Targs>
constexpr void print(const T value, const Targs... args) { 
    std::cout << value;
    std::cout << ", ";
    print(args...);
    return;
}

auto split(std::string_view str, const std::string delimiter) {

    std::vector<std::string> items; 
    size_t pos = 0;
    while( (pos = str.find(delimiter))  != std::string::npos) {
        items.push_back(std::string(str.substr(0, pos)));
        str.remove_prefix(pos + delimiter.length());
    }
    items.push_back(std::string(str));
    return items;
}
