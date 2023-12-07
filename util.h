#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <list>

std::vector<std::string> readlines(const std::string fn) {

    std::fstream buffer( fn ); 
    std::vector<std::string> lines;
    std::string line;
    while ( std::getline (buffer, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::string readfile(const std::string fn) {
    std::fstream f( fn); 
    std::stringstream b;
    b << f.rdbuf();
    return b.str();
}
template <typename T>
constexpr void print(const T value) { 
    std::cout << value << std::endl; 
    return;
}
template <typename T, typename... Targs>
constexpr void print(const T value, const Targs... args) { 
    std::cout << value << ", ";
    print(args...);
    return;
}

template <typename T>
constexpr void print(std::vector<T> vec) {
    std::cout << "{";
    for (auto &v : vec)
        std::cout << v << ", ";
    std::cout << "}" << std::endl;
}

template <typename T>
auto zeros(size_t size) {
    std::vector<T> v(size);
    std::fill(v.begin(), v.end(), static_cast<T>(0));
    return v;
}

template <typename T>
auto ones(size_t size) {
    std::vector<T> v(size);
    std::fill(v.begin(), v.end(), static_cast<T>(1));
    return v;
}

auto split(std::string_view str, const std::string delimiter) {

    std::vector<std::string> items; 
    size_t pos = 0;
    while( (pos = str.find(delimiter))  != std::string::npos) {
        std::string temp = std::string(str.substr(0,pos));
        if (!temp.empty())
            items.push_back(std::string(str.substr(0, pos)));
        str.remove_prefix(pos + delimiter.length());
    }
    std::string temp = std::string(str);
    if (!str.empty())
        items.push_back(std::string(str));
    return items;
}

auto count(std::string s) 
{ 
    std::map<char, int> m;  
    for (auto &c : s) {
        m[c]++; 
    } 
    return m; 
} 

