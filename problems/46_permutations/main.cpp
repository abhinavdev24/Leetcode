#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    void dfs(int idx, vector<int> &nums, vector<vector<int>> &res)
    {
        int n = (int)nums.size();
        if (idx == n)
        {
            res.push_back(nums);
            return;
        }
        for (int i = idx; i < n; ++i)
        {
            swap(nums[idx], nums[i]);
            dfs(idx + 1, nums, res);
            swap(nums[idx], nums[i]); // backtrack
        }
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        // reserve n! to reduce reallocations (n <= 6)
        int n = (int)nums.size();
        int fact = 1;
        for (int i = 2; i <= n; ++i)
            fact *= i;
        res.reserve(fact);

        dfs(0, nums, res);
        return res;
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

string vec2d_to_string(const vector<vector<int>> &data)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << vec_to_string(data[i]);
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<int>> samples = {
        {1, 2, 3},
        {0, 1},
        {1}};

    vector<vector<vector<int>>> expected = {
        {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}},
        {{0, 1}, {1, 0}},
        {{1}}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i];
        vector<vector<int>> result = sol.permute(nums);

        cout << "Sample " << (i + 1) << ": nums = " << vec_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << vec2d_to_string(result) << "\n";
        cout << "Expected output: " << vec2d_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
