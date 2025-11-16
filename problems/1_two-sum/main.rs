use std::collections::HashMap;
struct Solution;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        // TODO: implement this method
        let mut map = HashMap::new();
        for (i, &num) in nums.iter().enumerate() {
            let need = target - num;
            if let Some(&idx) = map.get(&need) {
                return vec![idx as i32, i as i32];
            }
            map.insert(num, i);
        }
        Vec::new()
    }
}

fn main() {
    let samples = vec![(vec![2, 7, 11, 15], 9), (vec![3, 2, 4], 6), (vec![3, 3], 6)];
    let expected = vec![vec![0, 1], vec![1, 2], vec![0, 1]];

    for (i, (nums, target)) in samples.iter().enumerate() {
        let result = Solution::two_sum(nums.clone(), *target);
        println!("Sample {}: nums = {:?}, target = {}", i + 1, nums, target);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\n", expected[i]);
    }
}
