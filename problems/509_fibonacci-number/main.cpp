#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    std::vector<int> dp;
    int fibrec(int n)
    {
        if (dp[n] != -1)
            return dp[n];
        if (n == 0 or n == 1)
            dp[n] = n;
        else
            dp[n] = fibrec(n - 1) + fibrec(n - 2);
        return dp[n];
    }
    int fib_3(int n)
    {
        if (n == 0 || n == 1)
            return n;
        int prev_1 = 0, prev_2 = 1, fibo = 1;
        for (int i = 2; i <= n; i++)
        {
            fibo = prev_1 + prev_2;
            prev_1 = prev_2;
            prev_2 = fibo;
        }
        return fibo;
    }
    int fib_2(int n)
    {
        dp.assign(n + 1, -1);
        return fibrec(n);
    }
    int fib(int n)
    {
        if (n == 0 || n == 1)
            return n;
        return fib(n - 1) + fib(n - 2);
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<int, int>> samples = {
        {2, 1},
        {3, 2},
        {4, 3},
    };

    for (const auto &[n, expected] : samples)
    {
        int result = solution.fib(n);
        std::cout << "input: n = " << n
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
