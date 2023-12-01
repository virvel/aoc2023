#include <fstream>
#include <memory>
#include <iostream>
#include <cstring>


int main() {

    std::ifstream input ("input", std::ios::binary);
    if (input) {
       input.seekg(0,input.end);
        int length = input.tellg();
        input.seekg(0, input.beg);

        auto buffer = std::make_unique<char[]>(length);
        input.read (buffer.get(),length);

        input.close();

        unsigned long sum =0;
        int first = 255, last;
        auto buf = buffer.get();
        for (int i = 0;i < length; i++) {
            auto character = buf[i];
            if (character == '\n' or i == length -1) { 
                sum += first * 10 + last;
                first = 255;
            }
            switch (character) {
                case 'e':
                    if (i > length - 6)
                        break;
                    if (strncmp(&buf[i], "eight", 5) == 0) {
                            first = first > 9 ? 8 : first;
                            last = 8;
                    }
                    break;
                case 'f':
                    if (i > length - 5)
                        break;
                    if (strncmp(&buf[i], "four", 4) == 0) { 
                        first = first > 9 ? 4 : first;
                        last = 4;
                    }
                    else if (strncmp(&buf[i], "five", 4) == 0) {
                        first = first > 9 ? 5 : first;
                        last = 5;
                    }
                    break;
                case 't':
                    if (i > length - 4)
                        break;
                    if (strncmp(&buf[i], "two", 3) == 0) {
                        first = first > 9 ? 2 : first; 
                        last = 2;
                    }
                    if (i > length - 6)
                        break;
                    if (strncmp(&buf[i], "three",5) == 0) {
                        first = first > 9 ? 3 : first;
                        last = 3;
                    }
                    break;
                case 's':
                    if (i > length - 4)
                        break;
                    if (strncmp(&buf[i], "six", 3) == 0) {
                        first = first > 9 ? 6 : first;
                        last = 6;
                    }
                    if (i > length - 6)
                        break;
                    if (strncmp(&buf[i], "seven", 5) == 0) {
                        first = first > 9 ? 7 : first;
                        last =7;
                    }
                    break;
                case 'n':
                    if (i > length - 5)
                        break;
                    if (strncmp(&buf[i], "nine", 4) == 0) {
                        first = first > 9 ? 9 : first; 
                        last = 9;
                    }
                    break;
                case 'o':
                    if (i > length - 4)
                        break;
                    if (strncmp(&buf[i], "one", 3) == 0) {
                        first = first > 9 ? 1 : first; 
                        last = 1;
                    }
                    break;
                default:
                    break;
                    
            }
            auto digit = character - 48;
            if (digit >= 0 and digit <= 9) {
                if (first > 9)  
                    first = digit;
                last = digit;
            }
        }
    std::cout << sum << std::endl;
    } 
    return 0;
}
