#include <iostream>
#include <vector>

class Solution
{
public:
    int findMin(std::vector<int> &nums)
    {
        int l = 0, r = (int)nums.size() - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] > nums[r])
            {
                l = mid + 1; // min is to the right
            }
            else
            {
                r = mid; // min is at mid or to the left
            }
        }
        return nums[l];
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<int>, int>> samples = {
        {{3, 4, 5, 1, 2}, 1},
        {{4, 5, 6, 7, 0, 1, 2}, 0},
        {{11, 13, 15, 17}, 11},
    };

    for (const auto &[nums, expected] : samples)
    {
        auto input = nums;
        int result = solution.findMin(input);

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
