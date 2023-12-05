#include "util.h"

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);    
    unsigned sum = 0;

    for (auto& l : lines) {
        auto line = l.erase(0, l.find_first_of(":")+1);
        auto stacks = split(line,"|");
        
        const auto winners = split(stacks[0], " ");
        const auto cards = split(stacks[1], " ");
       
        unsigned pts = 0;
        auto pos = cards.begin();
        while (pos < cards.end()) {
            const auto result = std::find_first_of(pos, cards.end(), winners.begin(), winners.end());
            if (result != cards.end())
                pts += 1;
            pos = result+1;
        }
        if (pts > 0) 
            sum += 1 << (pts-1);

    }
    print(sum);
}
