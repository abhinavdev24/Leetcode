struct Solution;

impl Solution {
    pub fn eventual_safe_nodes(graph: Vec<Vec<i32>>) -> Vec<i32> {
        let n = graph.len();
        let mut state = vec![0u8; n]; // 0: unvisited, 1: visiting, 2: safe
        let mut safe = Vec::new();
        for i in 0..n {
            if Self::dfs(i, &graph, &mut state) {
                safe.push(i as i32);
            }
        }
        safe
    }

    fn dfs(u: usize, graph: &Vec<Vec<i32>>, state: &mut Vec<u8>) -> bool {
        if state[u] == 1 {
            return false; // cycle
        }
        if state[u] == 2 {
            return true; // safe
        }
        state[u] = 1; // visiting
        for &v in &graph[u] {
            let v = v as usize;
            if !Self::dfs(v, graph, state) {
                return false;
            }
        }
        state[u] = 2; // safe
        true
    }

    fn eventual_safe_nodes_2(graph: Vec<Vec<i32>>) -> Vec<i32> {
        let n = graph.len();
        let mut vis = vec![false; n];
        let mut path = vec![false; n];
        let mut safenodes = Vec::new();
        for i in 0..n {
            if !vis[i] {
                Self::dfs_detect_cycle(i, &graph, &mut vis, &mut path, &mut safenodes);
            }
        }
        safenodes.sort();
        safenodes
    }

    fn dfs_detect_cycle(
        node: usize,
        graph: &Vec<Vec<i32>>,
        vis: &mut Vec<bool>,
        path: &mut Vec<bool>,
        safenodes: &mut Vec<i32>,
    ) -> bool {
        vis[node] = true;
        path[node] = true;
        for &nei in &graph[node] {
            let nei = nei as usize;
            if !vis[nei] {
                if Self::dfs_detect_cycle(nei, graph, vis, path, safenodes) {
                    return true;
                }
            } else if path[nei] {
                return true;
            }
        }
        safenodes.push(node as i32);
        path[node] = false;
        false
    }

    fn eventual_safe_nodes_3(graph: Vec<Vec<i32>>) -> Vec<i32> {
        let n = graph.len();
        let mut rev: Vec<Vec<usize>> = vec![vec![]; n];
        let mut outdegree: Vec<i32> = vec![0; n];
        for i in 0..n {
            outdegree[i] = graph[i].len() as i32;
            for &nei in &graph[i] {
                let nei = nei as usize;
                rev[nei].push(i);
            }
        }
        use std::collections::VecDeque;
        let mut q = VecDeque::new();
        for i in 0..n {
            if outdegree[i] == 0 {
                q.push_back(i);
            }
        }
        let mut safenodes = Vec::new();
        while let Some(curr) = q.pop_front() {
            safenodes.push(curr as i32);
            for &nei in &rev[curr] {
                outdegree[nei] -= 1;
                if outdegree[nei] == 0 {
                    q.push_back(nei);
                }
            }
        }
        safenodes.sort();
        safenodes
    }
}

fn main() {
    let sample1 = vec![
        vec![1, 2],
        vec![2, 3],
        vec![5],
        vec![0],
        vec![5],
        vec![],
        vec![],
    ];
    let sample2 = vec![vec![1, 2, 3, 4], vec![1, 2], vec![3, 4], vec![0, 4], vec![]];

    let result1 = Solution::eventual_safe_nodes(sample1);
    println!("Sample 1 placeholder result: {:?}", result1);
    println!("Sample 1 expected output: [2,4,5,6]\n");

    let result2 = Solution::eventual_safe_nodes(sample2);
    println!("Sample 2 placeholder result: {:?}", result2);
    println!("Sample 2 expected output: [4]");
}
