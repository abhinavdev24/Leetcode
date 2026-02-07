#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    std::vector<int> searchRange(std::vector<int> &nums, int target)
    {
        auto l = lower_bound(nums.begin(), nums.end(), target);
        auto r = upper_bound(nums.begin(), nums.end(), target);
        if (l == nums.end() || *l != target)
            return {-1, -1};
        return {(int)(l - nums.begin()), (int)(r - nums.begin() - 1)};
    }
};

int main()
{
    Solution solution;
    std::vector<std::tuple<std::vector<int>, int, std::vector<int>>> samples = {
        {{5, 7, 7, 8, 8, 10}, 8, {3, 4}},
        {{5, 7, 7, 8, 8, 10}, 6, {-1, -1}},
        {{}, 0, {-1, -1}},
    };

    for (const auto &[nums, target, expected] : samples)
    {
        auto input = nums;
        std::vector<int> result = solution.searchRange(input, target);

        std::cout << "input: nums = [";
        for (size_t i = 0; i < nums.size(); ++i)
        {
            std::cout << nums[i] << (i + 1 < nums.size() ? "," : "");
        }
        std::cout << "], target = " << target
                  << ", placeholder result: [" << result[0] << "," << result[1] << "]"
                  << ", expected: [" << expected[0] << "," << expected[1] << "]\n";
    }

    return 0;
}
