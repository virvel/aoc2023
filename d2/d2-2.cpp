#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

template <typename T>
void print(T value) { 
    std::cout << value;
    std::cout << std::endl; 
    return;
}
template <typename T, typename... Targs>
void print(T value, Targs... args) { 
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

int main(int argc, char * argv[]) {

    std::fstream buffer( argv[1]); 
    std::vector<std::string> lines;
    std::string line;
    while ( std::getline (buffer, line)) {
        lines.push_back(line);
    }

    std::unordered_map<std::string, int> colors_max {{"red", 0}, {"green", 0}, {"blue", 0}};

    unsigned sum = 0;
    for( auto& line: lines) {
        line.erase(0, line.find(": ") + 2);
        auto items = split(line, "; ");
        for (auto& item : items) {
                auto colors = split(item, ", ");
                for (auto &color : colors) {
                       auto nums = split(color, " ");
                       colors_max[nums[1]] = std::max(colors_max.at(nums[1]),std::stoi(nums[0]));
                       }
                } 
                sum += colors_max["red"] * colors_max["green"] * colors_max["blue"];
                colors_max["red"] = colors_max["green"] = colors_max["blue"] = 0;
    }

    print(sum);

    return 0;
}