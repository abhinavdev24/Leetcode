#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int n = (int)intervals.size();
        if (n == 0)
            return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        merged.reserve(n);
        merged.push_back(intervals[0]);
        int currEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            if (currEnd >= intervals[i][0])
            {
                if (intervals[i][1] > currEnd)
                {
                    currEnd = intervals[i][1];
                    merged.back()[1] = currEnd;
                }
            }
            else
            {
                merged.push_back(intervals[i]);
                currEnd = intervals[i][1];
            }
        }
        return merged;
    }
};

string intervals_to_string(const vector<vector<int>> &intervals)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < intervals.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << "[" << intervals[i][0] << ", " << intervals[i][1] << "]";
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<vector<int>>> samples = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{1, 4}, {4, 5}},
        {{4, 7}, {1, 4}}};
    vector<vector<vector<int>>> expected = {
        {{1, 6}, {8, 10}, {15, 18}},
        {{1, 5}},
        {{1, 7}}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<vector<int>> intervals = samples[i];
        vector<vector<int>> result = sol.merge(intervals);

        cout << "Sample " << (i + 1) << ": intervals = " << intervals_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << intervals_to_string(result) << "\n";
        cout << "Expected output: " << intervals_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
