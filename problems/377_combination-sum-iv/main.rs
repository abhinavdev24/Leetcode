struct Solution;

impl Solution {
    pub fn combination_sum4(nums: Vec<i32>, target: i32) -> i32 {
        if target < 0 {
            return 0;
        }
        let t = target as usize;
        let mut dp = vec![0i32; t + 1];
        let maxint = i32::MAX as u64;
        dp[0] = 1;

        for rem in 1..=t {
            for &x in nums.iter() {
                let x_us = x as usize;
                if rem >= x_us {
                    let total = dp[rem] as u64 + dp[rem - x_us] as u64;
                    dp[rem] = if total > maxint { i32::MAX } else { total as i32 };
                }
            }
        }

        dp[t]
    }
}

fn main() {
    let samples: Vec<((Vec<i32>, i32), i32)> = vec![((vec![1, 2, 3], 4), 7), ((vec![9], 3), 0)];

    for (idx, ((nums, target), expected)) in samples.iter().enumerate() {
        let result = Solution::combination_sum4(nums.clone(), *target);
        println!(
            "Example {} result: {}, expected: {}",
            idx + 1,
            result,
            expected
        );
    }
}
