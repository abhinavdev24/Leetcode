struct Solution;

impl Solution {
    pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len() as i32;
        let mut low: i32 = 0;
        let mut high: i32 = n - 1;
        while low <= high {
            let mid = low + (high - low) / 2;
            if target == nums[mid as usize] {
                return mid;
            } else if target > nums[mid as usize] {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        low
    }
}

fn main() {
    let nums1 = vec![1, 3, 5, 6];
    let target1 = 5;
    let expected1 = 2;
    let result1 = Solution::search_insert(nums1, target1);
    println!("Sample 1 result: {}, expected: {}", result1, expected1);

    let nums2 = vec![1, 3, 5, 6];
    let target2 = 2;
    let expected2 = 1;
    let result2 = Solution::search_insert(nums2, target2);
    println!("Sample 2 result: {}, expected: {}", result2, expected2);

    let nums3 = vec![1, 3, 5, 6];
    let target3 = 7;
    let expected3 = 4;
    let result3 = Solution::search_insert(nums3, target3);
    println!("Sample 3 result: {}, expected: {}", result3, expected3);
}
