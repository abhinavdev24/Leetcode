struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        // O(1) state machine solution (same as C++ `maxProfit`)
        let mut buy1 = i32::MIN;
        let mut sell1 = 0i32;
        let mut buy2 = i32::MIN;
        let mut sell2 = 0i32;

        for p in prices {
            buy1 = buy1.max(-p);           // best after 1st buy
            sell1 = sell1.max(buy1 + p);   // best after 1st sell
            buy2 = buy2.max(sell1 - p);    // best after 2nd buy
            sell2 = sell2.max(buy2 + p);   // best after 2nd sell
        }
        sell2
    }

    pub fn max_profit_2(prices: Vec<i32>) -> i32 {
        // Tabulated DP with rolling arrays (same as C++ `maxProfit_2`)
        let n = prices.len();
        let mut next = [[0i32; 3]; 2];
        let mut curr = [[0i32; 3]; 2];

        for i in (0..n).rev() {
            for tx_left in 1..=2 {
                // canBuy = 1
                curr[1][tx_left] = (-prices[i] + next[0][tx_left]).max(next[1][tx_left]);
                // canBuy = 0
                curr[0][tx_left] = (prices[i] + next[1][tx_left - 1]).max(next[0][tx_left]);
            }
            next = curr; // copy small fixed-size array
        }

        next[1][2]
    }

    pub fn max_profit_3(prices: Vec<i32>) -> i32 {
        // Full DP table (same as C++ `maxProfit_3`)
        let n = prices.len();
        let mut dp = vec![vec![vec![0i32; 3]; 2]; n + 1];

        for i in (0..n).rev() {
            for tx_left in 1..=2 {
                // canBuy = 1
                dp[i][1][tx_left] = (-prices[i] + dp[i + 1][0][tx_left]).max(dp[i + 1][1][tx_left]);
                // canBuy = 0
                dp[i][0][tx_left] = (prices[i] + dp[i + 1][1][tx_left - 1]).max(dp[i + 1][0][tx_left]);
            }
        }

        dp[0][1][2]
    }

    pub fn max_profit_4(prices: Vec<i32>) -> i32 {
        // Top-down recursion + memo (same as C++ `maxProfit_4` + `rec`)
        if prices.is_empty() {
            return 0;
        }
        let n = prices.len();
        let mut dp = vec![vec![vec![i32::MIN; 3]; 2]; n];
        Self::rec(&prices, 0usize, 1usize, 2usize, &mut dp)
    }

    fn rec(prices: &Vec<i32>, idx: usize, can_buy: usize, tx_left: usize, dp: &mut Vec<Vec<Vec<i32>>>) -> i32 {
        if idx == prices.len() || tx_left == 0 {
            return 0;
        }

        if dp[idx][can_buy][tx_left] != i32::MIN {
            return dp[idx][can_buy][tx_left];
        }

        let ans = if can_buy == 1 {
            let buy = -prices[idx] + Self::rec(prices, idx + 1, 0, tx_left, dp);
            let skip = Self::rec(prices, idx + 1, 1, tx_left, dp);
            buy.max(skip)
        } else {
            let sell = prices[idx] + Self::rec(prices, idx + 1, 1, tx_left - 1, dp);
            let hold = Self::rec(prices, idx + 1, 0, tx_left, dp);
            sell.max(hold)
        };

        dp[idx][can_buy][tx_left] = ans;
        ans
    }
}

fn main() {
    let samples: Vec<(Vec<i32>, i32)> = vec![
        (vec![3, 3, 5, 0, 0, 3, 1, 4], 6),
        (vec![1, 2, 3, 4, 5], 4),
        (vec![7, 6, 4, 3, 1], 0),
    ];

    for (idx, (prices, expected)) in samples.iter().enumerate() {
        let p = prices.clone();
        let r1 = Solution::max_profit(p.clone());
        let r2 = Solution::max_profit_2(p.clone());
        let r3 = Solution::max_profit_3(p.clone());
        let r4 = Solution::max_profit_4(p.clone());

        println!(
            "Example {} -> max_profit: {}, max_profit_2: {}, max_profit_3: {}, max_profit_4: {} (expected {})",
            idx + 1,
            r1,
            r2,
            r3,
            r4,
            expected
        );
    }
}
