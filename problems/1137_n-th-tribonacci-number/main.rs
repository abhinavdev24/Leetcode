struct Solution;

impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        if n == 0 {
            return 0;
        }
        if n == 1 || n == 2 {
            return 1;
        }
        let mut dp = vec![0; (n + 1) as usize];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;
        for i in 3..=(n as usize) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }
        dp[n as usize]
    }

    pub fn tribonacci_2(n: i32) -> i32 {
        if n == 0 {
            return 0;
        }
        if n == 1 || n == 2 {
            return 1;
        }
        let mut prev_3 = 0;
        let mut prev_2 = 1;
        let mut prev_1 = 1;
        let mut curr = 0;
        for _ in 3..=n {
            curr = prev_1 + prev_2 + prev_3;
            prev_3 = prev_2;
            prev_2 = prev_1;
            prev_1 = curr;
        }
        curr
    }
}

fn main() {
    let samples = vec![(4, 4), (25, 1_389_537)];

    for (n, expected) in samples {
        let result = Solution::tribonacci(n);
        println!(
            "input: n = {}, placeholder result: {}, expected: {}",
            n, result, expected
        );
    }
}
