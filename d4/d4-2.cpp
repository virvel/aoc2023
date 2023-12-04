#include "util.h"

auto get_matches = [](std::vector<int> &c, std::vector<int> &w) { 
    int acc= 0;
    auto pos = c.begin();
    while (pos < c.end()) {
        const auto result = std::find_first_of(pos, c.end(), w.begin(), w.end());
        if (result != c.end())
            acc += 1;
        pos = result + 1;
    }
    return acc;
};

int main(int argc, char *argv[]) {

    auto lines = readlines(argv[1]);
    std::vector<int> cards;

    for (auto& l : lines) {
        auto line = l.erase(0, l.find_first_of(":")+1);
        auto stacks = split(line,"|");
        
        const auto wins = split(stacks[0], " ");
        const auto my_cards = split(stacks[1], " ");
        
        std::vector<int> winners (wins.size());
        std::vector<int> card (my_cards.size());

        {
            auto stoi = [](auto& a) {return std::stoi(a);};
            std::transform(wins.begin(), wins.end(), winners.begin(),  stoi);
            std::transform(my_cards.begin(), my_cards.end(), card.begin(),  stoi);
        }
        
        auto m = get_matches(card, winners);
        cards.push_back(m);
    }

    auto fin = ones<int>(cards.size());

    for (int i = 0; i < cards.size(); ++i) {
        auto matches = cards[i];
        for (int j = i+1; j < i+1+matches; ++j) {
            fin[j] += fin[i];
        }
    }

    const auto res = std::accumulate(fin.begin(), fin.end(), 0, std::plus<>());
    print(res);
}
