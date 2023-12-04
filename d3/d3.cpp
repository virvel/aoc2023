#include "util.h"

struct item {
    std::string number;
    size_t lineNumber;
    size_t start;
    size_t end;
    bool valid = false;
};

bool scanLine(std::string str, std::string symbols) {
    const auto result = std::find_first_of(str.begin(), str.end(), symbols.begin(), symbols.end());
    return (result == str.end()) ? false : true;
}

bool scan(item token, std::vector<std::string> lines) {
    const std::string symbols = "#$%&*+-/=@";
    const auto min = std::max<int>(0, token.start-1);
    const auto max = std::min<int>(lines[0].length()-1, token.end+1);
    const auto lnum = token.lineNumber;
    const auto begin = std::max(lines.begin() + lnum - 1, lines.begin());
    const auto end = std::min(lines.begin() + lnum + 2, lines.end());

    for (auto &line : std::vector<std::string>(begin, end))
        if (scanLine(std::string(line.begin() + min, line.begin() + max), symbols))
            return true;

    return false;
}

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);
    const std::string digits = "0123456789";

    unsigned sum = 0;
    for (int i = 0; i < lines.size(); ++i) {
        auto line = lines[i];

        auto pos = line.begin();
        while (pos < line.end()) {
            auto const result = std::find_first_of(pos, line.end(), digits.begin(), digits.end()); 
            std::string digits {};
            if (result != line.end()) {
                item token;
                token.lineNumber = i;
                token.start = pos - line.begin();
                while (std::isdigit(*pos)) {
                        digits.push_back(*pos);
                        pos++;
                        token.end = pos - line.begin();
                }
                if (!digits.empty()) {
                    token.number = digits;
                    token.valid = scan(token, lines); 
                    if (token.valid)
                        sum += std::stoi(token.number);
                }
            }
                pos = result + digits.size();
        }

    }
        
    print(sum);

    return 0;
}
