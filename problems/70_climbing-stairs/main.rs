struct Solution;

impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        let mut dp = vec![-1; (n + 1) as usize];
        Self::climb(n, &mut dp)
    }

    fn climb(n: i32, dp: &mut Vec<i32>) -> i32 {
        if dp[n as usize] != -1 {
            return dp[n as usize];
        }
        if n == 0 || n == 1 {
            dp[n as usize] = 1;
        } else {
            dp[n as usize] = Self::climb(n - 1, dp) + Self::climb(n - 2, dp);
        }
        dp[n as usize]
    }

    pub fn climb_stairs_2(n: i32) -> i32 {
        if n == 0 || n == 1 {
            return 1;
        }
        let mut prev_1 = 1;
        let mut prev_2 = 1;
        let mut curr = 1;
        for _ in 2..=n {
            curr = prev_1 + prev_2;
            prev_1 = prev_2;
            prev_2 = curr;
        }
        curr
    }
}

fn main() {
    let samples = vec![(2, 2), (3, 3)];

    for (n, expected) in samples {
        let result = Solution::climb_stairs(n);
        println!(
            "input: n = {}, placeholder result: {}, expected: {}",
            n, result, expected
        );
    }
}
