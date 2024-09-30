#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxLuckyValue(vector<int>& gems, int K) {
    int M = gems.size();
    
    // 如果不能合并成最终一个宝石，直接返回 0
    if ((M - 1) % (K - 1) != 0) {
        return -1;
    }

    // 前缀和数组，用于快速计算 sum[i][j]
    vector<int> prefixSum(M + 1, 0);
    for (int i = 0; i < M; i++) {
        prefixSum[i + 1] = prefixSum[i] + gems[i];
    }

    // dp[i][j] 表示从 i 到 j 的最大幸运值
    vector<vector<int>> dp(M, vector<int>(M, 0));

    // 区间动态规划
    for (int len = K; len <= M; len++) {  // 枚举区间长度
        for (int i = 0; i + len - 1 < M; i++) {  // 枚举起点 i
            int j = i + len - 1;  // 区间的终点 j
            dp[i][j] = INT_MIN;    // 初始为极小值

            // 枚举分割点 k, 合并 [i,k] 和 [k+1,j]
            for (int k = i; k < j; k += (K - 1)) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }

            // 如果当前区间能合并成一个宝石
            if ((j - i) % (K - 1) == 0) {
                dp[i][j] += prefixSum[j + 1] - prefixSum[i];  // 加上能量值和
            }
        }
    }

    // 返回将 0 到 M-1 这段区间合并成一个宝石的最大幸运值
    return dp[0][M - 1];
}

int main() {
    vector<int> gems = {6, 5 , 4 , 1, 0, 5 , 7};
    int K = 2;
    int result = maxLuckyValue(gems, K);
    
    if (result != -1) {
        cout << "最大幸运值为: " << result << endl;
    } else {
        cout << "无法合并成一个宝石" << endl;
    }
    return 0;
}
