#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

    std::unordered_map<std::string, int> colors_max {{"red", 12}, {"green", 13}, {"blue", 14}};

    unsigned sum = 0;
    int index = 1;
    bool pass;
    for( auto& line: lines) {
        pass = true;
        line.erase(0, line.find(": ") + 2);
        auto items = split(line, "; ");
        for (auto& item : items) {
            if (pass) { 
                auto colors = split(item, ", ");
                for (auto &color : colors) {
                    if(pass) {
                       auto nums = split(color, " ");
                       if (colors_max.at(nums[1]) < std::stoi(nums[0])) {
                           sum += index;
                           pass = false;
                           break;
                       }
                    }
                }
            }
        }
        
        index++;
    }

    std::cout << ((index-1)*(index)/2) - sum  << std::endl;
    

    return 0;
}