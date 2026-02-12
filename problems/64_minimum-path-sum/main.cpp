#include <iostream>
#include <vector>

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        std::vector<int> dp(cols);
        dp[0] = grid[0][0];
        for (int i = 1; i < cols; i++)
            dp[i] = dp[i - 1] + grid[0][i];
        for (int row = 1; row < rows; row++)
        {
            dp[0] = dp[0] + grid[row][0];
            for (int col = 1; col < cols; col++)
                dp[col] = std::min(dp[col], dp[col - 1]) + grid[row][col];
        }
        return dp[cols - 1];
    }

    int minPathSum_2(std::vector<std::vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, INT_MAX));
        dp[0][0] = grid[0][0];
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if (row == 0 && col == 0)
                {
                    dp[0][0] = grid[0][0];
                    continue;
                }
                int up = row > 0 ? dp[row - 1][col] : INT_MAX;
                int left = col > 0 ? dp[row][col - 1] : INT_MAX;
                dp[row][col] = std::min(up, left) + grid[row][col];
            }
        }
        return dp[rows - 1][cols - 1];
    }
};

void printGrid(const std::vector<std::vector<int>> &grid)
{
    std::cout << "[";
    for (size_t i = 0; i < grid.size(); ++i)
    {
        std::cout << "[";
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            std::cout << grid[i][j];
            if (j + 1 < grid[i].size())
            {
                std::cout << ",";
            }
        }
        std::cout << "]";
        if (i + 1 < grid.size())
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
        {{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}, 7},
        {{{1, 2, 3}, {4, 5, 6}}, 12},
    };

    for (const auto &sample : samples)
    {
        std::vector<std::vector<int>> grid = sample.first;
        int expected = sample.second;
        int result = solution.minPathSum(grid);
        std::cout << "Input: grid = ";
        printGrid(grid);
        std::cout << '\n';
        std::cout << "Placeholder result: " << result << '\n';
        std::cout << "Expected output: " << expected << "\n\n";
    }

    return 0;
}
