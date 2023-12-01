#include <fstream>
#include <memory>
#include <iostream>


int main() {

    std::ifstream input ("input", std::ios::binary);
    if (input) {
        input.seekg(0,input.end);
        int length = input.tellg();
        input.seekg(0, input.beg);

        auto buffer = std::make_unique<char[]>(length);
        input.read (buffer.get(),length);

        input.close();

        int first = 255, last;
        auto buf = buffer.get();
        unsigned long sum =0;
        for (int i = 0;i < length; i++) {
            auto character = buf[i];
            if (character == '\n') { 
                sum += first * 10 + last;
                first = 255;
            }
            auto digit = character - 48;
            if (digit >= 0 && digit <= 9) {
                if (first > 9)  
                    first = digit;
                last = digit;
            }
        }
        std::cout << sum << std::endl;
    } 
    return 0;
}
