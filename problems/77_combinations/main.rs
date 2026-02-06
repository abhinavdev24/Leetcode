struct Solution;

impl Solution {
    pub fn combine(n: i32, k: i32) -> Vec<Vec<i32>> {
        let mut res = Vec::new();
        let mut cur = Vec::new();

        fn dfs(start: i32, left: i32, n: i32, cur: &mut Vec<i32>, res: &mut Vec<Vec<i32>>) {
            if left == 0 {
                res.push(cur.clone());
                return;
            }
            for x in start..=n - left + 1 {
                cur.push(x);
                dfs(x + 1, left - 1, n, cur, res);
                cur.pop();
            }
        }

        dfs(1, k, n, &mut cur, &mut res);
        res
    }
}

fn main() {
    let samples = vec![
        (
            4,
            2,
            vec![
                vec![1, 2],
                vec![1, 3],
                vec![1, 4],
                vec![2, 3],
                vec![2, 4],
                vec![3, 4],
            ],
        ),
        (1, 1, vec![vec![1]]),
    ];

    for (idx, (n, k, expected)) in samples.into_iter().enumerate() {
        let result = Solution::combine(n, k);

        println!("Sample {}: n = {}, k = {}", idx + 1, n, k);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\\n", expected);
    }
}
