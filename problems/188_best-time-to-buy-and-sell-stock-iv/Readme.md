# Best Time to Buy and Sell Stock IV

Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

<p>You are given an integer array <code>prices</code> where <code>prices[i]</code> is the price of a given stock on the <code>i<sup>th</sup></code> day, and an integer <code>k</code>.</p>

<p>Find the maximum profit you can achieve. You may complete at most <code>k</code> transactions: i.e. you may buy at most <code>k</code> times and sell at most <code>k</code> times.</p>

<p><strong>Note:</strong> You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> k = 2, prices = [2,4,1]
<strong>Output:</strong> 2
<strong>Explanation:</strong> Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> k = 2, prices = [3,2,6,5,0,3]
<strong>Output:</strong> 7
<strong>Explanation:</strong> Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= k &lt;= 100</code></li>
	<li><code>1 &lt;= prices.length &lt;= 1000</code></li>
	<li><code>0 &lt;= prices[i] &lt;= 1000</code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is stock/state-machine DP with a transaction budget, so we use small finite states.

### Step 2: Define minimal future-independent state

Let `f(i, cap, hold)` be max profit from day `i` onward where:
- `i` is the day index
- `cap` is remaining sells allowed (`0..k`)
- `hold` is `0` (not holding) or `1` (holding)

Answer is `f(0, k, 0)`.

### Step 3: Recurrence

- If `hold = 0`, either skip or buy:
\[
f(i,cap,0)=\max\big(f(i+1,cap,0),\ -prices[i]+f(i+1,cap,1)\big)
\]
- If `hold = 1`, either skip or sell (selling uses one transaction):
\[
f(i,cap,1)=\max\big(f(i+1,cap,1),\ prices[i]+f(i+1,cap-1,0)\big)
\]

### Step 4: Base cases + invalid states

- If `i == n`, return `0` if `hold == 0`, otherwise impossible (`-INF`).
- If `cap == 0` and `hold == 0`, profit is `0` (cannot open new profitable transaction set).
- If `cap == 0` and `hold == 1`, cannot sell anymore, so impossible (`-INF`).

### Step 5: Memo + sentinel

Use `memo[n][k+1][2]` and `INT_MIN` sentinel for uncomputed states.

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    static constexpr int NEG = -1000000000;
    vector<vector<array<int, 2>>> memo;

    int dfs(int i, int cap, int hold, const vector<int>& prices) {
        int n = (int)prices.size();
        if (i == n) return hold ? NEG : 0;
        if (cap == 0) return hold ? NEG : 0;

        int &res = memo[i][cap][hold];
        if (res != INT_MIN) return res;

        if (hold == 0) {
            res = max(dfs(i + 1, cap, 0, prices), -prices[i] + dfs(i + 1, cap, 1, prices));
        } else {
            res = max(dfs(i + 1, cap, 1, prices), prices[i] + dfs(i + 1, cap - 1, 0, prices));
        }
        return res;
    }

public:
    int maxProfit(int k, vector<int>& prices) {
        int n = (int)prices.size();
        memo.assign(n, vector<array<int, 2>>(k + 1, {INT_MIN, INT_MIN}));
        return max(0, dfs(0, k, 0, prices));
    }
};
```

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(i,*,*)` depends on `f(i+1,*,*)`, so iterate `i` backward from `n-1` to `0`.

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = (int)prices.size();
        const int NEG = -1000000000;
        vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>>(k + 1, {0, NEG}));

        for (int i = n - 1; i >= 0; --i) {
            for (int cap = 1; cap <= k; ++cap) {
                dp[i][cap][0] = max(dp[i + 1][cap][0], -prices[i] + dp[i + 1][cap][1]);
                dp[i][cap][1] = max(dp[i + 1][cap][1], prices[i] + dp[i + 1][cap - 1][0]);
            }
        }
        return dp[0][k][0];
    }
};
```

### Step 9: Ensure base states pre-filled

Initialize day `n` as `dp[n][cap][0] = 0`, `dp[n][cap][1] = -INF`. Also `cap = 0` stays `cash=0`, `hold=-INF` for every day.

### Pass 3 - Space Optimization

### Step 10: Check compressibility

Each day depends only on next day, so keep only two `[(k+1) x 2]` layers.

### Step 11: Apply compression pattern

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        const int NEG = -1000000000;
        vector<array<int, 2>> next(k + 1, {0, NEG}), cur(k + 1, {0, NEG});

        for (int i = (int)prices.size() - 1; i >= 0; --i) {
            cur[0] = {0, NEG};
            for (int cap = 1; cap <= k; ++cap) {
                cur[cap][0] = max(next[cap][0], -prices[i] + next[cap][1]);
                cur[cap][1] = max(next[cap][1], prices[i] + next[cap - 1][0]);
            }
            next.swap(cur);
        }
        return next[k][0];
    }
};
```

### Step 12: Re-validate after compression

Same transitions as tabulation are preserved, so complexity is `O(n * k)` time. Space drops from `O(n * k)` to `O(k)`.

### Pattern Cheatsheet

For Stock IV, use `(day, remainingTransactions, hold)` and decrement transactions on `sell`.

### State Signature

`f(i, cap, hold)` where `cap` is remaining sells and `hold` is binary.

### If Stuck

Model two modes first (`cash`/`hold`), then decide transaction accounting rule; for this problem, count a transaction when selling.

### Interview Script

1. I define state as day, remaining sells, and holding mode.
2. Transition is skip/buy from cash and skip/sell from hold, where sell consumes one transaction.
3. Base cases are no days left, or no transactions left while holding (invalid).
4. Complexity is `O(n*k*2)` states with `O(1)` work each.
5. Then convert to bottom-up and compress to `O(k)` space using rolling layers.
