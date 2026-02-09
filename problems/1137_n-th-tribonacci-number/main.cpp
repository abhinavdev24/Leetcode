#include <iostream>
#include <vector>

class Solution
{
public:
    int tribonacci(int n)
    {
        std::vector<int> dp(n + 1, 0);
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;
        for (int i = 3; i <= n; i++)
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        return dp[n];
    }
    int tribonacci_2(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;
        int prev_3 = 0, prev_2 = 1, prev_1 = 1, curr = 0;
        for (int i = 3; i <= n; i++)
        {
            curr = prev_1 + prev_2 + prev_3;
            prev_3 = prev_2;
            prev_2 = prev_1;
            prev_1 = curr;
        }
        return curr;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<int, int>> samples = {
        {4, 4},
        {25, 1389537},
    };

    for (const auto &[n, expected] : samples)
    {
        int result = solution.tribonacci(n);
        std::cout << "input: n = " << n
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
