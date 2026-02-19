#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profit = 0;
        for (int i = 0; i < prices.size() - 1; i++)
        {
            if (prices[i] < prices[i + 1])
                profit += prices[i + 1] - prices[i];
        }
        return profit;
    }
    int maxProfit_2(vector<int> &prices)
    {
        vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
        for (int i = prices.size() - 1; i >= 0; i--)
        {
            dp[i][1] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = max(prices[i] + dp[i + 1][1], dp[i + 1][0]);
        }
        return dp[0][1];
    }
    int maxProfit_3(vector<int> &prices)
    {
        vector<vector<int>> dp(prices.size(), vector<int>(2, INT_MIN));
        return rec(prices, 0, true, dp);
    }
    int rec(vector<int> &prices, int index, bool canBuy, vector<vector<int>> &dp)
    {
        if (index == prices.size())
            return 0;
        if (dp[index][canBuy] != INT_MIN)
            return dp[index][canBuy];
        if (canBuy)
        { // not holding a stock
            int buy = -prices[index] + rec(prices, index + 1, false, dp);
            int notbuy = rec(prices, index + 1, true, dp);
            return dp[index][canBuy] = max(buy, notbuy);
        }
        else
        { // holding a stock
            int sell = prices[index] + rec(prices, index + 1, true, dp);
            int notsell = rec(prices, index + 1, false, dp);
            return dp[index][canBuy] = max(sell, notsell);
        }
    }
};

int main()
{
    Solution solution;

    vector<vector<int>> test_cases = {
        {7, 1, 5, 3, 6, 4},
        {1, 2, 3, 4, 5},
        {7, 6, 4, 3, 1}};
    vector<int> expected = {7, 4, 0};

    for (size_t i = 0; i < test_cases.size(); ++i)
    {
        vector<int> prices = test_cases[i];
        int result = solution.maxProfit(prices);
        cout << "Sample " << (i + 1) << ": result=" << result
             << ", expected=" << expected[i] << '\n';
    }

    return 0;
}
