struct Solution;

impl Solution {
    pub fn merge(mut intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        if intervals.is_empty() {
            return vec![];
        }
        intervals.sort_unstable();
        let mut merged = vec![intervals[0].clone()];
        let mut curr_end = intervals[0][1];
        for i in 1..intervals.len() {
            if curr_end >= intervals[i][0] {
                if intervals[i][1] > curr_end {
                    curr_end = intervals[i][1];
                    merged.last_mut().unwrap()[1] = curr_end;
                }
            } else {
                merged.push(intervals[i].clone());
                curr_end = intervals[i][1];
            }
        }
        merged
    }
}

fn main() {
    let samples = vec![
        (
            vec![vec![1, 3], vec![2, 6], vec![8, 10], vec![15, 18]],
            vec![vec![1, 6], vec![8, 10], vec![15, 18]],
        ),
        (vec![vec![1, 4], vec![4, 5]], vec![vec![1, 5]]),
        (vec![vec![4, 7], vec![1, 4]], vec![vec![1, 7]]),
    ];

    for (idx, (intervals, expected)) in samples.into_iter().enumerate() {
        let result = Solution::merge(intervals.clone());
        println!("Sample {}: intervals = {:?}", idx + 1, intervals);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}", expected);
    }
}
