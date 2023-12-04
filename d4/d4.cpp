#include "util.h"

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);    
    unsigned sum = 0;

    for (auto& l : lines) {
        auto line = l.erase(0, l.find_first_of(":")+1);
        auto stacks = split(line,"|");
        
        const auto wins = split(stacks[0], " ");
        const auto mycards = split(stacks[1], " ");
        
        std::vector<int> cards (mycards.size());
        std::vector<int> winners (wins.size());

        {
            auto stoi = [](auto &a) {return std::stoi(a);};
            std::transform(mycards.begin(), mycards.end(), cards.begin(),  stoi);
            std::transform(wins.begin(), wins.end(), winners.begin(),  stoi);
        }
       
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
