struct Solution;

impl Solution {
    pub fn minimum_total(triangle: Vec<Vec<i32>>) -> i32 {
        let rows = triangle.len();
        if rows == 0 {
            return 0;
        }
        let mut dp = triangle[rows - 1].clone();
        for row in (0..rows - 1).rev() {
            for col in 0..=row {
                dp[col] = triangle[row][col] + dp[col].min(dp[col + 1]);
            }
        }
        dp[0]
    }

    pub fn minimum_total_2(triangle: Vec<Vec<i32>>) -> i32 {
        let rows = triangle.len();
        if rows == 0 {
            return 0;
        }
        let mut dp = Vec::with_capacity(rows);
        for i in 0..rows {
            dp.push(vec![i32::MAX; triangle[i].len()]);
        }
        dp[0][0] = triangle[0][0];
        for row in 1..rows {
            for col in 0..triangle[row].len() {
                let top = if col < triangle[row - 1].len() {
                    dp[row - 1][col]
                } else {
                    i32::MAX
                };
                let topleft = if col > 0 {
                    dp[row - 1][col - 1]
                } else {
                    i32::MAX
                };
                dp[row][col] = top.min(topleft) + triangle[row][col];
            }
        }
        let mut res = i32::MAX;
        for &val in &dp[rows - 1] {
            res = res.min(val);
        }
        res
    }

    pub fn minimum_total_3(triangle: Vec<Vec<i32>>) -> i32 {
        let rows = triangle.len();
        if rows == 0 {
            return 0;
        }
        let mut dp = Vec::with_capacity(rows);
        for i in 0..rows {
            dp.push(vec![i32::MAX; triangle[i].len()]);
        }
        let mut res = i32::MAX;
        for col in 0..triangle[rows - 1].len() {
            res = res.min(Self::rec(&triangle, rows - 1, col, &mut dp));
        }
        res
    }

    fn rec(tri: &Vec<Vec<i32>>, row: usize, col: usize, dp: &mut Vec<Vec<i32>>) -> i32 {
        if row >= tri.len() || col >= tri[row].len() {
            return i32::MAX;
        }
        if row == 0 && col == 0 {
            return tri[0][0];
        }
        if dp[row][col] != i32::MAX {
            return dp[row][col];
        }
        let top = Self::rec(tri, row - 1, col, dp);
        let topleft = if col > 0 {
            Self::rec(tri, row - 1, col - 1, dp)
        } else {
            i32::MAX
        };
        dp[row][col] = top.min(topleft) + tri[row][col];
        dp[row][col]
    }
}

fn main() {
    let samples = vec![
        (
            vec![vec![2], vec![3, 4], vec![6, 5, 7], vec![4, 1, 8, 3]],
            11,
        ),
        (vec![vec![-10]], -10),
    ];

    for (triangle, expected) in samples {
        let result = Solution::minimum_total(triangle.clone());
        println!("Input: triangle = {:?}", triangle);
        println!("Placeholder result: {result}");
        println!("Expected output: {expected}\n");
    }
}
