#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 2)
            return x;

        int l = 1, r = x / 2;
        int ans = 0;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (mid <= x / mid)
            { // mid*mid <= x (safe)
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::pair<int, int>> samples = {
        {4, 2},
        {8, 2},
    };

    for (const auto &[x, expected] : samples)
    {
        int result = solution.mySqrt(x);
        std::cout << "input: x = " << x
                  << ", placeholder result: " << result
                  << ", expected: " << expected << '\n';
    }

    return 0;
}
