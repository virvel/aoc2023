#include "util.h"

struct item {
    std::string number;
    int lineNumber;
    size_t start;
    size_t end;
    bool valid = false;
};

struct pt {

    int x;
    int y;

    pt(int xx, int yy) {
        x = xx;
        y = yy;
    }

    bool operator==(const pt& other) const {
        return ( x == other.x and y == other.y);
    }

};

struct MyHash
{
    std::size_t operator()(const pt& p) const noexcept
    {
        std::size_t a = std::hash<int>{}(p.x);
        std::size_t b = std::hash<int>{}(p.y);
        return a >= b ? a * a + a + b : a + b * b;
    }
};

using hm = std::unordered_multimap<pt, int, MyHash>;

bool scanLine(std::string str, std::string symbols) {
    print(str);
    const auto result = std::find_first_of(str.begin(), str.end(), symbols.begin(), symbols.end());
    return (result == str.end()) ? false : true;
}

void scan(item token, std::vector<std::string> lines, hm *hm) {
    const std::string symbols = "*";
    const auto min = std::max<int>(0, token.start-1);
    const auto max = std::min<int>(lines[0].length()-1, token.end+1);
    const auto lnum = token.lineNumber;
    const auto begin = std::max(lines.begin() + lnum - 1, lines.begin());
    const auto end = std::min(lines.begin() + lnum + 2, lines.end());

    int l = lnum == 0 ? lnum + 1 : lnum;
    for (auto &line : std::vector<std::string>(begin, end)) {
        const auto result = std::find_first_of(line.begin()+min, line.begin()+max, symbols.begin(), symbols.end());
        if (result != (line.begin()+max)) {
            int x = result - line.begin();
            hm->insert({pt(x,l),std::stoi(token.number)});
        }
        l++;
    }

}

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);
    const std::string digits = "0123456789";

    for (auto &l:lines) print(l);

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

    for (auto & g : gears)
    {
        int prod = 1;
        auto bucket = gears.bucket(g.first);
        if (gears.bucket_size(bucket) == 2) {
            auto it = gears.begin(bucket);
            while (it != gears.end(bucket)) 
                prod *= (*it++).second;
            sum += prod;
        }

    }
        
    print(sum/2);

    return 0;
}
