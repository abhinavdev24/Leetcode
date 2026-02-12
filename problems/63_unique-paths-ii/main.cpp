#include <iostream>
#include <vector>

class Solution
{
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
    {
        int rows = obstacleGrid.size(), cols = obstacleGrid[0].size();
        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, -1));
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if (obstacleGrid[row][col])
                {
                    dp[row][col] = 0;
                    continue;
                }
                if (row == 0 && col == 0)
                {
                    dp[0][0] = 1;
                    continue;
                }
                int top = row - 1 >= 0 ? dp[row - 1][col] : 0;
                int left = col - 1 >= 0 ? dp[row][col - 1] : 0;
                dp[row][col] = top + left;
            }
        }
        return dp[rows - 1][cols - 1];
    }
    int solve(std::vector<std::vector<int>> grid, int row, int col, std::vector<std::vector<int>> &dp)
    {
        if (row < 0 || col < 0)
            return 0;
        if (grid[row][col] == 1)
            return 0;
        if (row == 0 && col == 0)
            return 1;
        if (dp[row][col] != -1)
            return dp[row][col];
        int top = solve(grid, row - 1, col, dp);
        int left = solve(grid, row, col - 1, dp);
        return dp[row][col] = top + left;
    }
    int uniquePathsWithObstacles_2(std::vector<std::vector<int>> &obstacleGrid)
    {
        int row = obstacleGrid.size(), col = obstacleGrid[0].size();
        std::vector<std::vector<int>> dp(row, std::vector<int>(col, -1));
        return solve(obstacleGrid, row - 1, col - 1, dp);
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
        {{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, 2},
        {{{0, 1}, {0, 0}}, 1},
    };

    for (const auto &sample : samples)
    {
        std::vector<std::vector<int>> obstacleGrid = sample.first;
        int expected = sample.second;
        int result = solution.uniquePathsWithObstacles(obstacleGrid);
        std::cout << "Input: obstacleGrid = ";
        printGrid(obstacleGrid);
        std::cout << '\n';
        std::cout << "Placeholder result: " << result << '\n';
        std::cout << "Expected output: " << expected << "\n\n";
    }

    return 0;
}
