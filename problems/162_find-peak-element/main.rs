struct Solution;

impl Solution {
    pub fn find_peak_element(nums: Vec<i32>) -> i32 {
        let mut left = 0;
        let mut right = nums.len() as i32 - 1;
        while left < right {
            let mid = left + (right - left) / 2;
            if nums[mid as usize] < nums[(mid + 1) as usize] {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        left
    }
}

fn main() {
    let samples: Vec<(Vec<i32>, i32)> = vec![(vec![1, 2, 3, 1], 2), (vec![1, 2, 1, 3, 5, 6, 4], 5)];

    for (nums, expected) in samples {
        let result = Solution::find_peak_element(nums.clone());
        println!(
            "input: nums = {:?}, placeholder result: {}, expected: {}",
            nums, result, expected
        );
    }
}
