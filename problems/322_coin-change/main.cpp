#include <iostream>
#include <vector>

class Solution
{
public:
    int coinChange(std::vector<int> &coins, int amount)
    {
        int INF = amount + 1;
        std::vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for (auto c : coins)
        {
            for (int i = c; i <= amount; i++)
                dp[i] = std::min(dp[i], dp[i - c] + 1);
        }
        return dp[amount] == INF ? -1 : dp[amount];
    }

    int rec(std::vector<int> &coins, int amt, std::vector<int> &dp)
    {
        if (amt == 0)
            return 0;
        if (amt < 0)
            return INT_MAX / 2; // safe INF

        if (dp[amt] != -1)
            return dp[amt]; // memo hit

        int count = INT_MAX / 2;
        for (int c : coins)
        {
            int res = rec(coins, amt - c, dp);
            count = std::min(count, res + 1);
        }

        dp[amt] = count; // memo store
        return count;
    }

    int coinChange_2(std::vector<int> &coins, int amount)
    {
        std::vector<int> dp(amount + 1, -1); // -1 = uncomputed
        int res = rec(coins, amount, dp);
        return (res >= INT_MAX / 2) ? -1 : res;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::pair<std::vector<int>, int>, int>> samples = {
        {{{1, 2, 5}, 11}, 3},
        {{{2}, 3}, -1},
        {{{1}, 0}, 0},
    };

    for (const auto &sample : samples)
    {
        std::vector<int> coins = sample.first.first;
        int amount = sample.first.second;
        int expected = sample.second;
        int result = solution.coinChange(coins, amount);

        std::cout << "Input: coins = [";
        for (size_t i = 0; i < coins.size(); ++i)
        {
            std::cout << coins[i];
            if (i + 1 < coins.size())
            {
                std::cout << ",";
            }
        }
        std::cout << "], amount = " << amount << '\n';
        std::cout << "Placeholder result: " << result << '\n';
        std::cout << "Expected output: " << expected << "\n\n";
    }

    return 0;
}
