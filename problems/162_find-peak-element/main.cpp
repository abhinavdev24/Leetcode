#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    int findPeakElement(std::vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1])
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<int>, int>> samples = {
        {{1, 2, 3, 1}, 2},
        {{1, 2, 1, 3, 5, 6, 4}, 5},
    };

    for (const auto &[nums, expected] : samples)
    {
        auto input = nums;
        int result = solution.findPeakElement(input);

        std::cout << "input: nums = [";
        for (size_t i = 0; i < nums.size(); ++i)
        {
            std::cout << nums[i] << (i + 1 < nums.size() ? "," : "");
        }
        std::cout << "]"
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
