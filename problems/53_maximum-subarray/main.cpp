#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxSubArray(std::vector<int> &nums)
    {
        int currSum = 0;
        int maxSum = INT_MIN;
        for (int i = 0; i < nums.size(); i++)
        {

            currSum = std::max(currSum + nums[i], nums[i]);
            maxSum = std::max(maxSum, currSum);
        }
        return maxSum;
    }
};

int main()
{
    {
        std::vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int expected = 6;
        Solution sol;
        int result = sol.maxSubArray(nums);
        std::cout << "Sample 1 result: " << result << ", expected: " << expected << "\n";
    }

    {
        std::vector<int> nums{1};
        int expected = 1;
        Solution sol;
        int result = sol.maxSubArray(nums);
        std::cout << "Sample 2 result: " << result << ", expected: " << expected << "\n";
    }

    {
        std::vector<int> nums{5, 4, -1, 7, 8};
        int expected = 23;
        Solution sol;
        int result = sol.maxSubArray(nums);
        std::cout << "Sample 3 result: " << result << ", expected: " << expected << "\n";
    }

    return 0;
}
