struct Solution;

impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let mut l = 0;
        let mut r = nums.len() as i32 - 1;
        while l < r {
            let mid = l + (r - l) / 2;
            if nums[mid as usize] > nums[r as usize] {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        nums[l as usize]
    }
}

fn main() {
    let samples: Vec<(Vec<i32>, i32)> = vec![
        (vec![3, 4, 5, 1, 2], 1),
        (vec![4, 5, 6, 7, 0, 1, 2], 0),
        (vec![11, 13, 15, 17], 11),
    ];

    for (nums, expected) in samples {
        let result = Solution::find_min(nums.clone());
        println!(
            "input: nums = {:?}, placeholder result: {}, expected: {}",
            nums, result, expected
        );
    }
}
