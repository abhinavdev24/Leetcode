struct Solution;

impl Solution {
    pub fn coin_change(coins: Vec<i32>, amount: i32) -> i32 {
        if amount == 0 {
            return 0;
        }
        let inf = amount + 1;
        let mut dp = vec![inf; (amount + 1) as usize];
        dp[0] = 0;
        for &c in &coins {
            for i in c..=amount {
                dp[i as usize] = dp[i as usize].min(dp[(i - c) as usize] + 1);
            }
        }
        if dp[amount as usize] == inf {
            -1
        } else {
            dp[amount as usize]
        }
    }

    pub fn coin_change_2(coins: Vec<i32>, amount: i32) -> i32 {
        let mut dp = vec![-1; (amount + 1) as usize];
        let res = Self::rec(&coins, amount, &mut dp);
        if res >= i32::MAX / 2 {
            -1
        } else {
            res
        }
    }

    fn rec(coins: &Vec<i32>, amt: i32, dp: &mut Vec<i32>) -> i32 {
        if amt == 0 {
            return 0;
        }
        if amt < 0 {
            return i32::MAX / 2;
        }
        if dp[amt as usize] != -1 {
            return dp[amt as usize];
        }
        let mut count = i32::MAX / 2;
        for &c in coins {
            let res = Self::rec(coins, amt - c, dp);
            count = count.min(res + 1);
        }
        dp[amt as usize] = count;
        count
    }
}

fn main() {
    let samples = vec![(vec![1, 2, 5], 11, 3), (vec![2], 3, -1), (vec![1], 0, 0)];

    for (coins, amount, expected) in samples {
        let result = Solution::coin_change(coins.clone(), amount);
        println!("Input: coins = {:?}, amount = {}", coins, amount);
        println!("Placeholder result: {result}");
        println!("Expected output: {expected}\n");
    }
}
