struct Solution;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut single = 0;
        for &i in &nums {
            single ^= i;
        }
        single
    }
}

fn main() {
    let test_cases = vec![vec![2, 2, 1], vec![4, 1, 2, 1, 2], vec![1]];
    let expected = [1, 4, 1];

    for (idx, nums) in test_cases.into_iter().enumerate() {
        let result = Solution::single_number(nums);
        println!(
            "Sample {}: result={}, expected={}",
            idx + 1,
            result,
            expected[idx]
        );
    }
}
