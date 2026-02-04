struct Solution;

impl Solution {
    pub fn set_zeroes(matrix: &mut Vec<Vec<i32>>) {
        use std::collections::HashSet;
        let m = matrix.len();
        if m == 0 {
            return;
        }
        let n = matrix[0].len();
        let mut rows = HashSet::new();
        let mut cols = HashSet::new();
        for i in 0..m {
            for j in 0..n {
                if matrix[i][j] == 0 {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        }
        for &i in &rows {
            for j in 0..n {
                matrix[i][j] = 0;
            }
        }
        for &j in &cols {
            for i in 0..m {
                matrix[i][j] = 0;
            }
        }
    }
}

fn main() {
    let mut sample1 = vec![vec![1, 1, 1], vec![1, 0, 1], vec![1, 1, 1]];
    let mut sample2 = vec![vec![0, 1, 2, 0], vec![3, 4, 5, 2], vec![1, 3, 1, 5]];

    Solution::set_zeroes(&mut sample1);
    println!("Sample 1 placeholder result: {:?}", sample1);
    println!("Sample 1 expected output: [[1,0,1],[0,0,0],[1,0,1]]\n");

    Solution::set_zeroes(&mut sample2);
    println!("Sample 2 placeholder result: {:?}", sample2);
    println!("Sample 2 expected output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]");
}
