#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> res;
        vector<int> cur;
        cur.reserve(k);

        auto dfs = [&](auto &&self, int start, int left) -> void
        {
            if (left == 0)
            { // picked k numbers
                res.push_back(cur);
                return;
            }
            // pruning: we need 'left' numbers, last possible start is n-left+1
            for (int x = start; x <= n - left + 1; ++x)
            {
                cur.push_back(x);
                self(self, x + 1, left - 1);
                cur.pop_back();
            }
        };

        dfs(dfs, 1, k);
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

    vector<pair<int, int>> samples = {
        {4, 2},
        {1, 1}};

    vector<vector<vector<int>>> expected = {
        {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}},
        {{1}}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        int n = samples[i].first;
        int k = samples[i].second;
        vector<vector<int>> result = sol.combine(n, k);

        cout << "Sample " << (i + 1) << ": n = " << n << ", k = " << k << "\n";
        cout << "Placeholder result: " << vec2d_to_string(result) << "\n";
        cout << "Expected output: " << vec2d_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
