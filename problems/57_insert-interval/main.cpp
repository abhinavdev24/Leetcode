#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        auto pos = lower_bound(intervals.begin(), intervals.end(), newInterval);
        intervals.insert(pos, newInterval);
        int n = (int)intervals.size();
        // sort(intervals.begin(), intervals.end());
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

string interval_list_to_string(const vector<vector<int>> &intervals)
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

    vector<vector<vector<int>>> all_intervals = {
        {{1, 3}, {6, 9}},
        {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}};
    vector<vector<int>> new_intervals = {
        {2, 5},
        {4, 8}};
    vector<vector<vector<int>>> expected = {
        {{1, 5}, {6, 9}},
        {{1, 2}, {3, 10}, {12, 16}}};

    for (size_t i = 0; i < all_intervals.size(); ++i)
    {
        vector<vector<int>> intervals = all_intervals[i];
        vector<int> new_interval = new_intervals[i];
        vector<vector<int>> result = sol.insert(intervals, new_interval);

        cout << "Sample " << (i + 1) << ": intervals = " << interval_list_to_string(all_intervals[i])
             << ", newInterval = [" << new_intervals[i][0] << ", " << new_intervals[i][1] << "]\n";
        cout << "Placeholder result: " << interval_list_to_string(result) << "\n";
        cout << "Expected output: " << interval_list_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
