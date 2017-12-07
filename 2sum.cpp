#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

vector<int> toSum(vector<int> &num, int target) {
    map<int, int> mapping;
    vector<int> result;
    for(int i = 0; i < num.size(); i++) {
        int rem = target - num[i];
        if(mapping.find(rem) != mapping.end()) {
            result.push_back(mapping[rem]);
            result.push_back(i);
            return result;
        }
        mapping[num[i]] = i;
    }
    return result;
}


vector<vector<int> > Tsum(vector<int> &num, int target) {

    vector<vector<int> > result;
    if(num.size() < 3 ) return result;
    sort(num.begin(), num.end());
    vector<int>::iterator last = num.end();
    for(vector<int>::iterator a = num.begin(); a < prev(last,2); a++) {
        vector<int>::iterator b = next(a);
        vector<int>::iterator c = prev(last);
        while(b < c) {
            if(*a + *b + *c < target) { ++b; }
            else if(*a + *b + *c > target) { --c; }
            else {
                result.push_back({*a, *b, *c}); ++b; --c; }
        }
    }
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}
    

int main() {
    int arr[] = {2, 7, 11, 15, 6};
    vector<int> num(arr, arr + sizeof(arr)/ sizeof(arr[0]));
    vector<int> ret = toSum(num, 8);
    cout << "Return : "<< ret[0] << "," << ret[1] <<endl;
    vector<vector<int> > ret2 = Tsum(num, 15);
    cout << "Return : "<< ret[0][0] << "," << ret[0][1] << "," << ret[0][2] <<endl;
    return 1;
}
