#include <fstream>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

string trim(string str)
{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
}

map<string, int> dataParse(string strFileName) {
    map<string, int> dataMap;
    ifstream ifile(strFileName.c_str(), ios::in);
    if(!ifile.good()) { cout << "File canot be found!" << endl; return dataMap; }

    string line;
    string item;
    while(getline(ifile, line, '\n')) {
        line = trim(line);
        while(line.length() >= 0) {
            int pos = line.find(" ");
            if(-1 == pos) {
                break;
            }
            item = trim(line.substr(0, pos));
             
            if(item.length() >= 0) {
                if(dataMap.find(item) == dataMap.end()) {
                    dataMap.insert(pair<string, int>(item, 1));
                } else {
                    dataMap[item] ++;
                }
            }
            line = trim(line.substr(line.find(" ") + 1, line.length() -1 ));
        }
    }
    return dataMap;
}

//Compile : g++ -std=c++11 -o statisticsData statisticsData.cpp

int main() {

    string file("./text.txt");
    map<string, int> ret = dataParse(file);
    for(map<string,int>::iterator itor = ret.begin(); itor != ret.end(); itor++) {
        cout << "itor[" << itor->first << "] = " << itor->second <<endl;
    }


    // Declaring the type of Predicate that accepts 2 pairs and return a bool
    typedef function<bool(pair<string, int>, pair<string, int>)> Comparator;
 
    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    Comparator compFunctor = [](pair<string, int> elem1 ,pair<string, int> elem2) {
       return elem1.second < elem2.second;
    };
 
    // Declaring a set that will store the pairs using above comparision logic
    multiset<pair<string, int>, Comparator> setOfWords(ret.begin(), ret.end(), compFunctor);
 
    // Iterate over a set using range base for loop
    // It will display the items in sorted order of values
    for (pair<string, int> element : setOfWords)
        cout << element.first << " :: " << element.second << endl;
 
    return 1;
}
