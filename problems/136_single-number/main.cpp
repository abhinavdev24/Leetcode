#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int single = 0;
        for (auto i : nums)
            single = single ^ i;
        return single;
    }
};

int main()
{
    Solution solution;

    vector<vector<int>> test_cases = {
        {2, 2, 1},
        {4, 1, 2, 1, 2},
        {1}};
    vector<int> expected = {1, 4, 1};

    for (size_t i = 0; i < test_cases.size(); ++i)
    {
        vector<int> nums = test_cases[i];
        int result = solution.singleNumber(nums);
        cout << "Sample " << (i + 1) << ": result=" << result
             << ", expected=" << expected[i] << '\n';
    }

    return 0;
}
