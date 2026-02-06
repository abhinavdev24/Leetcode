struct Solution;

impl Solution {
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        fn dfs(idx: usize, nums: &mut Vec<i32>, res: &mut Vec<Vec<i32>>) {
            if idx == nums.len() {
                res.push(nums.clone());
                return;
            }
            for i in idx..nums.len() {
                nums.swap(idx, i);
                dfs(idx + 1, nums, res);
                nums.swap(idx, i);
            }
        }

        let mut res = Vec::new();
        let mut nums = nums;
        dfs(0, &mut nums, &mut res);
        res
    }
}

fn main() {
    let samples = vec![
        (
            vec![1, 2, 3],
            vec![
                vec![1, 2, 3],
                vec![1, 3, 2],
                vec![2, 1, 3],
                vec![2, 3, 1],
                vec![3, 1, 2],
                vec![3, 2, 1],
            ],
        ),
        (vec![0, 1], vec![vec![0, 1], vec![1, 0]]),
        (vec![1], vec![vec![1]]),
    ];

    for (idx, (nums, expected)) in samples.into_iter().enumerate() {
        let result = Solution::permute(nums.clone());

        println!("Sample {}: nums = {:?}", idx + 1, nums);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\\n", expected);
    }
}
