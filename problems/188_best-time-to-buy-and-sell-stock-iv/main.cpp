#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    static inline int unlimitedProfit(const vector<int> &prices)
    {
        int profit = 0;
        for (int i = 1; i < (int)prices.size(); ++i)
            if (prices[i] > prices[i - 1])
                profit += prices[i] - prices[i - 1];
        return profit;
    }

    int maxProfit(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;
        if (k >= n / 2)
            return unlimitedProfit(prices);

        vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
        for (int p : prices)
        {
            for (int t = 1; t <= k; ++t)
            {
                buy[t] = max(buy[t], sell[t - 1] - p);
                sell[t] = max(sell[t], buy[t] + p);
            }
        }
        return sell[k];
    }
    int maxProfit_2(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;
        if (k >= n / 2)
            return unlimitedProfit(prices);

        vector<int> prev(n, 0), curr(n, 0);

        for (int t = 1; t <= k; ++t)
        {
            int best = -prices[0]; // dp[t-1][0] - prices[0] (prev[0]=0)
            curr[0] = 0;
            for (int i = 1; i < n; ++i)
            {
                curr[i] = max(curr[i - 1], prices[i] + best);
                best = max(best, prev[i] - prices[i]);
            }
            prev.swap(curr);
        }
        return prev[n - 1];
    }
    int maxProfit_3(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;
        if (k >= n / 2)
            return unlimitedProfit(prices);

        vector<int> st(2 * k, INT_MIN);
        for (int p : prices)
        {
            st[0] = max(st[0], -p);        // buy1
            st[1] = max(st[1], st[0] + p); // sell1
            for (int j = 2; j < 2 * k; ++j)
            {
                if ((j & 1) == 0)
                { // buy (even)
                    st[j] = max(st[j], st[j - 1] - p);
                }
                else
                { // sell (odd)
                    st[j] = max(st[j], st[j - 1] + p);
                }
            }
        }
        return max(0, st[2 * k - 1]);
    }
    int maxProfit_4(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;
        if (k >= n / 2)
            return unlimitedProfit(prices);

        // next[canBuy][t], curr[canBuy][t]
        vector<vector<int>> next(2, vector<int>(k + 1, 0));
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));

        for (int i = n - 1; i >= 0; --i)
        {
            for (int t = 1; t <= k; ++t)
            {
                curr[1][t] = max(-prices[i] + next[0][t], next[1][t]);    // canBuy
                curr[0][t] = max(prices[i] + next[1][t - 1], next[0][t]); // holding
            }
            next.swap(curr);
        }
        return next[1][k];
    }
    int maxProfit_5(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;
        if (k >= n / 2)
            return unlimitedProfit(prices);

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, INT_MIN)));
        return rec_5(0, 1, k, prices, dp);
    }
    int rec_5(int i, int canBuy, int txLeft, const vector<int> &prices,
              vector<vector<vector<int>>> &dp)
    {
        if (i == (int)prices.size() || txLeft == 0)
            return 0;

        int &ans = dp[i][canBuy][txLeft];
        if (ans != INT_MIN)
            return ans;

        if (canBuy)
        {
            int buy = -prices[i] + rec_5(i + 1, 0, txLeft, prices, dp);
            int skip = rec_5(i + 1, 1, txLeft, prices, dp);
            ans = max(buy, skip);
        }
        else
        {
            int sell = prices[i] + rec_5(i + 1, 1, txLeft - 1, prices, dp);
            int hold = rec_5(i + 1, 0, txLeft, prices, dp);
            ans = max(sell, hold);
        }
        return ans;
    }
    int maxProfit_6(int k, vector<int> &prices)
    {
        int n = (int)prices.size();
        if (n <= 1 || k == 0)
            return 0;

        // Optimization: if k >= n/2, it's equivalent to unlimited transactions
        if (k >= n / 2)
        {
            int profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] > prices[i - 1])
                    profit += prices[i] - prices[i - 1];
            return profit;
        }

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(k + 1, INT_MIN)));

        return rec_6(0, 1, k, prices, dp);
    }
    int rec_6(int i, int canBuy, int txLeft, const vector<int> &prices,
              vector<vector<vector<int>>> &dp)
    {
        if (i == (int)prices.size() || txLeft == 0)
            return 0;

        int &ans = dp[i][canBuy][txLeft];
        if (ans != INT_MIN)
            return ans;

        if (canBuy)
        {
            int buy = -prices[i] + rec_6(i + 1, 0, txLeft, prices, dp);
            int skip = rec_6(i + 1, 1, txLeft, prices, dp);
            ans = max(buy, skip);
        }
        else
        {
            int sell = prices[i] + rec_6(i + 1, 1, txLeft - 1, prices, dp);
            int hold = rec_6(i + 1, 0, txLeft, prices, dp);
            ans = max(sell, hold);
        }
        return ans;
    }
};

int main()
{
    Solution sol;

    {
        int k = 2;
        vector<int> prices = {2, 4, 1};
        int expected = 2;
        int result = sol.maxProfit(k, prices);
        cout << "Sample 1 -> placeholder result: " << result
             << ", expected: " << expected << '\n';
    }

    {
        int k = 2;
        vector<int> prices = {3, 2, 6, 5, 0, 3};
        int expected = 7;
        int result = sol.maxProfit(k, prices);
        cout << "Sample 2 -> placeholder result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
