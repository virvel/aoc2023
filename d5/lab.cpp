#include <vector>
#include <util.h>

int main () {


    std::vector<unsigned> lut(100);
    std::generate(lut.begin(), lut.end(), [n = 0] () mutable { return n++; });
   
    std::vector<int> d { 50, 98, 2};
    
    print(lut);
    int n = 0;
    for (int i = d[1]; i < (d[1]+d[2]); i++) {
        lut[i] = d[0]+n; 
        n++;
     }
    d = {52, 50, 48};
    n = 0;
    for (int i = d[1]; i < (d[1]+d[2]); i++) {
        lut[i] = d[0]+n; 
        n++;
     }
    print(lut);
}
