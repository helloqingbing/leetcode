#include <vector>
#include <iostream>
using namespace std;


int rotateSearch(vector<int> &num, int target, int len) {
    if( 0 >= len) return -1;
    int left = 0, right = len - 1;
    while( left < right ) {
        int mid = ( left + right ) / 2;
        if( num[mid] == target ) return mid;
        if( num[left] <= num[mid]) {
            if( num[left] <= target && target < num[mid]) {
                right = mid + 1;
            } else {
                left = mid;
            }
        } else {
            if( num[mid] <= target && target < num[right]) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}


int main() {

    int a[] = { 8, 9, 10, 2, 3, 5, 6, 7};
    vector<int> num(a, a + sizeof(a)/sizeof(a[0]));
    int pos = rotateSearch(num, 10, sizeof(a)/sizeof(a[0]));
    cout << "10's pos is : " << pos <<endl;
    return 0;
}
