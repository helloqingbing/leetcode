#include <string>
#include <iostream>
#include <memory>
#include <cstring>
using namespace std;

string longestPalindrom(string s) {
    const int n = s.size();
    bool f[n][n];
    memset(&f[0][0], n*n, 0);
    int maxLen = 1, start = 0;
    for(int i = 0; i < n; i++) {
        f[i][i] = 1;
        for(int j = 0; j < i; j++) {
            f[j][i] = (s[j] == s[i] && (i - j < 2 || f[j + 1][i - 1]));
            if(f[j][i] && maxLen < (i - j + 1)) {
                maxLen = i - j + 1;
                start = j;
            }   
        }
    }
    return s.substr(start, maxLen);
}


int main() {
    string str = "abcdcbdpcdudcpdbc";
    string lg = longestPalindrom(str);
    cout << "longestPalidrom : " << lg <<endl;
    return 0;
}
