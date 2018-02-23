#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool isPalindrome(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int left = 0, right = s.length() - 1;    
    while(left < right) {
        if(!::isalnum(s[left])) ++left;
        else if(!::isalnum(s[right])) --right;
        else if(s[left] != s[right]) return false;
        else { ++left; --right; }
    }
    return true;
}

int main() {
    string s = "A man, a plan, a canal: Panama";
    bool is = isPalindrome(s);
    cout << "s is:" << is <<endl;
    return 0;
}
