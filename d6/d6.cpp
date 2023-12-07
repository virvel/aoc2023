#include "util.h"

int main(int argc, char *argv[]) {

//  std::vector<std::pair<int, int>> tup {{7,9}, {15,40}, {30,200}};
    std::vector<std::pair<int,int>> tup {{44,208}, {80, 1581}, {65,1050}, {72,1102}};

    unsigned prod = 1;
    for (auto &t:tup) {
        auto maxtime = std::get<0>(t), distance = std::get<1>(t);
        unsigned sum = 0;
        for (int i = 0; i < maxtime; ++i) {
            auto travel = (i * (maxtime - i));
                if (travel > distance)
                    sum++;
        }
        prod *= sum;
    }
    print(prod);
}
