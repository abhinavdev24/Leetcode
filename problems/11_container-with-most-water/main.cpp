#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int left = 0;
        int right = height.size() - 1;
        int max_area = 0;
        while (left < right)
        {
            int h = min(height[left], height[right]);
            int w = right - left;
            max_area = max(max_area, h * w);
            if (height[left] < height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
        }
        return max_area;
    }

    int maxArea2(vector<int> &height)
    {
        int maxArea = INT_MIN;
        int i = 0, j = height.size() - 1;
        while (i < j)
        {
            int currArea = (j - i) * min(height[i], height[j]);
            maxArea = max(maxArea, currArea);
            if (height[i] <= height[j])
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return maxArea;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> samples = {
        {1, 8, 6, 2, 5, 4, 8, 3, 7},
        {1, 1}};
    vector<int> expected = {49, 1};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> height = samples[i];
        int result = solution.maxArea(height);
        cout << "Sample " << (i + 1) << ": result=" << result
             << ", expected=" << expected[i] << endl;
    }

    return 0;
}
