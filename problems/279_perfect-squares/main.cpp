#include <iostream>

using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        int max_sq_root = sqrt(n);
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= max_sq_root; i++)
        {
            int sq = i * i;
            for (int j = sq; j <= n; j++)
                dp[j] = min(dp[j], dp[j - sq] + 1);
        }
        return dp[n];
    }
};

int main()
{
    Solution sol;

    {
        int n = 12;
        int expected = 3;
        int result = sol.numSquares(n);
        cout << "Sample 1 -> placeholder result: " << result
             << ", expected: " << expected << '\n';
    }

    {
        int n = 13;
        int expected = 2;
        int result = sol.numSquares(n);
        cout << "Sample 2 -> placeholder result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
