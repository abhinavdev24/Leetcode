struct Solution;

impl Solution {
    pub fn find_min_arrow_shots(mut points: Vec<Vec<i32>>) -> i32 {
        if points.is_empty() {
            return 0;
        }
        points.sort_by(|a, b| a[1].cmp(&b[1]));
        let mut arrows = 1;
        let mut prev_end = points[0][1];
        for i in 1..points.len() {
            if points[i][0] > prev_end {
                arrows += 1;
                prev_end = points[i][1];
            }
        }
        arrows
    }
}

fn main() {
    let samples = vec![
        (vec![vec![10, 16], vec![2, 8], vec![1, 6], vec![7, 12]], 2),
        (vec![vec![1, 2], vec![3, 4], vec![5, 6], vec![7, 8]], 4),
        (vec![vec![1, 2], vec![2, 3], vec![3, 4], vec![4, 5]], 2),
    ];

    for (idx, (points, expected)) in samples.into_iter().enumerate() {
        let result = Solution::find_min_arrow_shots(points.clone());

        println!("Sample {}: points = {:?}", idx + 1, points);
        println!("Placeholder result: {}", result);
        println!("Expected output: {}\\n", expected);
    }
}
