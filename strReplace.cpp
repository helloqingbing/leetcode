/*
*  Input : ABCDabcd34 54435 6ABC56*abch7123#@10@abc35dfle9AVDFE  abc jeremy
*
*
*/

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


string strReplace(string src, string rep, string target)
{
    string ret("");
    if(src.length() == 0) return ret;
    if(rep.length() == 0) return src;
    if(target.length() == 0) return src;

    int srcLen = src.length(), repLen = rep.length();
    int start = 0;
    transform(rep.begin(), rep.end(), rep.begin(), ::tolower);
    for(int i = start; i < srcLen;) {
        for(int j = 0; j < repLen; j++) {
            if( src[i] == rep[j] || src[i] + 32 == rep[j]) i++;
            else break;
        }
        if((i - start) == repLen) {
            ret += target;
            start += repLen;
        } else {
            ret += src.substr(start, i - start + 1);
            start++;
        }
        i = start;
    }
    return ret;
}

int main() {
    string str="ABCDabcd34 54435 6ABC56*abch7123#@10@abc35dfle9AVDFE";
    string rep("abc"), tgt("jeremy");
    string ret = strReplace(str, rep, tgt);
    cout << "Source string : " << str <<endl;
    cout << "Replace string: " << rep <<endl;
    cout << "Target string : " << tgt <<endl;
    cout << "Replaced done : " << ret << endl;
    return 0;
}
