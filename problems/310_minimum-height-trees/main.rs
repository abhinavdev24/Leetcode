struct Solution;

impl Solution {
    pub fn find_min_height_trees(n: i32, edges: Vec<Vec<i32>>) -> Vec<i32> {
        let n = n as usize;
        if n <= 1 {
            return vec![0];
        }
        let mut graph: Vec<Vec<usize>> = vec![vec![]; n];
        let mut indegree: Vec<i32> = vec![0; n];
        for edge in edges {
            let u = edge[0] as usize;
            let v = edge[1] as usize;
            graph[u].push(v);
            graph[v].push(u);
            indegree[u] += 1;
            indegree[v] += 1;
        }
        use std::collections::VecDeque;
        let mut queue = VecDeque::new();
        for i in 0..n {
            if indegree[i] == 1 {
                queue.push_back(i as i32);
            }
        }
        let mut remaining = n;
        while remaining > 2 {
            let sz = queue.len();
            remaining -= sz;
            for _ in 0..sz {
                let leaf = queue.pop_front().unwrap() as usize;
                for &nei in &graph[leaf] {
                    indegree[nei] -= 1;
                    if indegree[nei] == 1 {
                        queue.push_back(nei as i32);
                    }
                }
            }
        }
        let mut res = Vec::new();
        while let Some(x) = queue.pop_front() {
            res.push(x);
        }
        res
    }
}

fn print_vec(values: &[i32]) {
    print!("[");
    for (idx, value) in values.iter().enumerate() {
        if idx > 0 {
            print!(",");
        }
        print!("{value}");
    }
    println!("]");
}

fn main() {
    let edges1 = vec![vec![1, 0], vec![1, 2], vec![1, 3]];
    let result1 = Solution::find_min_height_trees(4, edges1);
    print!("Sample 1 placeholder result: ");
    print_vec(&result1);
    println!("Sample 1 expected output: [1]");

    let edges2 = vec![vec![3, 0], vec![3, 1], vec![3, 2], vec![3, 4], vec![5, 4]];
    let result2 = Solution::find_min_height_trees(6, edges2);
    print!("Sample 2 placeholder result: ");
    print_vec(&result2);
    println!("Sample 2 expected output: [3,4]");
}
