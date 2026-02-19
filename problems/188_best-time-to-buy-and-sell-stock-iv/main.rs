struct Solution;

impl Solution {
    // helper: unlimited transactions (sum of positive deltas)
    fn unlimited_profit(prices: &Vec<i32>) -> i32 {
        let mut profit = 0i32;
        for i in 1..prices.len() {
            if prices[i] > prices[i - 1] {
                profit += prices[i] - prices[i - 1];
            }
        }
        profit
    }

    // O(k) space state machine (same as C++ `maxProfit`)
    pub fn max_profit(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut buy = vec![i32::MIN; k_us + 1];
        let mut sell = vec![0i32; k_us + 1];

        for &p in &prices {
            for t in 1..=k_us {
                buy[t] = buy[t].max(sell[t - 1] - p);
                sell[t] = sell[t].max(buy[t] + p);
            }
        }
        sell[k_us]
    }

    // DP with prev/curr arrays (same as C++ `maxProfit_2`)
    pub fn max_profit_2(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut prev = vec![0i32; n];
        let mut curr = vec![0i32; n];

        for _t in 1..=k_us {
            let mut best = -prices[0];
            curr[0] = 0;
            for i in 1..n {
                curr[i] = curr[i - 1].max(prices[i] + best);
                best = best.max(prev[i] - prices[i]);
            }
            std::mem::swap(&mut prev, &mut curr);
        }
        prev[n - 1]
    }

    // compact 2*k state vector (same as C++ `maxProfit_3`)
    pub fn max_profit_3(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut st = vec![i32::MIN; 2 * k_us];
        for p in prices {
            st[0] = st[0].max(-p); // buy1
            if 2 * k_us > 1 {
                st[1] = st[1].max(st[0] + p); // sell1
            }
            for j in 2..2 * k_us {
                if (j & 1) == 0 {
                    // buy
                    st[j] = st[j].max(st[j - 1] - p);
                } else {
                    // sell
                    st[j] = st[j].max(st[j - 1] + p);
                }
            }
        }
        st[2 * k_us - 1].max(0)
    }

    // rolling 2D DP (same as C++ `maxProfit_4`)
    pub fn max_profit_4(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut next = vec![vec![0i32; k_us + 1]; 2];
        let mut curr = vec![vec![0i32; k_us + 1]; 2];

        for i in (0..n).rev() {
            for t in 1..=k_us {
                curr[1][t] = (-prices[i] + next[0][t]).max(next[1][t]);
                curr[0][t] = (prices[i] + next[1][t - 1]).max(next[0][t]);
            }
            std::mem::swap(&mut next, &mut curr);
        }
        next[1][k_us]
    }

    // top-down memo (same as C++ `maxProfit_5` + `rec_5`)
    pub fn max_profit_5(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut dp = vec![vec![vec![i32::MIN; k_us + 1]; 2]; n];
        Self::rec_5(0usize, 1usize, k_us, &prices, &mut dp)
    }

    fn rec_5(i: usize, can_buy: usize, tx_left: usize, prices: &Vec<i32>, dp: &mut Vec<Vec<Vec<i32>>>) -> i32 {
        if i == prices.len() || tx_left == 0 {
            return 0;
        }
        if dp[i][can_buy][tx_left] != i32::MIN {
            return dp[i][can_buy][tx_left];
        }

        let ans = if can_buy == 1 {
            let buy = -prices[i] + Self::rec_5(i + 1, 0, tx_left, prices, dp);
            let skip = Self::rec_5(i + 1, 1, tx_left, prices, dp);
            buy.max(skip)
        } else {
            let sell = prices[i] + Self::rec_5(i + 1, 1, tx_left - 1, prices, dp);
            let hold = Self::rec_5(i + 1, 0, tx_left, prices, dp);
            sell.max(hold)
        };

        dp[i][can_buy][tx_left] = ans;
        ans
    }

    // another top-down variant (same as C++ `maxProfit_6` + `rec_6`)
    pub fn max_profit_6(k: i32, prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 || k == 0 {
            return 0;
        }
        let k_us = k as usize;
        if k_us >= n / 2 {
            return Self::unlimited_profit(&prices);
        }

        let mut dp = vec![vec![vec![i32::MIN; k_us + 1]; 2]; n];
        Self::rec_6(0usize, 1usize, k_us, &prices, &mut dp)
    }

    fn rec_6(i: usize, can_buy: usize, tx_left: usize, prices: &Vec<i32>, dp: &mut Vec<Vec<Vec<i32>>>) -> i32 {
        if i == prices.len() || tx_left == 0 {
            return 0;
        }
        if dp[i][can_buy][tx_left] != i32::MIN {
            return dp[i][can_buy][tx_left];
        }

        let ans = if can_buy == 1 {
            let buy = -prices[i] + Self::rec_6(i + 1, 0, tx_left, prices, dp);
            let skip = Self::rec_6(i + 1, 1, tx_left, prices, dp);
            buy.max(skip)
        } else {
            let sell = prices[i] + Self::rec_6(i + 1, 1, tx_left - 1, prices, dp);
            let hold = Self::rec_6(i + 1, 0, tx_left, prices, dp);
            sell.max(hold)
        };

        dp[i][can_buy][tx_left] = ans;
        ans
    }
}

fn main() {
    {
        let k = 2;
        let prices = vec![2, 4, 1];
        let expected = 2;
        let r1 = Solution::max_profit(k, prices.clone());
        let r2 = Solution::max_profit_2(k, prices.clone());
        let r3 = Solution::max_profit_3(k, prices.clone());
        let r4 = Solution::max_profit_4(k, prices.clone());
        let r5 = Solution::max_profit_5(k, prices.clone());
        let r6 = Solution::max_profit_6(k, prices.clone());
        println!(
            "Sample 1 -> max_profit: {}, max_profit_2: {}, max_profit_3: {}, max_profit_4: {}, max_profit_5: {}, max_profit_6: {} (expected {})",
            r1, r2, r3, r4, r5, r6, expected
        );
    }

    {
        let k = 2;
        let prices = vec![3, 2, 6, 5, 0, 3];
        let expected = 7;
        let r1 = Solution::max_profit(k, prices.clone());
        let r2 = Solution::max_profit_2(k, prices.clone());
        let r3 = Solution::max_profit_3(k, prices.clone());
        let r4 = Solution::max_profit_4(k, prices.clone());
        let r5 = Solution::max_profit_5(k, prices.clone());
        let r6 = Solution::max_profit_6(k, prices.clone());
        println!(
            "Sample 2 -> max_profit: {}, max_profit_2: {}, max_profit_3: {}, max_profit_4: {}, max_profit_5: {}, max_profit_6: {} (expected {})",
            r1, r2, r3, r4, r5, r6, expected
        );
    }
}
