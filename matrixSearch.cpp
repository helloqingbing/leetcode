#include <vector>
#include <iostream>
using namespace std;

vector< vector<int> > matrixSearch(int A[][], int m, int n, int target) {
    vector< vector<int>> res;
    if(m == 0 && n ==0) return res.push_back({-1, -1});
    for(int j = n -1; j >= 0; ) {
        for(int i = 0; i <= m - 1; ) {
            if(i == m -1 || j = n -1 ) return res;
            if(A[i][j] > target) {
                 j--;
            } else if(A[i][j] == target) {
                res.push_back({i, j});
            } else {
                i ++;
            }
        }
    }
    return res;
}
int main() {
    A[][] = {
        {1, 3, 5, 6, 8, 10},
        {2, 4, 8, 9, 10, 12},
        {3, 8, 9, 10, 12, 15},
        {4, 10, 17, 19, 20, 23}
    };
    vector< vector<int> > res;
    res = matrixSearch(A, 4, 6, 8);
    vector< vector<int> >::iterator iter = res.begin();
    while(res != res.end()) {
        cout << res[0] << ", " << res[1] <endl;
    }
    return 1;
}
