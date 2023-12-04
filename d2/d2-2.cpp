#include "util.h"


int main(int argc, char * argv[]) {

    auto lines = readlines(argv[1]);

    std::unordered_map<std::string, int> colors_max {{"red", 0}, {"green", 0}, {"blue", 0}};

    unsigned sum = 0;
    for( auto& line: lines) {
        line.erase(0, line.find(": ") + 2);
        const auto items = split(line, "; ");
        for (auto& item : items) {
                const auto colors = split(item, ", ");
                for (auto &color : colors) {
                       const auto nums = split(color, " ");
                       colors_max[nums[1]] = std::max(colors_max.at(nums[1]),std::stoi(nums[0]));
                       }
                } 
                sum += colors_max["red"] * colors_max["green"] * colors_max["blue"];
                colors_max["red"] = colors_max["green"] = colors_max["blue"] = 0;
    }

    print(sum);

    return 0;
}
