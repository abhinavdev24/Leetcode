struct Solution;

impl Solution {
    pub fn jump(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n <= 1 {
            return 0;
        }
        let mut jumps = 0;
        let mut curr = 0;
        let mut reach = 0;
        for i in 0..n - 1 {
            reach = reach.max(i + nums[i] as usize);
            if i == curr {
                jumps += 1;
                curr = reach;
                if curr >= n - 1 {
                    break;
                }
            }
        }
        jumps
    }

    pub fn jump_2(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n <= 1 {
            return 0;
        }
        let max_val = 100000000;
        let mut dp = vec![max_val; n + 1];
        dp[n - 1] = 0;
        for i in (0..n - 1).rev() {
            for j in 1..=nums[i] as usize {
                if i + j < n {
                    dp[i] = dp[i].min(dp[i + j] + 1);
                }
            }
        }
        dp[0]
    }
}

fn main() {
    let test_cases = vec![vec![2, 3, 1, 1, 4], vec![2, 3, 0, 1, 4]];
    let expected = [2, 2];

    for (idx, nums) in test_cases.into_iter().enumerate() {
        let result = Solution::jump(nums);
        println!(
            "Sample {}: result={}, expected={}",
            idx + 1,
            result,
            expected[idx]
        );
    }
}
