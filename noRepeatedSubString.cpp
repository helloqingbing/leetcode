#include <string>
#include <map>
#include <iostream>
using namespace std;

int main() {
    string s = "abcdefzfesedfsdfedcvdfe";
    const char *p = s.c_str(), *q = p;
    map<char, int> mcc;
    int cur_len = 0, max_len = 0, index = 0;
    while(*q != '\0') {
        if( mcc.find(*q) == mcc.end()) {
            mcc[*q] = index;
            cur_len++;
        } else {
            if(cur_len > max_len) {
                max_len = cur_len;
            }
            cur_len = 0;
            q = q - (index - mcc.find(*q)->second);
            index = mcc.find(*q)->second;
            mcc.clear();
        }
        q++;
        index = index + 1;
    }
    if(cur_len > max_len) {
        max_len = cur_len;
    }

    cout << "Max Len: " << max_len <<endl;
    return 0;
}
