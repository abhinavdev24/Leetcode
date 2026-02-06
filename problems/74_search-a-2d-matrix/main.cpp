#include <iostream>
#include <vector>

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int start = 0, end = m * n - 1;
        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            int r = mid / n, c = mid % n;
            if (matrix[r][c] == target)
                return true;
            else if (matrix[r][c] > target)
                end = mid - 1;
            else
                start = mid + 1;
        }
        return false;
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        std::vector<std::vector<int>> matrix{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 3;
        bool expected = true;
        Solution sol;
        bool result = sol.searchMatrix(matrix, target);
        std::cout << "Sample 1 result: " << result << ", expected: " << expected << "\n";
    }

    {
        std::vector<std::vector<int>> matrix{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 13;
        bool expected = false;
        Solution sol;
        bool result = sol.searchMatrix(matrix, target);
        std::cout << "Sample 2 result: " << result << ", expected: " << expected << "\n";
    }

    return 0;
}
