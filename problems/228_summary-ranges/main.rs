struct Solution;

impl Solution {
    pub fn summary_ranges(nums: Vec<i32>) -> Vec<String> {
        let mut res = Vec::new();
        if nums.is_empty() {
            return res;
        }
        let mut start = 0;
        let mut i = 1;
        while i < nums.len() {
            if nums[i] == nums[i - 1] + 1 {
                i += 1;
                continue;
            }
            // push range
            if start == i - 1 {
                res.push(nums[start].to_string());
            } else {
                res.push(format!("{}->{}", nums[start], nums[i - 1]));
            }
            start = i;
            i += 1;
        }
        // last range
        if start == i - 1 {
            res.push(nums[start].to_string());
        } else {
            res.push(format!("{}->{}", nums[start], nums[i - 1]));
        }
        res
    }
}

fn main() {
    let samples = vec![
        (
            vec![0, 1, 2, 4, 5, 7],
            vec!["0->2".to_string(), "4->5".to_string(), "7".to_string()],
        ),
        (
            vec![0, 2, 3, 4, 6, 8, 9],
            vec![
                "0".to_string(),
                "2->4".to_string(),
                "6".to_string(),
                "8->9".to_string(),
            ],
        ),
    ];

    for (idx, (nums, expected)) in samples.into_iter().enumerate() {
        let result = Solution::summary_ranges(nums.clone());
        println!("Sample {}: nums = {:?}", idx + 1, nums);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}", expected);
    }
}
