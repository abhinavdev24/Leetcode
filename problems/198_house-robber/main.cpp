#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int rec(const std::vector<int> &nums, std::vector<int> &dp, int index)
    {
        if (dp[index] != -1)
            return dp[index];
        if (index == 0)
            return dp[0] = nums[0];
        if (index == 1)
            return dp[1] = std::max(rec(nums, dp, 0), nums[1]);
        return dp[index] = std::max(rec(nums, dp, index - 1), rec(nums, dp, index - 2) + nums[index]);
    }
    int rob(const std::vector<int> &nums)
    {
        std::vector<int> dp(nums.size(), -1);
        return rec(nums, dp, nums.size() - 1);
    }
    int rob_2(const std::vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        std::vector<int> dp(nums.size(), -1);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (std::size_t i = 2; i < nums.size(); ++i)
        {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp.back();
    }
    int rob_3(const std::vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        int prev_2 = nums[0];
        int prev_1 = std::max(nums[0], nums[1]);
        int curr = prev_1;
        for (std::size_t i = 2; i < nums.size(); ++i)
        {
            curr = std::max(prev_1, prev_2 + nums[i]);
            prev_2 = prev_1;
            prev_1 = curr;
        }
        return curr;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<int>, int>> samples = {
        {{1, 2, 3, 1}, 4},
        {{2, 7, 9, 3, 1}, 12},
    };

    for (const auto &[nums, expected] : samples)
    {
        std::vector<int> input = nums;
        int result = solution.rob(input);
        std::cout << "input: nums = [";
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << ",";
            }
            std::cout << nums[i];
        }
        std::cout << "], placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
