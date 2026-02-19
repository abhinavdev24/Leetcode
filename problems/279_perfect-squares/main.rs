struct Solution;

impl Solution {
    pub fn num_squares(n: i32) -> i32 {
        if n <= 0 {
            return 0;
        }

        let n_us = n as usize;
        let max_sq_root = (n as f64).sqrt() as usize;
        let mut dp = vec![i32::MAX; n_us + 1];
        dp[0] = 0;

        for i in 1..=max_sq_root {
            let sq = i * i;
            for j in sq..=n_us {
                if dp[j - sq] != i32::MAX {
                    dp[j] = dp[j].min(dp[j - sq] + 1);
                }
            }
        }

        dp[n_us]
    }
}

fn main() {
    {
        let n = 12;
        let expected = 3;
        let result = Solution::num_squares(n);
        println!(
            "Sample 1 -> placeholder result: {}, expected: {}",
            result, expected
        );
    }

    {
        let n = 13;
        let expected = 2;
        let result = Solution::num_squares(n);
        println!(
            "Sample 2 -> placeholder result: {}, expected: {}",
            result, expected
        );
    }
}
