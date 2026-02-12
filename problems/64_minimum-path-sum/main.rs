struct Solution;

impl Solution {
    pub fn min_path_sum(grid: Vec<Vec<i32>>) -> i32 {
        let rows = grid.len();
        if rows == 0 {
            return 0;
        }
        let cols = grid[0].len();
        let mut dp = vec![0; cols];
        dp[0] = grid[0][0];
        for i in 1..cols {
            dp[i] = dp[i - 1] + grid[0][i];
        }
        for row in 1..rows {
            dp[0] += grid[row][0];
            for col in 1..cols {
                dp[col] = dp[col].min(dp[col - 1]) + grid[row][col];
            }
        }
        dp[cols - 1]
    }

    pub fn min_path_sum_2(grid: Vec<Vec<i32>>) -> i32 {
        let rows = grid.len();
        if rows == 0 {
            return 0;
        }
        let cols = grid[0].len();
        let mut dp = vec![vec![i32::MAX; cols]; rows];
        dp[0][0] = grid[0][0];
        for row in 0..rows {
            for col in 0..cols {
                if row == 0 && col == 0 {
                    continue;
                }
                let up = if row > 0 { dp[row - 1][col] } else { i32::MAX };
                let left = if col > 0 { dp[row][col - 1] } else { i32::MAX };
                dp[row][col] = up.min(left) + grid[row][col];
            }
        }
        dp[rows - 1][cols - 1]
    }
}

fn main() {
    let samples = vec![
        (vec![vec![1, 3, 1], vec![1, 5, 1], vec![4, 2, 1]], 7),
        (vec![vec![1, 2, 3], vec![4, 5, 6]], 12),
    ];

    for (grid, expected) in samples {
        let result = Solution::min_path_sum(grid.clone());
        println!("Input: grid = {:?}", grid);
        println!("Placeholder result: {result}");
        println!("Expected output: {expected}\n");
    }
}
