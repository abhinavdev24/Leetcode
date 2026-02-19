struct Solution;

impl Solution {
    pub fn max_area(height: Vec<i32>) -> i32 {
        if height.len() < 2 {
            return 0;
        }
        let mut left: usize = 0;
        let mut right: usize = height.len() - 1;
        let mut max_area: i32 = 0;

        while left < right {
            let h = height[left].min(height[right]);
            let w = (right - left) as i32;
            max_area = max_area.max(h * w);

            if height[left] < height[right] {
                left += 1;
            } else {
                right -= 1;
            }
        }

        max_area
    }

    pub fn max_area2(height: Vec<i32>) -> i32 {
        if height.len() < 2 {
            return 0;
        }
        let mut max_area = i32::MIN;
        let mut i: usize = 0;
        let mut j: usize = height.len() - 1;

        while i < j {
            let curr_area = ((j - i) as i32) * height[i].min(height[j]);
            max_area = max_area.max(curr_area);
            if height[i] <= height[j] {
                i += 1;
            } else {
                j -= 1;
            }
        }

        max_area
    }
}

fn main() {
    let samples = vec![
        (vec![1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
        (vec![1, 1], 1),
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let r1 = Solution::max_area(input.clone());
        let r2 = Solution::max_area2(input);
        println!(
            "Sample {}: max_area={}, max_area2={}, expected={}",
            idx + 1,
            r1,
            r2,
            expected
        );
    }
}
