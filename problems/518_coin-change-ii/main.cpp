#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {

        vector<long long> dp(amount + 1, 0);

        dp[0] = 1;

        for (int x : coins)
        {
            for (int i = x; i <= amount; i++)
            {
                if (dp[i] < INT_MAX)
                    dp[i] += dp[i - x];
            }
        }

        return dp[amount];
    }
};

int main()
{
    Solution solution;

    vector<pair<pair<int, vector<int>>, int>> samples = {
        {{5, {1, 2, 5}}, 4},
        {{3, {2}}, 0},
        {{10, {10}}, 1},
    };

    for (size_t i = 0; i < samples.size(); ++i)
    {
        int amount = samples[i].first.first;
        vector<int> coins = samples[i].first.second;
        int expected = samples[i].second;

        int result = solution.change(amount, coins);
        cout << "Example " << (i + 1) << " result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
