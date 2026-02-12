#include <iostream>
#include <vector>

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, -1));
        if (m == 1 && n == 1)
            return 1;
        dp[0][0] = 1;
        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (row == 0 && col == 0)
                {
                    dp[0][0] = 1;
                    continue;
                }
                int top = row - 1 >= 0 ? dp[row - 1][col] : 0;
                int left = col - 1 >= 0 ? dp[row][col - 1] : 0;
                dp[row][col] = top + left;
            }
        }

        return dp[m - 1][n - 1];
    }
    int rec(int row, int col, std::vector<std::vector<int>> &dp)
    {
        if (row < 0 || col < 0)
            return 0;
        if (dp[row][col] != -1)
            return dp[row][col];
        if (row == 0 && col == 0)
            return dp[0][0] = 1;
        return dp[row][col] = rec(row - 1, col, dp) + rec(row, col - 1, dp);
    }

    int uniquePaths_2(int m, int n)
    {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, -1));
        return rec(m - 1, n - 1, dp);
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::pair<int, int>, int>> samples = {
        {{3, 7}, 28},
        {{3, 2}, 3},
    };

    for (const auto &sample : samples)
    {
        int m = sample.first.first;
        int n = sample.first.second;
        int expected = sample.second;
        int result = solution.uniquePaths(m, n);
        std::cout << "Input: m = " << m << ", n = " << n << '\n';
        std::cout << "Placeholder result: " << result << '\n';
        std::cout << "Expected output: " << expected << "\n\n";
    }

    return 0;
}
