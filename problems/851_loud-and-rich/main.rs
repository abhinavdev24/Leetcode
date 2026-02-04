struct Solution;

impl Solution {
    pub fn loud_and_rich(richer: Vec<Vec<i32>>, quiet: Vec<i32>) -> Vec<i32> {
        let n = quiet.len();
        let mut graph: Vec<Vec<usize>> = vec![vec![]; n];
        for r in richer {
            let a = r[0] as usize;
            let b = r[1] as usize;
            graph[b].push(a); // b -> a, a is richer than b
        }
        let mut ans = vec![-1i32; n];
        for i in 0..n {
            if ans[i] == -1 {
                Self::dfs(i, &graph, &quiet, &mut ans);
            }
        }
        ans
    }

    fn dfs(u: usize, graph: &Vec<Vec<usize>>, quiet: &Vec<i32>, ans: &mut Vec<i32>) -> i32 {
        if ans[u] != -1 {
            return ans[u];
        }
        ans[u] = u as i32;
        for &v in &graph[u] {
            let t = Self::dfs(v, graph, quiet, ans);
            if quiet[t as usize] < quiet[ans[u] as usize] {
                ans[u] = t;
            }
        }
        ans[u]
    }

    pub fn loud_and_rich_topological(richer: Vec<Vec<i32>>, quiet: Vec<i32>) -> Vec<i32> {
        let n = quiet.len();
        let mut graph: Vec<Vec<usize>> = vec![vec![]; n];
        let mut indeg = vec![0; n];
        for r in &richer {
            let a = r[0] as usize;
            let b = r[1] as usize;
            graph[a].push(b);
            indeg[b] += 1;
        }
        let mut res: Vec<i32> = (0..n as i32).collect();
        use std::collections::VecDeque;
        let mut q = VecDeque::new();
        for i in 0..n {
            if indeg[i] == 0 {
                q.push_back(i);
            }
        }
        while let Some(curr) = q.pop_front() {
            for &nei in &graph[curr] {
                if quiet[res[curr] as usize] < quiet[res[nei] as usize] {
                    res[nei] = res[curr];
                }
                indeg[nei] -= 1;
                if indeg[nei] == 0 {
                    q.push_back(nei);
                }
            }
        }
        res
    }
}

fn main() {
    let richer1 = vec![
        vec![1, 0],
        vec![2, 1],
        vec![3, 1],
        vec![3, 7],
        vec![4, 3],
        vec![5, 3],
        vec![6, 3],
    ];
    let quiet1 = vec![3, 2, 5, 4, 6, 1, 7, 0];
    let richer2: Vec<Vec<i32>> = vec![];
    let quiet2 = vec![0];

    let result1 = Solution::loud_and_rich(richer1, quiet1);
    println!("Sample 1 placeholder result: {:?}", result1);
    println!("Sample 1 expected output: [5,5,2,5,4,5,6,7]\n");

    let result2 = Solution::loud_and_rich(richer2, quiet2);
    println!("Sample 2 placeholder result: {:?}", result2);
    println!("Sample 2 expected output: [0]");
}
