struct Solution;

impl Solution {
    pub fn max_sub_array(nums: Vec<i32>) -> i32 {
        let mut curr_sum = 0;
        let mut max_sum = i32::MIN;
        for &num in &nums {
            curr_sum = std::cmp::max(curr_sum + num, num);
            max_sum = std::cmp::max(max_sum, curr_sum);
        }
        max_sum
    }
}

fn main() {
    let nums1 = vec![-2, 1, -3, 4, -1, 2, 1, -5, 4];
    let expected1 = 6;
    let result1 = Solution::max_sub_array(nums1);
    println!("Sample 1 result: {}, expected: {}", result1, expected1);

    let nums2 = vec![1];
    let expected2 = 1;
    let result2 = Solution::max_sub_array(nums2);
    println!("Sample 2 result: {}, expected: {}", result2, expected2);

    let nums3 = vec![5, 4, -1, 7, 8];
    let expected3 = 23;
    let result3 = Solution::max_sub_array(nums3);
    println!("Sample 3 result: {}, expected: {}", result3, expected3);
}
