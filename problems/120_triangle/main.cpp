#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumTotal(std::vector<std::vector<int>> &triangle)
    {
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();
        std::vector<int> dp = triangle.back();
        for (int row = rows - 2; row >= 0; row--)
        {
            for (int col = 0; col <= row; col++)
                dp[col] = triangle[row][col] + std::min(dp[col], dp[col + 1]);
        }
        return dp[0];
    }
    int minimumTotal_2(std::vector<std::vector<int>> &triangle)
    {
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();
        std::vector<std::vector<int>> dp(triangle.size());

        for (int i = 0; i < rows; i++)
            dp[i] = std::vector<int>(triangle[i].size(), INT_MAX);

        dp[0][0] = triangle[0][0];
        for (int row = 1; row < rows; row++)
        {
            for (int col = 0; col < dp[row].size(); col++)
            {
                int top = col < dp[row - 1].size() ? dp[row - 1][col] : INT_MAX;
                int topleft = col > 0 ? dp[row - 1][col - 1] : INT_MAX;
                dp[row][col] = std::min(top, topleft) + triangle[row][col];
            }
        }
        int res = INT_MAX;
        for (int i = 0; i < triangle[rows - 1].size(); i++)
        {
            res = std::min(res, dp[rows - 1][i]);
        }
        return res;
    }
    int rec(std::vector<std::vector<int>> &tri, int row, int col, std::vector<std::vector<int>> &dp)
    {
        if (row < 0 || col < 0 || col >= tri[row].size())
            return INT_MAX;
        if (row == 0 && col == 0)
            return tri[0][0];
        if (dp[row][col] != INT_MAX)
            return dp[row][col];
        int top = rec(tri, row - 1, col, dp);
        int topleft = rec(tri, row - 1, col - 1, dp);
        return dp[row][col] = std::min(top, topleft) + tri[row][col];
    }
    int minimumTotal_3(std::vector<std::vector<int>> &triangle)
    {
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();
        std::vector<std::vector<int>> dp(triangle.size());
        for (int i = 0; i < rows; i++)
            dp[i] = std::vector<int>(triangle[i].size(), INT_MAX);

        int res = INT_MAX;
        for (int i = 0; i < triangle[rows - 1].size(); i++)
        {
            res = std::min(res, rec(triangle, rows - 1, i, dp));
        }
        return res;
    }
};

void printTriangle(const std::vector<std::vector<int>> &triangle)
{
    std::cout << "[";
    for (size_t i = 0; i < triangle.size(); ++i)
    {
        std::cout << "[";
        for (size_t j = 0; j < triangle[i].size(); ++j)
        {
            std::cout << triangle[i][j];
            if (j + 1 < triangle[i].size())
            {
                std::cout << ",";
            }
        }
        std::cout << "]";
        if (i + 1 < triangle.size())
        {
            std::cout << ",";
        }
    }
    std::cout << "]";
}

int main()
{
    Solution solution;
    std::vector<std::pair<std::vector<std::vector<int>>, int>> samples = {
        {{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}, 11},
        {{{-10}}, -10},
    };

    for (const auto &sample : samples)
    {
        std::vector<std::vector<int>> triangle = sample.first;
        int expected = sample.second;
        int result = solution.minimumTotal(triangle);
        std::cout << "Input: triangle = ";
        printTriangle(triangle);
        std::cout << '\n';
        std::cout << "Placeholder result: " << result << '\n';
        std::cout << "Expected output: " << expected << "\n\n";
    }

    return 0;
}
