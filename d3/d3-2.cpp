#include "util.h"

struct item {
    std::string number;
    size_t lineNumber;
    size_t start;
    size_t end;
    bool valid = false;
};

auto scan(std::vector<std::string> &lines, size_t lineNumber, size_t start, size_t end) {
    const std::string symbols = "0123456789";
    const auto min = std::max<int>(0, start);
    const auto max = std::min<int>(lines[0].length()-1, end);

    const auto lbegin = std::max(lines.begin() + lineNumber - 1, lines.begin());
    const auto lend = std::min(lines.begin() + lineNumber + 2, lines.end());

    for (auto &line : std::vector<std::string>(lbegin, lend)) {
        const auto res = std::find_first_of(line.begin()+min, line.begin()+max, symbols.begin(), symbols.end());
        if (res != (line.begin()+max))
            print(*res, res-line.begin());
    }
    return false;
}

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);
    const std::string symbols = "*";
    
    for(auto &line : lines) print(line);

    for (int i = 0; i < lines.size(); ++i) {
        auto line = lines[i];
        int linenumber = i;
        int xcoord = 0;
        auto pos = line.begin();
        while (pos < line.end()) {
            auto const result = std::find_first_of(pos, line.end(), symbols.begin(), symbols.end()); 
            if (result != line.end()) {
                xcoord = result - line.begin();
                scan(lines, linenumber, xcoord-1, xcoord+2);
                pos = result;
            }
            pos++;
        }
    } 
    return 0;
}
