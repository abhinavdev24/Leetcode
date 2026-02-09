struct Solution;

impl Solution {
    pub fn fib(n: i32) -> i32 {
        if n == 0 || n == 1 {
            return n;
        }
        Self::fib(n - 1) + Self::fib(n - 2)
    }

    pub fn fib_2(n: i32) -> i32 {
        let mut dp = vec![-1; (n + 1) as usize];
        Self::fibrec(n, &mut dp)
    }

    fn fibrec(n: i32, dp: &mut Vec<i32>) -> i32 {
        if dp[n as usize] != -1 {
            return dp[n as usize];
        }
        if n == 0 || n == 1 {
            dp[n as usize] = n;
        } else {
            dp[n as usize] = Self::fibrec(n - 1, dp) + Self::fibrec(n - 2, dp);
        }
        dp[n as usize]
    }

    pub fn fib_3(n: i32) -> i32 {
        if n == 0 || n == 1 {
            return n;
        }
        let mut prev_1 = 0;
        let mut prev_2 = 1;
        let mut fibo = 1;
        for _ in 2..=n {
            fibo = prev_1 + prev_2;
            prev_1 = prev_2;
            prev_2 = fibo;
        }
        fibo
    }
}

fn main() {
    let samples = vec![(2, 1), (3, 2), (4, 3)];

    for (n, expected) in samples {
        let result = Solution::fib(n);
        println!(
            "input: n = {}, placeholder result: {}, expected: {}",
            n, result, expected
        );
    }
}
