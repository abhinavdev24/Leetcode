struct Solution;

impl Solution {
    pub fn max_area(height: Vec<i32>) -> i32 {
        // TODO: Implement the two-pointer solution.
        todo!("Implement max_area");
    }
}

fn main() {
    let samples = vec![
        (vec![1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
        (vec![1, 1], 1),
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let result = Solution::max_area(input);
        println!("Sample {}: result={}, expected={}", idx + 1, result, expected);
    }
}
