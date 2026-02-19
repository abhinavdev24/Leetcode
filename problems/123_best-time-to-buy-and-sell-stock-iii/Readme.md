# Best Time to Buy and Sell Stock III

Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

<p>You are given an array <code>prices</code> where <code>prices[i]</code> is the price of a given stock on the <code>i<sup>th</sup></code> day.</p>

<p>Find the maximum profit you can achieve. You may complete <strong>at most two transactions</strong>.</p>

<p><strong>Note:</strong> You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> prices = [3,3,5,0,0,3,1,4]
<strong>Output:</strong> 6
<strong>Explanation:</strong> Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> prices = [1,2,3,4,5]
<strong>Output:</strong> 4
<strong>Explanation:</strong> Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> prices = [7,6,4,3,1]
<strong>Output:</strong> 0
<strong>Explanation:</strong> In this case, no transaction is done, i.e. max profit = 0.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= prices.length &lt;= 10<sup>5</sup></code></li>
	<li><code>0 &lt;= prices[i] &lt;= 10<sup>5</sup></code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is a stock/state-machine DP with limited transactions, so we use small finite states.

### Step 2: Define minimal future-independent state

Let `f(i, t, hold)` be maximum profit from day `i` onward, where:
- `i` = current day
- `t` = transactions completed so far (`0..2`)
- `hold` = `0` (not holding) or `1` (holding)

Answer: `f(0, 0, 0)`.

### Step 3: Recurrence

At each day, choose skip or trade:

- If `hold = 0`:
\[
f(i,t,0)=\max\big(f(i+1,t,0),\ -prices[i]+f(i+1,t,1)\big)
\]
- If `hold = 1`:
\[
f(i,t,1)=\max\big(f(i+1,t,1),\ prices[i]+f(i+1,t+1,0)\big)
\]

Selling increases completed transactions by 1.

### Step 4: Base cases + invalid states

- If `i == n`, no days left, return `0`.
- If `t == 2` and `hold == 1`, we cannot sell anymore, treat as impossible (`-INF`).
- If `t > 2`, also impossible (`-INF`).

### Step 5: Memo + sentinel

Use `memo[n][3][2]` with `INT_MIN` sentinel for uncomputed states.

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    static constexpr int NEG = -1e9;
    vector<vector<array<int, 2>>> memo;

    int dfs(int i, int t, int hold, const vector<int>& prices) {
        int n = (int)prices.size();
        if (t > 2) return NEG;
        if (i == n) return hold ? NEG : 0;
        int &res = memo[i][t][hold];
        if (res != INT_MIN) return res;

        if (hold == 0) {
            res = max(dfs(i + 1, t, 0, prices), -prices[i] + dfs(i + 1, t, 1, prices));
        } else {
            res = max(dfs(i + 1, t, 1, prices), prices[i] + dfs(i + 1, t + 1, 0, prices));
        }
        return res;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        memo.assign(n, vector<array<int, 2>>(3, {INT_MIN, INT_MIN}));
        return max(0, dfs(0, 0, 0, prices));
    }
};
```

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(i,*,*)` depends on `f(i+1,*,*)`, so iterate `i` from `n-1` down to `0`.

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        const int NEG = -1e9;
        vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>>(3, {0, NEG}));

        for (int i = n - 1; i >= 0; --i) {
            for (int t = 0; t <= 2; ++t) {
                dp[i][t][0] = max(dp[i + 1][t][0], -prices[i] + dp[i + 1][t][1]);
                if (t < 2) {
                    dp[i][t][1] = max(dp[i + 1][t][1], prices[i] + dp[i + 1][t + 1][0]);
                } else {
                    dp[i][t][1] = dp[i + 1][t][1];
                }
            }
        }
        return dp[0][0][0];
    }
};
```

### Step 9: Ensure base states pre-filled

Initialize day `n` as:
- `dp[n][t][0] = 0` (no stock, no future profit)
- `dp[n][t][1] = -INF` (cannot finish while still holding)

### Pass 3 - Space Optimization

### Step 10: Check compressibility

Only day `i+1` is needed, so compress `dp[i][t][hold]` to rolling arrays over `t` and `hold`.

### Step 11: Apply compression pattern

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int NEG = -1e9;
        array<int, 3> nextCash{0, 0, 0};
        array<int, 3> nextHold{NEG, NEG, NEG};

        for (int i = (int)prices.size() - 1; i >= 0; --i) {
            array<int, 3> curCash{}, curHold{};
            for (int t = 0; t <= 2; ++t) {
                curCash[t] = max(nextCash[t], -prices[i] + nextHold[t]);
                if (t < 2) curHold[t] = max(nextHold[t], prices[i] + nextCash[t + 1]);
                else curHold[t] = nextHold[t];
            }
            nextCash = curCash;
            nextHold = curHold;
        }
        return nextCash[0];
    }
};
```

### Step 12: Re-validate after compression

The compressed transitions are identical to tabulation, so complexity becomes `O(n * 3)` time and `O(3)` space.

### Pattern Cheatsheet

For "at most K transactions" stock problems, use `(day, completedTransactions, hold)` with sell action consuming one transaction.

### State Signature

`f(i, t, hold)` with `t in [0,2]` and binary `hold`.

### If Stuck

Write legal actions per mode first: `cash -> {skip, buy}`, `hold -> {skip, sell}`; then decide where transaction count changes (on sell).

### Interview Script

1. I use `f(i,t,hold)` to capture day, number of completed sells, and holding mode.
2. Transition is skip/buy from cash and skip/sell from hold, with sell increasing `t`.
3. Base case is no future days: `0` if not holding, impossible if holding.
4. Complexity is `O(n * 3 * 2)` states and `O(1)` transitions per state.
5. Tabulation runs backward in day, and we compress to constant space because only next day is needed.
