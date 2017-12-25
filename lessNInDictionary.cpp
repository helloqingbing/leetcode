#include <iostream>
using namespace std;
/*
题目具体输出举例：N=121

0
1
10
100
101
……
108
109
11
110
111
……

118
119
12
120
121
13
……

19
2
20
21
22
23
24
25
26
27
28
29
3
30
……
*/

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
