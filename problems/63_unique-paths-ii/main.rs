struct Solution;

impl Solution {
    pub fn unique_paths_with_obstacles(obstacle_grid: Vec<Vec<i32>>) -> i32 {
        let rows = obstacle_grid.len();
        if rows == 0 {
            return 0;
        }
        let cols = obstacle_grid[0].len();
        let mut dp = vec![vec![-1; cols]; rows];
        for row in 0..rows {
            for col in 0..cols {
                if obstacle_grid[row][col] == 1 {
                    dp[row][col] = 0;
                    continue;
                }
                if row == 0 && col == 0 {
                    dp[0][0] = 1;
                    continue;
                }
                let top = if row > 0 { dp[row - 1][col] } else { 0 };
                let left = if col > 0 { dp[row][col - 1] } else { 0 };
                dp[row][col] = top + left;
            }
        }
        dp[rows - 1][cols - 1]
    }

    pub fn unique_paths_with_obstacles_2(obstacle_grid: Vec<Vec<i32>>) -> i32 {
        let rows = obstacle_grid.len();
        if rows == 0 {
            return 0;
        }
        let cols = obstacle_grid[0].len();
        let mut dp = vec![vec![-1; cols]; rows];
        Self::solve(&obstacle_grid, rows - 1, cols - 1, &mut dp)
    }

    fn solve(grid: &Vec<Vec<i32>>, row: usize, col: usize, dp: &mut Vec<Vec<i32>>) -> i32 {
        if row >= grid.len() || col >= grid[0].len() {
            return 0;
        }
        if grid[row][col] == 1 {
            return 0;
        }
        if row == 0 && col == 0 {
            return 1;
        }
        if dp[row][col] != -1 {
            return dp[row][col];
        }
        let top = if row > 0 {
            Self::solve(grid, row - 1, col, dp)
        } else {
            0
        };
        let left = if col > 0 {
            Self::solve(grid, row, col - 1, dp)
        } else {
            0
        };
        dp[row][col] = top + left;
        dp[row][col]
    }
}

fn main() {
    let samples = vec![
        (vec![vec![0, 0, 0], vec![0, 1, 0], vec![0, 0, 0]], 2),
        (vec![vec![0, 1], vec![0, 0]], 1),
    ];

    for (obstacle_grid, expected) in samples {
        let result = Solution::unique_paths_with_obstacles(obstacle_grid.clone());
        println!("Input: obstacleGrid = {:?}", obstacle_grid);
        println!("Placeholder result: {result}");
        println!("Expected output: {expected}\n");
    }
}
