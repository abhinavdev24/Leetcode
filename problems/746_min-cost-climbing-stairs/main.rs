struct Solution;

impl Solution {
    pub fn min_cost_climbing_stairs(cost: Vec<i32>) -> i32 {
        let n = cost.len();
        if n == 1 {
            return cost[0];
        }
        let mut dp = vec![i32::MAX; n + 1];
        dp[0] = 0;
        dp[1] = 0;
        for i in 2..=n {
            dp[i] = std::cmp::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        dp[n]
    }

    pub fn min_cost_climbing_stairs_2(cost: Vec<i32>) -> i32 {
        let n = cost.len();
        if n == 1 {
            return cost[0];
        }
        let mut prev_2 = 0;
        let mut prev_1 = 0;
        let mut curr = 0;
        for i in 2..=n {
            curr = std::cmp::min(prev_1 + cost[i - 1], prev_2 + cost[i - 2]);
            prev_2 = prev_1;
            prev_1 = curr;
        }
        curr
    }
}

fn main() {
    let samples = vec![
        (vec![10, 15, 20], 15),
        (vec![1, 100, 1, 1, 1, 100, 1, 1, 100, 1], 6),
    ];

    for (cost, expected) in samples {
        let result = Solution::min_cost_climbing_stairs(cost.clone());
        println!(
            "input: cost = {:?}, placeholder result: {}, expected: {}",
            cost, result, expected
        );
    }
}
