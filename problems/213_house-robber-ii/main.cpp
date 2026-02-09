#include <iostream>
#include <vector>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        std::vector<int> dp1(nums.size()), dp2(nums.size() + 1);
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return std::max(nums[0], nums[1]);
        return std::max(rob_helper(nums, 0), rob_helper(nums, 1));
    }
    int rob_helper(std::vector<int> &nums, int start)
    {
        int end = start == 0 ? nums.size() - 2 : nums.size() - 1;
        std::vector<int> dp(nums.size() + 1);
        if (end - start == 0)
            return nums[start]; // only one element
        if (end - start == 1)
            return std::max(nums[start], nums[end]); // two elements
        dp[start] = nums[start];
        dp[start + 1] = std::max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++)
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        return dp[end];
    }
    int rob_helper_2(std::vector<int> &nums, int start)
    {
        int end = start == 0 ? nums.size() - 2 : nums.size() - 1;
        int prev1 = 0;
        int prev2 = 0;
        int curr = 0;
        for (int i = start; i <= end; i++)
        {
            curr = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<int>, int>> samples = {
        {{2, 3, 2}, 3},
        {{1, 2, 3, 1}, 4},
        {{1, 2, 3}, 3},
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
