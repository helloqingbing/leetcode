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

string longestPalindrome2(string s) {
    int min_start = 0;
    int max_len = 1;
    for(int i = 0; i < s.size(); /* tricky*/ )
    {
        //set up the initial point
        int j = i; //tail
        int k = i; //head
        
        while(k < s.size()-1 && s[k+1] == s[k]) ++k; //grow the head
        i = k+1; //increament
        while( k < s.size()-1 && j > 0 && s[k+1] == s[j-1])
        {
            ++k; //grow the head
            --j; //expand the tail
        }
        int new_len = k - j + 1;
        if(new_len > max_len) { min_start = j; max_len = new_len;}
    }
    return s.substr(min_start, max_len); //intesting function
    
}



int main() {
    string str = "abcdcbdpcdudcpdbc";
    string lg = longestPalindrom(str);
    string lg2 = longestPalindrom(str);
    cout << "longestPalidrom : " << lg <<endl;
    cout << "longestPalidrom : " << lg2 <<endl;
    return 0;
}
