struct Solution;

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        if nums.is_empty() {
            return 0;
        }
        let mut dp = vec![-1; nums.len()];
        Self::rec(&nums, &mut dp, nums.len() - 1)
    }

    fn rec(nums: &Vec<i32>, dp: &mut Vec<i32>, index: usize) -> i32 {
        if dp[index] != -1 {
            return dp[index];
        }
        if index == 0 {
            dp[0] = nums[0];
            return dp[0];
        }
        if index == 1 {
            dp[1] = std::cmp::max(Self::rec(nums, dp, 0), nums[1]);
            return dp[1];
        }
        dp[index] = std::cmp::max(
            Self::rec(nums, dp, index - 1),
            Self::rec(nums, dp, index - 2) + nums[index],
        );
        dp[index]
    }

    pub fn rob_2(nums: Vec<i32>) -> i32 {
        if nums.is_empty() {
            return 0;
        }
        if nums.len() == 1 {
            return nums[0];
        }
        let mut dp = vec![-1; nums.len()];
        dp[0] = nums[0];
        dp[1] = std::cmp::max(nums[0], nums[1]);
        for i in 2..nums.len() {
            dp[i] = std::cmp::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        dp[nums.len() - 1]
    }

    pub fn rob_3(nums: Vec<i32>) -> i32 {
        if nums.is_empty() {
            return 0;
        }
        if nums.len() == 1 {
            return nums[0];
        }
        let mut prev_2 = nums[0];
        let mut prev_1 = std::cmp::max(nums[0], nums[1]);
        let mut curr = prev_1;
        for i in 2..nums.len() {
            curr = std::cmp::max(prev_1, prev_2 + nums[i]);
            prev_2 = prev_1;
            prev_1 = curr;
        }
        curr
    }
}

fn main() {
    let samples = vec![(vec![1, 2, 3, 1], 4), (vec![2, 7, 9, 3, 1], 12)];

    for (nums, expected) in samples {
        let result = Solution::rob(nums.clone());
        println!(
            "input: nums = {:?}, placeholder result: {}, expected: {}",
            nums, result, expected
        );
    }
}
