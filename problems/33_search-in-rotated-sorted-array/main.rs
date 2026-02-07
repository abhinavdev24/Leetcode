struct Solution;

impl Solution {
    pub fn search(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len();
        if n == 0 {
            return -1;
        }
        let mut low = 0;
        let mut high = n as i32 - 1;
        let first = nums[0];
        while low <= high {
            let mid = low + (high - low) / 2;
            let value = nums[mid as usize];
            if value == target {
                return mid;
            }
            let am_big = value >= first;
            let target_big = target >= first;
            if am_big == target_big {
                if value < target {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else {
                if am_big {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        -1
    }
}

fn main() {
    let samples: Vec<(Vec<i32>, i32, i32)> = vec![
        (vec![4, 5, 6, 7, 0, 1, 2], 0, 4),
        (vec![4, 5, 6, 7, 0, 1, 2], 3, -1),
        (vec![1], 0, -1),
    ];

    for (nums, target, expected) in samples {
        let result = Solution::search(nums.clone(), target);
        println!(
            "input: nums = {:?}, target = {}, placeholder result: {}, expected: {}",
            nums, target, result, expected
        );
    }
}
