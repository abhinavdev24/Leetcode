#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    std::vector<int> dp;
    int climb(int n)
    {
        if (dp[n] != -1)
            return dp[n];
        if (n == 0 || n == 1)
            return dp[n] = 1;
        return dp[n] = climb(n - 1) + climb(n - 2);
    }
    int climbStairs(int n)
    {
        dp.assign(n + 1, -1);
        return climb(n);
    }
    int climbStairs_2(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        int prev_1 = 1, prev_2 = 1, curr = 1;
        for (int i = 2; i <= n; i++)
        {
            curr = prev_1 + prev_2;
            prev_1 = prev_2;
            prev_2 = curr;
        }
        return curr;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<int, int>> samples = {
        {2, 2},
        {3, 3},
    };

    for (const auto &[n, expected] : samples)
    {
        int result = solution.climbStairs(n);
        std::cout << "input: n = " << n
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
