#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
            return 0;
        int jumps = 0, curr = 0, reach = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            reach = max(reach, i + nums[i]);
            if (i == curr)
            {
                jumps++;
                curr = reach;
                if (curr >= n - 1)
                    break;
            }
        }
        return jumps;
    }
    int jump_2(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
            return 0;
        int MAX = 1e8;
        vector<int> dp(n + 1, MAX);
        dp[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 1; j <= nums[i] && i + j < n; j++)
            {
                dp[i] = min(dp[i], dp[i + j] + 1);
            }
        }
        return dp[0];
    }
};

int main()
{
    Solution solution;

    vector<vector<int>> test_cases = {
        {2, 3, 1, 1, 4},
        {2, 3, 0, 1, 4}};
    vector<int> expected = {2, 2};

    for (size_t i = 0; i < test_cases.size(); ++i)
    {
        vector<int> nums = test_cases[i];
        int result = solution.jump(nums);
        cout << "Sample " << (i + 1) << ": result=" << result
             << ", expected=" << expected[i] << '\n';
    }

    return 0;
}
