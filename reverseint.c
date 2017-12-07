#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <list>
using namespace std;
int reverse(int x) {
    if(x > INT_MAX  || x < INT_MIN)  return 0;

    int sign;
    if((sign = x) < 0) {
        x = -x;
    }
    char d[32] = {'\0'};
    snprintf(d, 32, "%d", x);

    char *str = d;
    list<char> ll;
    while(*str != '\0') {
        ll.push_back(*str);
        str++;
    }
    ll.reverse();

    list<char>::iterator it = ll.begin();
    int i = 0;
    while(it != ll.end()) {
        d[i] = *it;
        it++;
        i++;
    }
    if(sign < 0) return -atoll(d);
    return atoll(d); 
}


int main() {
    int i = 1534236469;
    //    cout << reverse(i) <<endl;
    printf("%d\n", reverse(i));
    return 0;
}
