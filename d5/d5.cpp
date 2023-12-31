#include "util.h"

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

auto to_int_vec(std::vector<std::string> &v) {
    std::vector<unsigned> d(v.size());
    auto stoi = [](auto &s) {return std::stoul(s);};
    std::transform(v.begin(), v.end(), d.begin(), stoi);
    return d;
}

int main(int argc, char *argv[]) {
    
    auto input = readfile(argv[1]);
    std::vector<unsigned> seeds;

    auto tokens = split(input,":");
    auto seedtemp1 = split(tokens[1], "\n");
    auto seedtemp2 = split(seedtemp1[0], " ");
    seeds = to_int_vec(seedtemp2);

    for (auto &s: seeds) {
        for(unsigned t = 2; t < tokens.size(); ++t) {
            auto lines = split(tokens[t], "\n");
            
            for (unsigned i = 0; i < lines.size(); ++i) {
                auto digits = split(lines[i], " ");
                if (is_number(digits[0])) { 
                    auto d = to_int_vec(digits);
                    unsigned long dest = d[0], src = d[1], size = d[2];

                    if (unsigned diff = s - src; s >= src and diff < size) {
                        s = dest + diff;
                        break;
                    }
                } 
            }
        }
    }
            
    print(*std::min_element(seeds.begin(), seeds.end()));
    
}
