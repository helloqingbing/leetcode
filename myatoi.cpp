#include <string>
#include "limits.h"
#include <iostream>
using namespace std;

int myAtoi(const string &str) {
    int num = 0;
    int sign = 1;
    const int n = str.length();
    int i = 0;
    while (str[i] == ' ' && i < n) i++;
    if (str[i] == '+') {
        i++;
    } else if (str[i] == '-') {
        sign = -1;
        i++; }
    for (; i < n; i++) {
        if (str[i] < '0' || str[i] > '9')
            break;
        if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
            return sign == -1 ? INT_MIN : INT_MAX;
        }
        num = num * 10 + str[i] - '0';
    }
    return num * sign;
}


int main() {
    const string str = "+234234";
    cout << myAtoi(str)<<endl;
    return 0;
}
