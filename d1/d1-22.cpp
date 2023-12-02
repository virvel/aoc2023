#include <fstream>
#include <memory>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>


int main() {

    std::vector<std::string> lines;
    std::string string;

    std::ifstream input ("input", std::ios::binary);
    if (input) {

        while (getline( input, string)) {
            lines.push_back(string);
        }
    }
    
    unsigned long p1, p2;
    std::vector<int> p1_digits;
    std::vector<int> p2_digits;

    for (const std::string_view &line : lines) {
        p1_digits.clear();
        p2_digits.clear();
          
        int idx = 0;
        for (auto &c : line) {  
            if (std::isdigit(c)) {
                p1_digits.push_back(c - 48);
                p2_digits.push_back(c - 48);
            }
            int idy = 1;
            const auto substring = line.substr(idx++);
            for (auto &val : {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}) {
                if (substring.starts_with(val)) {
                        p2_digits.push_back(idy++);
                }
            }
        }
        p1 += p1_digits.front()*10 + p1_digits.back();
        p2 += p2_digits.front()*10 + p2_digits.back();
    }

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;

    return 0;
}
