struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut profit = 0;
        for i in 0..prices.len() - 1 {
            if prices[i] < prices[i + 1] {
                profit += prices[i + 1] - prices[i];
            }
        }
        profit
    }

    pub fn max_profit_2(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        let mut dp = vec![vec![0; 2]; n + 1];
        for i in (0..n).rev() {
            dp[i][1] = (-prices[i] + dp[i + 1][0]).max(dp[i + 1][1]);
            dp[i][0] = (prices[i] + dp[i + 1][1]).max(dp[i + 1][0]);
        }
        dp[0][1]
    }

    pub fn max_profit_3(prices: Vec<i32>) -> i32 {
        let mut dp = vec![vec![i32::MIN; 2]; prices.len()];
        Self::rec(&prices, 0, true, &mut dp)
    }

    fn rec(prices: &Vec<i32>, index: usize, can_buy: bool, dp: &mut Vec<Vec<i32>>) -> i32 {
        if index == prices.len() {
            return 0;
        }
        let can_buy_idx = if can_buy { 1 } else { 0 };
        if dp[index][can_buy_idx] != i32::MIN {
            return dp[index][can_buy_idx];
        }
        let res = if can_buy {
            let buy = -prices[index] + Self::rec(prices, index + 1, false, dp);
            let not_buy = Self::rec(prices, index + 1, true, dp);
            buy.max(not_buy)
        } else {
            let sell = prices[index] + Self::rec(prices, index + 1, true, dp);
            let not_sell = Self::rec(prices, index + 1, false, dp);
            sell.max(not_sell)
        };
        dp[index][can_buy_idx] = res;
        res
    }
}

fn main() {
    let test_cases = vec![
        vec![7, 1, 5, 3, 6, 4],
        vec![1, 2, 3, 4, 5],
        vec![7, 6, 4, 3, 1],
    ];
    let expected = [7, 4, 0];

    for (idx, prices) in test_cases.into_iter().enumerate() {
        let result = Solution::max_profit(prices);
        println!(
            "Sample {}: result={}, expected={}",
            idx + 1,
            result,
            expected[idx]
        );
    }
}
