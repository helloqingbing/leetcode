#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))

int largest(vector<int> &height) {
    stack<int> s;
    height.push_back(0);
    int result = 0;
    for(int i = 0; i < height.size();) {
        if(s.empty() || height[i] > height[s.top()])
            s.push(i++);
        else {
            int tmp = s.top();
            s.pop();
            result = max(result, height[tmp] * (s.empty() ? i : i - s.top() -1));
        }
    }
    return result;
}

int main()
{
    int a[] = { 2, 1, 5, 6, 7, 2 ,3};
    vector<int> height(a, a + 7);
    int res = largest(height);
    cout<<"res: " << res <<endl;
    return 1;
}
