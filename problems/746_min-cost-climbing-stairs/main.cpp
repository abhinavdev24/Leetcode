#include <iostream>
#include <vector>

class Solution
{
public:
    int minCostClimbingStairs(std::vector<int> &cost)
    {
        std::vector<int> dp(cost.size() + 1, INT_MAX);
        if (cost.size() == 1)
            return cost[0];
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= cost.size(); i++)
            dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        return dp[cost.size()];
    }
    int minCostClimbingStairs_2(std::vector<int> &cost)
    {
        if (cost.size() == 1)
            return cost[0];
        int prev_2 = 0;
        int prev_1 = 0;
        int curr = 0;
        for (int i = 2; i <= cost.size(); i++)
        {
            curr = std::min(prev_1 + cost[i - 1], prev_2 + cost[i - 2]);
            prev_2 = prev_1;
            prev_1 = curr;
        }
        return curr;
    };
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<int>, int>> samples = {
        {{10, 15, 20}, 15},
        {{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, 6},
    };

    for (const auto &[cost, expected] : samples)
    {
        std::vector<int> input = cost;
        int result = solution.minCostClimbingStairs(input);
        std::cout << "input: cost = [";
        for (std::size_t i = 0; i < cost.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << ",";
            }
            std::cout << cost[i];
        }
        std::cout << "], placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
