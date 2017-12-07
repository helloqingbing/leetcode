#include <vector>
#include <iostream>
using namespace std;

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {

    int a[] = { 0, 1 ,2 ,1, 1, 2, 2, 2, 0, 0, 2, 1};

    int i0 = 0, i2 = sizeof(a)/sizeof(a[0]) - 1;
    for(int i = 0; i < i2;) {
        if(a[i] == 0) {
            swap(a[i0++], a[i++]); 
        } else if (a[i] == 2) {
            swap(a[i2--], a[i]);
        } else {
            i++;
        }
    }

    for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        cout << a[i] << ", "; 
    }
    cout <<endl;
    

    return 0;
}
