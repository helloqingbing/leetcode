#include <iostream>
using namespace std;

int dump(long long n) {
    long long total = 0;
    long long begin = 0;

    while( total < n) {
        if( begin <=n ) {
            cout << begin <<endl;
            total++;

            if(begin == 0) ++begin;
            else begin *= 10;

        }
        else {
            begin = begin/10 + 1;
            while(begin != 0 && begin %10 == 0) {
                begin /= 10;
            }
        }
    }
    return 0;
}


int main() {
    long long i = 150; 
    int ret = dump(i);
    return 0;
}
