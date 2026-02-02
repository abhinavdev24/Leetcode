#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> res;
        if (nums.size() == 0)
            return res;
        int start = 0, i = 1;
        auto pushRange = [&](int start, int end)
        {
            if (start == end)
                res.push_back(to_string(nums[start]));
            else
                res.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
        };

        while (i < nums.size())
        {
            if (nums[i] == nums[i - 1] + 1)
            {
                i++;
                continue;
            };
            pushRange(start, i - 1);
            start = i;
            i++;
        }

        pushRange(start, i - 1);
        return res;
    }
};

string ints_to_string(const vector<int> &nums)
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

string strings_to_string(const vector<string> &values)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << '"' << values[i] << '"';
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<int>> samples = {
        {0, 1, 2, 4, 5, 7},
        {0, 2, 3, 4, 6, 8, 9}};
    vector<vector<string>> expected = {
        {"0->2", "4->5", "7"},
        {"0", "2->4", "6", "8->9"}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i];
        vector<string> result = sol.summaryRanges(nums);

        cout << "Sample " << (i + 1) << ": nums = " << ints_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << strings_to_string(result) << "\n";
        cout << "Expected output: " << strings_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
