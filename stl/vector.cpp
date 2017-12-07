#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        vector<int>::iterator v = nums.begin();
        int i = 0;
        while(v != nums.end()) {
            vector<int>::iterator it = v + 1;
            int j = i + 1;
            while(it != nums.end()) {
                if(*it + *v == target) {
                    ret.push_back(i);
                    ret.push_back(j);
                    break;
                } 
                j++;
                it++;
            } 
            i++;
            v++;
        }
        return ret;
}

int main() {
    vector<int> vec;
    int i;

    vector<int> vc(4);
    vc[0] = 2;
    vc[1] = 3;
    vc[2] = 5;
    vc[3] = 7;
    int target = 10;
    vector<int> ret(2);
    ret = twoSum(vc, 10);
    
    cout << "[" << ret[0] << "," << ret[1] <<"]"<<endl;
    cout<<"vector size is ="<<vec.size()<<endl;

    for(i = 0; i < 5; i++) {
        vec.push_back(i);
    }

    cout<<"Extended vector size = "<<vec.size()<<endl;

    for(i = 0;i < 5; i++) {
        cout<<"Value of vec [" <<i<<"]="<<vec[i]<<endl;
    }

    vector<int>::iterator v = vec.begin();
    while(v != vec.end()) {
        cout << "value of v = " << *v <<endl;
        v++;
    }

    vector<int>::reverse_iterator rv = vec.rbegin();
    while(rv != vec.rend()) {
        cout << "Value of v = " << *rv <<endl;
        rv++;
    }
    cout<<vec.max_size()<<endl;
    cout<<vec.capacity()<<endl;
    cout<<"Empty vector" << vec.empty() << ", len: " << vec.size()<<endl;
    cout<<vec.front()<<endl;
    cout<<vec.back()<<endl;
    return 0;

}
