struct Solution;

impl Solution {
    pub fn contains_nearby_duplicate(nums: Vec<i32>, k: i32) -> bool {
        use std::collections::HashSet;
        let k = k as usize;
        let mut seen = HashSet::with_capacity(k + 1);

        for (i, &num) in nums.iter().enumerate() {
            if !seen.insert(num) {
                return true;
            }
            if i + 1 > k {
                seen.remove(&nums[i - k]);
            }
        }
        false
    }
}

fn main() {
    let samples = vec![
        (vec![1, 2, 3, 1], 3, true),
        (vec![1, 0, 1, 1], 1, true),
        (vec![1, 2, 3, 1, 2, 3], 2, false),
    ];

    for (idx, (nums, k, expected)) in samples.into_iter().enumerate() {
        let result = Solution::contains_nearby_duplicate(nums.clone(), k);
        println!("Sample {}: nums = {:?}, k = {}", idx + 1, nums, k);
        println!("Placeholder result: {}", result);
        println!("Expected output: {}\\n", expected);
    }
}
