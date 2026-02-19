struct Solution;

impl Solution {
    pub fn can_jump(nums: Vec<i32>) -> bool {
        let n = nums.len() as i32;
        let mut reach = 0;
        for i in 0..n {
            if i > reach {
                return false;
            }
            reach = reach.max(i + nums[i as usize]);
            if reach >= n - 1 {
                return true;
            }
        }
        true
    }

    pub fn can_jump_2(nums: Vec<i32>) -> bool {
        let n = nums.len();
        if n <= 1 {
            return true;
        }
        let mut dp = vec![false; n + 1];
        dp[n - 1] = true;
        for i in (0..n - 1).rev() {
            for j in 1..=nums[i] as usize {
                if i + j < n && dp[i + j] {
                    dp[i] = true;
                    break;
                }
            }
        }
        dp[0]
    }

    pub fn can_jump_3(nums: Vec<i32>) -> bool {
        let n = nums.len();
        if n <= 1 {
            return true;
        }
        let mut dp = vec![false; n + 1];
        dp[n - 1] = true;
        for i in (0..n - 1).rev() {
            for j in 1..=nums[i] as usize {
                if i + j < n && dp[i + j] {
                    dp[i] = true;
                }
            }
        }
        dp[0]
    }

    pub fn can_jump_4(nums: Vec<i32>) -> bool {
        if nums.len() <= 1 {
            return true;
        }
        let mut dp = vec![-1; nums.len() + 1];
        Self::rec(&nums, 0, &mut dp)
    }

    fn rec(nums: &Vec<i32>, index: usize, dp: &mut Vec<i32>) -> bool {
        if index >= nums.len() - 1 {
            return true;
        }
        if dp[index] != -1 {
            return dp[index] == 1;
        }
        let mut possible = false;
        for i in 1..=nums[index] as usize {
            if index + i < nums.len() {
                possible = possible || Self::rec(nums, index + i, dp);
                if possible {
                    dp[index] = 1;
                    return true;
                }
            }
        }
        dp[index] = 0;
        possible
    }
}

fn main() {
    let test_cases = vec![vec![2, 3, 1, 1, 4], vec![3, 2, 1, 0, 4]];
    let expected = [true, false];

    for (idx, nums) in test_cases.into_iter().enumerate() {
        let result = Solution::can_jump(nums);
        println!(
            "Sample {}: result={}, expected={}",
            idx + 1,
            result,
            expected[idx]
        );
    }
}
