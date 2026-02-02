struct Solution;

impl Solution {
    pub fn insert(mut intervals: Vec<Vec<i32>>, new_interval: Vec<i32>) -> Vec<Vec<i32>> {
        // Find the position to insert new_interval
        let pos = intervals.partition_point(|interval| interval[0] < new_interval[0]);
        intervals.insert(pos, new_interval);

        // Now merge overlapping intervals
        let mut merged = Vec::new();
        if intervals.is_empty() {
            return merged;
        }
        merged.push(intervals[0].clone());
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
            vec![vec![1, 3], vec![6, 9]],
            vec![2, 5],
            vec![vec![1, 5], vec![6, 9]],
        ),
        (
            vec![
                vec![1, 2],
                vec![3, 5],
                vec![6, 7],
                vec![8, 10],
                vec![12, 16],
            ],
            vec![4, 8],
            vec![vec![1, 2], vec![3, 10], vec![12, 16]],
        ),
    ];

    for (idx, (intervals, new_interval, expected)) in samples.into_iter().enumerate() {
        let result = Solution::insert(intervals.clone(), new_interval.clone());
        println!(
            "Sample {}: intervals = {:?}, newInterval = {:?}",
            idx + 1,
            intervals,
            new_interval
        );
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}", expected);
    }
}
