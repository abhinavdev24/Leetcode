struct Solution;

impl Solution {
    pub fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        if matrix.is_empty() {
            return false;
        }
        let m = matrix.len();
        let n = matrix[0].len();
        if n == 0 {
            return false;
        }
        let mut start: usize = 0;
        let mut end: usize = m * n - 1;
        while start <= end {
            let mid = start + (end - start) / 2;
            let r = mid / n;
            let c = mid % n;
            if matrix[r][c] == target {
                return true;
            } else if matrix[r][c] > target {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        false
    }
}

fn main() {
    let matrix1 = vec![vec![1, 3, 5, 7], vec![10, 11, 16, 20], vec![23, 30, 34, 60]];
    let target1 = 3;
    let expected1 = true;
    let result1 = Solution::search_matrix(matrix1, target1);
    println!("Sample 1 result: {}, expected: {}", result1, expected1);

    let matrix2 = vec![vec![1, 3, 5, 7], vec![10, 11, 16, 20], vec![23, 30, 34, 60]];
    let target2 = 13;
    let expected2 = false;
    let result2 = Solution::search_matrix(matrix2, target2);
    println!("Sample 2 result: {}, expected: {}", result2, expected2);
}
