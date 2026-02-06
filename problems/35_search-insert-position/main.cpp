#include <iostream>
#include <vector>

class Solution
{
public:
    int searchInsert(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (target == nums[mid])
                return mid;
            else if (target > nums[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }
};

int main()
{
    {
        std::vector<int> nums{1, 3, 5, 6};
        int target = 5;
        int expected = 2;
        Solution sol;
        int result = sol.searchInsert(nums, target);
        std::cout << "Sample 1 result: " << result << ", expected: " << expected << "\n";
    }

    {
        std::vector<int> nums{1, 3, 5, 6};
        int target = 2;
        int expected = 1;
        Solution sol;
        int result = sol.searchInsert(nums, target);
        std::cout << "Sample 2 result: " << result << ", expected: " << expected << "\n";
    }

    {
        std::vector<int> nums{1, 3, 5, 6};
        int target = 7;
        int expected = 4;
        Solution sol;
        int result = sol.searchInsert(nums, target);
        std::cout << "Sample 3 result: " << result << ", expected: " << expected << "\n";
    }

    return 0;
}
