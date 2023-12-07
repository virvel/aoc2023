#include "util.h"


int main(int argc, char *argv[]) {

    //unsigned long maxtime = 71530, distance = 940200;
    unsigned long long maxtime = 44806572, distance = 208158110501102;
    unsigned long long prod = 1;
    unsigned sum = 0;
    for (unsigned long i = 0; i < maxtime; ++i) {
        auto travel = (i * (maxtime - i));
            if (travel > distance)
                sum++;
    }
    prod*=sum;
    print(prod);
}
