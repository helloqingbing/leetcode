#include <array>
#include <iostream>
using namespace std;

int main() {
    array<int, 10> myArr= {1 , 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for(int &i : myArr) {
        cout<< " " << i;
    }
    cout <<endl;

    return 0;
}



