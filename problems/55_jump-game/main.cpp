#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int n = nums.size();
        int reach = 0;
        for (int i = 0; i < n; i++)
        {
            if (i > reach)
                return false;
            reach = max(reach, i + nums[i]);
            if (reach >= n - 1)
                return true;
        }
        return true;
    }
    bool canJump_2(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
            return true;
        vector<bool> dp(n + 1, false);
        dp[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 1; j <= nums[i] && i + j < n; j++)
            {
                if (dp[i + j])
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
    bool canJump_3(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
            return true;
        vector<bool> dp(n + 1, false);
        dp[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 1; j <= nums[i] && i + j < n; j++)
                if (dp[i + j])
                    dp[i] = true;
        }
        return dp[0];
    }
    bool canJump_4(vector<int> &nums)
    {
        if (nums.size() <= 1)
            return true;
        vector<int> dp(nums.size() + 1, -1);
        return rec(nums, 0, dp);
    }
    bool rec(vector<int> &nums, int index, vector<int> &dp)
    {
        if (index >= nums.size() - 1)
            return true;
        if (dp[index] != -1)
            return dp[index];
        bool possible = false;
        for (int i = 1; i <= nums[index]; i++)
        {
            possible = possible || rec(nums, index + i, dp);
            if (possible)
                return dp[index] = true;
        }
        return dp[index] = possible;
    }
};

int main()
{
    Solution solution;

    vector<vector<int>> test_cases = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4}};
    vector<bool> expected = {true, false};

    for (size_t i = 0; i < test_cases.size(); ++i)
    {
        vector<int> nums = test_cases[i];
        bool result = solution.canJump(nums);
        cout << "Sample " << (i + 1) << ": result=" << boolalpha << result
             << ", expected=" << expected[i] << '\n';
    }

    return 0;
}
