#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size(), count = 0, maxCount = INT_MIN;

        if (n == 0)
            return 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++)
        {

            if (i == 0)
            {
                count++;
            }
            else if (nums[i] == nums[i - 1])
                continue;

            else if (nums[i] == (nums[i - 1] + 1))
            {
                count++;
            }
            else
            {
                maxCount = max(maxCount, count);
                count = 1;
            }
        }
        maxCount = max(maxCount, count);
        return maxCount;
    }
};

string vec_to_string(const vector<int> &nums)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << nums[i];
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<int>> samples = {
        {100, 4, 200, 1, 3, 2},
        {0, 3, 7, 2, 5, 8, 4, 6, 0, 1},
        {1, 0, 1, 2}};
    vector<int> expected = {4, 9, 3};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i];
        int result = sol.longestConsecutive(nums);

        cout << "Sample " << (i + 1) << ": nums = " << vec_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << result << "\n";
        cout << "Expected output: " << expected[i] << "\n\n";
    }

    return 0;
}
