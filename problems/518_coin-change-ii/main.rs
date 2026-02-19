struct Solution;

impl Solution {
    pub fn change(amount: i32, coins: Vec<i32>) -> i32 {
        let amount = amount as usize;
        let mut dp = vec![0i64; amount + 1];
        dp[0] = 1;
        for &c in &coins {
            let coin = c as usize;
            if coin == 0 || coin > amount { continue; }
            for j in coin..=amount {
                dp[j] += dp[j - coin];
            }
        }
        dp[amount].min(i32::MAX as i64) as i32
    }
}

fn main() {
    let samples: Vec<((i32, Vec<i32>), i32)> = vec![
        ((5, vec![1, 2, 5]), 4),
        ((3, vec![2]), 0),
        ((10, vec![10]), 1),
    ];

    for (idx, ((amount, coins), expected)) in samples.iter().enumerate() {
        let result = Solution::change(*amount, coins.clone());
        println!(
            "Example {} result: {}, expected: {}",
            idx + 1,
            result,
            expected
        );
    }
}
