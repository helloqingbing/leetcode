#include <vector>
#include <iostream>
using namespace std;

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        vector<int>::iterator itm = nums1.begin(), itn = nums2.begin();
        while( itm != nums1.end() && itn != nums2.end()) {
            if(*itm > *itn) {
                itm = nums1.insert(itm, *itn);
                itn++;
            } else {
                itm++;
            }
        }
        while(itn != nums2.end()) {
            nums1.push_back(*itn);
            itn++;
        }
        
        if((m+n)%2 == 0) {
            return (nums1[(m+n)/2 - 1] + nums1[(m+n)/2])/2.0;
        } else {
            return (nums1[(m+n +1)/2 - 1]);
        }
 
    }


int main() {
    int n1[] = {1, 2, 5};
    int n2[] = {3, 4, 8, 12, 34};
    vector<int> nums1(n1, n1 + sizeof(n1)/sizeof(n1[0]));
    vector<int> nums2(n2, n2 + sizeof(n2)/sizeof(int));

    double ret = findMedianSortedArrays(nums1,nums2);
    cout << ret <<endl;
   return 0; 
}
