#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int buy1 = INT_MIN, sell1 = 0;
        int buy2 = INT_MIN, sell2 = 0;

        for (int p : prices)
        {
            buy1 = max(buy1, -p);         // best after 1st buy
            sell1 = max(sell1, buy1 + p); // best after 1st sell
            buy2 = max(buy2, sell1 - p);  // best after 2nd buy
            sell2 = max(sell2, buy2 + p); // best after 2nd sell
        }
        return sell2;
    }
    int maxProfit_2(vector<int> &prices)
    {
        // next[canBuy][txLeft], curr[canBuy][txLeft]
        int next[2][3] = {}; // initialized to 0
        int curr[2][3] = {};

        for (int i = (int)prices.size() - 1; i >= 0; --i)
        {
            for (int txLeft = 1; txLeft <= 2; ++txLeft)
            {
                // canBuy = 1
                curr[1][txLeft] = max(
                    -prices[i] + next[0][txLeft],
                    next[1][txLeft]);

                // canBuy = 0
                curr[0][txLeft] = max(
                    prices[i] + next[1][txLeft - 1],
                    next[0][txLeft]);
            }
            // move curr -> next
            for (int b = 0; b < 2; ++b)
                for (int t = 0; t < 3; ++t)
                    next[b][t] = curr[b][t];
        }
        return next[1][2];
    }
    int maxProfit_3(vector<int> &prices)
    {
        int n = (int)prices.size();

        // dp[i][canBuy][txLeft]
        vector<vector<vector<int>>> dp(n + 1,
                                       vector<vector<int>>(2, vector<int>(3, 0)));

        // dp[n][*][*] already 0; dp[*][*][0] already 0

        for (int i = n - 1; i >= 0; --i)
        {
            for (int txLeft = 1; txLeft <= 2; ++txLeft)
            {
                // canBuy = 1
                dp[i][1][txLeft] = max(
                    -prices[i] + dp[i + 1][0][txLeft], // buy
                    dp[i + 1][1][txLeft]               // skip
                );

                // canBuy = 0 (holding)
                dp[i][0][txLeft] = max(
                    prices[i] + dp[i + 1][1][txLeft - 1], // sell (consume 1 tx)
                    dp[i + 1][0][txLeft]                  // hold
                );
            }
        }

        return dp[0][1][2];
    }
    int maxProfit_4(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, INT_MIN)));
        return rec(prices, 0, 1, 2, dp);
    }
    int rec(vector<int> &prices, int idx, int canBuy, int txLeft,
            vector<vector<vector<int>>> &dp)
    {
        if (idx == (int)prices.size() || txLeft == 0)
            return 0;

        int &ans = dp[idx][canBuy][txLeft];
        if (ans != INT_MIN)
            return ans;

        if (canBuy)
        {
            int buy = -prices[idx] + rec(prices, idx + 1, 0, txLeft, dp);
            int skip = rec(prices, idx + 1, 1, txLeft, dp);
            ans = max(buy, skip);
        }
        else
        {
            int sell = prices[idx] + rec(prices, idx + 1, 1, txLeft - 1, dp);
            int hold = rec(prices, idx + 1, 0, txLeft, dp);
            ans = max(sell, hold);
        }
        return ans;
    }
};

int main()
{
    Solution solution;

    vector<pair<vector<int>, int>> samples = {
        {{3, 3, 5, 0, 0, 3, 1, 4}, 6},
        {{1, 2, 3, 4, 5}, 4},
        {{7, 6, 4, 3, 1}, 0},
    };

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> prices = samples[i].first;
        int expected = samples[i].second;
        int result = solution.maxProfit(prices);
        cout << "Example " << (i + 1) << " result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
