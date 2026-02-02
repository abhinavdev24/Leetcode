#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_set<int> set;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > k)
            {
                set.erase(nums[i - k - 1]);
            }
            if (set.count(nums[i]))
                return true;
            set.insert(nums[i]);
        }
        return false;
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

string bool_to_string(bool value)
{
    return value ? "true" : "false";
}

int main()
{
    Solution sol;

    vector<vector<int>> samples = {
        {1, 2, 3, 1},
        {1, 0, 1, 1},
        {1, 2, 3, 1, 2, 3}};
    vector<int> ks = {3, 1, 2};
    vector<bool> expected = {true, true, false};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i];
        bool result = sol.containsNearbyDuplicate(nums, ks[i]);

        cout << "Sample " << (i + 1) << ": nums = " << vec_to_string(samples[i])
             << ", k = " << ks[i] << "\n";
        cout << "Placeholder result: " << bool_to_string(result) << "\n";
        cout << "Expected output: " << bool_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
