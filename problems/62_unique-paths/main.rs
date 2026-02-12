struct Solution;

impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let m = m as usize;
        let n = n as usize;
        let mut dp = vec![vec![-1; n]; m];
        if m == 1 && n == 1 {
            return 1;
        }
        dp[0][0] = 1;
        for row in 0..m {
            for col in 0..n {
                if row == 0 && col == 0 {
                    continue;
                }
                let top = if row > 0 { dp[row - 1][col] } else { 0 };
                let left = if col > 0 { dp[row][col - 1] } else { 0 };
                dp[row][col] = top + left;
            }
        }
        dp[m - 1][n - 1]
    }

    pub fn unique_paths_2(m: i32, n: i32) -> i32 {
        let m = m as usize;
        let n = n as usize;
        let mut dp = vec![vec![-1; n]; m];
        Self::rec(m - 1, n - 1, &mut dp)
    }

    fn rec(row: usize, col: usize, dp: &mut Vec<Vec<i32>>) -> i32 {
        if row >= dp.len() || col >= dp[0].len() {
            return 0;
        }
        if dp[row][col] != -1 {
            return dp[row][col];
        }
        if row == 0 && col == 0 {
            dp[0][0] = 1;
            return 1;
        }
        dp[row][col] = Self::rec(row.wrapping_sub(1), col, dp) + Self::rec(row, col.wrapping_sub(1), dp);
        dp[row][col]
    }
}

fn main() {
    let samples = vec![(3, 7, 28), (3, 2, 3)];

    for (m, n, expected) in samples {
        let result = Solution::unique_paths(m, n);
        println!("Input: m = {m}, n = {n}");
        println!("Placeholder result: {result}");
        println!("Expected output: {expected}\n");
    }
}
