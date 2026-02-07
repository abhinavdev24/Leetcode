#include <iostream>
#include <tuple>
#include <vector>

class Solution
{
public:
    int search(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        if (n == 0)
        {
            return -1;
        }
        int low = 0, high = n - 1;
        int first = nums[0];
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int value = nums[mid];
            if (value == target)
            {
                return mid;
            }
            bool am_big = value >= first;
            bool target_big = target >= first;
            if (am_big == target_big)
            {
                if (value < target)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            else
            {
                if (am_big)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution solution;
    std::vector<std::tuple<std::vector<int>, int, int>> samples = {
        {{4, 5, 6, 7, 0, 1, 2}, 0, 4},
        {{4, 5, 6, 7, 0, 1, 2}, 3, -1},
        {{1}, 0, -1},
    };

    for (const auto &[nums, target, expected] : samples)
    {
        auto input = nums;
        int result = solution.search(input, target);

        std::cout << "input: nums = [";
        for (size_t i = 0; i < nums.size(); ++i)
        {
            std::cout << nums[i] << (i + 1 < nums.size() ? "," : "");
        }
        std::cout << "], target = " << target
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
