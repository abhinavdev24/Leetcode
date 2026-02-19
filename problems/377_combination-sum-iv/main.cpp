#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        vector<int> dp(target + 1, 0);
        unsigned long long maxint = INT_MAX;
        dp[0] = 1;
        for (int rem = 1; rem <= target; ++rem)
        {
            for (int x : nums)
            {
                if (rem >= x)
                {
                    unsigned long long total = (unsigned long long)dp[rem] + dp[rem - x];
                    if (total > maxint)
                        dp[rem] = INT_MAX;
                    else
                        dp[rem] = total;
                }
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution solution;

    vector<pair<pair<vector<int>, int>, int>> samples = {
        {{{1, 2, 3}, 4}, 7},
        {{{9}, 3}, 0},
    };

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i].first.first;
        int target = samples[i].first.second;
        int expected = samples[i].second;
        int result = solution.combinationSum4(nums, target);

        cout << "Example " << (i + 1) << " result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
