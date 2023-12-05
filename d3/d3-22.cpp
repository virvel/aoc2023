#include "util.h"

struct item {
    std::string number;
    int lineNumber;
    size_t start;
    size_t end;
    bool valid = false;
};

struct pt {
    unsigned x,y;
    pt(unsigned xx, unsigned yy) {x = xx, y = yy;}
    bool operator==(const pt& other) const {return ( x == other.x and y == other.y);}
};

template <>
struct std::hash<pt>
{
    unsigned long operator()(const pt& p) const {
        unsigned long a = static_cast<unsigned long>(p.x);
        unsigned long b = static_cast<unsigned long>(p.y);
        return (a << 16) | b;
    } 
};

using hm = std::unordered_multimap<pt, unsigned>;

void scan(item token, std::vector<std::string> lines, hm *hm) {
    const std::string symbols = "*";
    const auto min = std::max<int>(0, token.start-1);
    const auto max = std::min<int>(lines[0].length()-1, token.end+1);
    const auto lnum = token.lineNumber;
    const auto begin = std::max(lines.begin() + lnum - 1, lines.begin());
    const auto end = std::min(lines.begin() + lnum + 2, lines.end());

    int l = lnum == 0 ? lnum + 1 : lnum;
    for (auto &line : std::vector<std::string>(begin, end)) {
        auto pos = line.begin()+min;
        while (pos < line.begin()+max) {
            const auto result = std::find_first_of(pos, line.begin()+max, symbols.begin(), symbols.end());
            if (result != (line.begin()+max)) {
                int x = std::distance(line.begin(),result);
                hm->insert({pt((unsigned)x,(unsigned)l),std::stoi(token.number)});
                break;
            }
            pos = result + 1;
        }
        l++;
    }
}

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);
    const std::string digits = "0123456789";

    hm gears;

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
                    scan(token, lines, &gears); 
                }
            }
            pos = result + digits.size();
        }
    }
    unsigned long sum = 0;
    
    for(const auto& [key,value] : gears) {
        unsigned prod = 1;
        auto range = gears.equal_range(key);
        if (std::distance(range.first, range.second) == 2) {
            for (auto it = range.first; it != range.second; ++it) {
                prod *= (*it).second;
            }
        sum += prod;
        }
    }
     
    print(sum/2);
}
