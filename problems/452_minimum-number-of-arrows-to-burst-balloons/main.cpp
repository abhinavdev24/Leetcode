#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });

        int arrows = 1;
        int prevEnd = points[0][1];

        // Count the number of non-overlapping intervals
        for (int i = 1; i < points.size(); ++i)
        {
            if (points[i][0] > prevEnd)
            {
                arrows++;
                prevEnd = points[i][1];
            }
        }

        return arrows;
    }
};

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
        ss << "[" << data[i][0] << ", " << data[i][1] << "]";
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<vector<int>>> samples = {
        {{10, 16}, {2, 8}, {1, 6}, {7, 12}},
        {{1, 2}, {3, 4}, {5, 6}, {7, 8}},
        {{1, 2}, {2, 3}, {3, 4}, {4, 5}}};
    vector<int> expected = {2, 4, 2};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<vector<int>> points = samples[i];
        int result = sol.findMinArrowShots(points);

        cout << "Sample " << (i + 1) << ": points = " << vec2d_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << result << "\n";
        cout << "Expected output: " << expected[i] << "\n\n";
    }

    return 0;
}
