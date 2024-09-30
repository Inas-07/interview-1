#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int cal(int n, int m, vector<int>& a, vector<int>& v) {
    vector<int> dp(m + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= a[i]; --j) {
            dp[j] = max(dp[j], dp[j - a[i]] + v[i]);
        }
    }

    return dp[m];
}

// 测试函数
int main() {
    int n = 4, m = 10; 
    vector<int> A = {2, 3, 4, 5};  
    vector<int> V = {1, 5, 2, 4};

    cout << cal(n, m, A, V) << endl;
    return 0;
}
