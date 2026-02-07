struct Solution;

impl Solution {
    pub fn search_range(nums: Vec<i32>, target: i32) -> Vec<i32> {
        fn lower_bound(nums: &Vec<i32>, target: i32) -> usize {
            let mut left = 0;
            let mut right = nums.len();
            while left < right {
                let mid = left + (right - left) / 2;
                if nums[mid] < target {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            left
        }

        fn upper_bound(nums: &Vec<i32>, target: i32) -> usize {
            let mut left = 0;
            let mut right = nums.len();
            while left < right {
                let mid = left + (right - left) / 2;
                if nums[mid] <= target {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            left
        }

        let l = lower_bound(&nums, target);
        let r = upper_bound(&nums, target);
        if l < r && nums[l] == target {
            vec![l as i32, (r - 1) as i32]
        } else {
            vec![-1, -1]
        }
    }
}

fn main() {
    let samples: Vec<(Vec<i32>, i32, Vec<i32>)> = vec![
        (vec![5, 7, 7, 8, 8, 10], 8, vec![3, 4]),
        (vec![5, 7, 7, 8, 8, 10], 6, vec![-1, -1]),
        (vec![], 0, vec![-1, -1]),
    ];

    for (nums, target, expected) in samples {
        let result = Solution::search_range(nums.clone(), target);
        println!(
            "input: nums = {:?}, target = {}, placeholder result: {:?}, expected: {:?}",
            nums, target, result, expected
        );
    }
}
