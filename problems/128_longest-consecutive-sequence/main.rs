struct Solution;

impl Solution {
    pub fn longest_consecutive(mut nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 0 {
            return 0;
        }
        nums.sort();
        let mut count = 0;
        let mut max_count = 0;
        for i in 0..n {
            if i == 0 {
                count = 1;
            } else if nums[i] == nums[i - 1] {
                continue;
            } else if nums[i] == nums[i - 1] + 1 {
                count += 1;
            } else {
                max_count = max_count.max(count);
                count = 1;
            }
        }
        max_count.max(count)
    }
}

fn main() {
    let samples = vec![
        (vec![100, 4, 200, 1, 3, 2], 4),
        (vec![0, 3, 7, 2, 5, 8, 4, 6, 0, 1], 9),
        (vec![1, 0, 1, 2], 3),
    ];

    for (idx, (nums, expected)) in samples.into_iter().enumerate() {
        let result = Solution::longest_consecutive(nums.clone());

        println!("Sample {}: nums = {:?}", idx + 1, nums);
        println!("Placeholder result: {}", result);
        println!("Expected output: {}\\n", expected);
    }
}
