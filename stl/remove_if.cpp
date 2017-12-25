#include <iostream>     // std::cout
#include <vector>
#include <algorithm>    // std::remove_if
using namespace std;

bool IsOdd (int i) { return ((i%2)==1); }

int main () {
    int myints[] = {1,2,3,4,5,6,7,8,9};            // 1 2 3 4 5 6 7 8 9

    vector<int> vint(myints, myints + sizeof(myints)/sizeof(int));
    cout << "Before size: " << vint.size() <<endl;
    vector<int>::iterator itor = vint.begin();
    for(; itor != vint.end(); itor++) {
        cout << *itor <<", ";
    }
    cout <<endl<<endl;

    remove_if(vint.begin(), vint.end(), IsOdd);
    cout << "After remove_if size: " << vint.size() <<endl;

    for(itor = vint.begin(); itor != vint.end(); itor++) {
        cout << *itor <<", ";
    }
    cout <<endl<<endl;;

    vint.clear();
    vint.assign(myints, myints + sizeof(myints)/sizeof(int));

    vint.erase(remove_if(vint.begin(), vint.end(), IsOdd), vint.end());
    for(itor = vint.begin(); itor != vint.end(); itor++) {
        cout << *itor <<", ";
    }
    cout <<endl;
    cout << "After erase size: " << vint.size() <<endl<<endl;
    return 0;
}
