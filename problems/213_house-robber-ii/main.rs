struct Solution;

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 1 {
            return nums[0];
        }
        if n == 2 {
            return std::cmp::max(nums[0], nums[1]);
        }
        std::cmp::max(Self::rob_helper(&nums, 0), Self::rob_helper(&nums, 1))
    }

    fn rob_helper(nums: &Vec<i32>, start: usize) -> i32 {
        let end = if start == 0 {
            nums.len() - 2
        } else {
            nums.len() - 1
        };
        if end - start == 0 {
            return nums[start];
        }
        if end - start == 1 {
            return std::cmp::max(nums[start], nums[end]);
        }
        let mut dp = vec![0; nums.len() + 1];
        dp[start] = nums[start];
        dp[start + 1] = std::cmp::max(nums[start], nums[start + 1]);
        for i in (start + 2)..=end {
            dp[i] = std::cmp::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        dp[end]
    }

    fn rob_helper_2(nums: &Vec<i32>, start: usize) -> i32 {
        let end = if start == 0 {
            nums.len() - 2
        } else {
            nums.len() - 1
        };
        let mut prev1 = 0;
        let mut prev2 = 0;
        let mut curr = 0;
        for i in start..=end {
            curr = std::cmp::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        curr
    }
}

fn main() {
    let samples = vec![
        (vec![2, 3, 2], 3),
        (vec![1, 2, 3, 1], 4),
        (vec![1, 2, 3], 3),
    ];

    for (nums, expected) in samples {
        let result = Solution::rob(nums.clone());
        println!(
            "input: nums = {:?}, placeholder result: {}, expected: {}",
            nums, result, expected
        );
    }
}
