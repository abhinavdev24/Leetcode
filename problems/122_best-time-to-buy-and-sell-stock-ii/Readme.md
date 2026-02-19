# Best Time to Buy and Sell Stock II

Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

<p>You are given an integer array <code>prices</code> where <code>prices[i]</code> is the price of a given stock on the <code>i<sup>th</sup></code> day.</p>

<p>On each day, you may decide to buy and/or sell the stock. You can only hold <strong>at most one</strong> share of the stock at any time. However, you can sell and buy the stock multiple times on the <strong>same day</strong>, ensuring you never hold more than one share of the stock.</p>

<p>Find and return <em>the <strong>maximum</strong> profit you can achieve</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> prices = [7,1,5,3,6,4]
<strong>Output:</strong> 7
<strong>Explanation:</strong> Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> prices = [1,2,3,4,5]
<strong>Output:</strong> 4
<strong>Explanation:</strong> Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> prices = [7,6,4,3,1]
<strong>Output:</strong> 0
<strong>Explanation:</strong> There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= prices.length &lt;= 3 * 10<sup>4</sup></code></li>
	<li><code>0 &lt;= prices[i] &lt;= 10<sup>4</sup></code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is a state-machine DP (stock DP) with day index and holding mode.

### Step 2: Define minimal future-independent state

Let `f(i, hold)` be the maximum profit from day `i` onward, where:
- `hold = 0`: currently not holding stock
- `hold = 1`: currently holding one stock

### Step 3: Recurrence

At day `i`:
- If `hold = 0`: either skip, or buy.
- If `hold = 1`: either skip, or sell.

\[
f(i,0)=\max(f(i+1,0), -prices[i]+f(i+1,1))
\]
\[
f(i,1)=\max(f(i+1,1), +prices[i]+f(i+1,0))
\]

Answer is `f(0,0)`.

### Step 4: Base cases + invalid states

If `i == n`, no days left, so `f(n,0) = f(n,1) = 0`.

### Step 5: Memo + sentinel

Use `memo[n][2]` initialized to `INT_MIN` as uncomputed sentinel.

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    vector<array<int, 2>> memo;
    int dfs(int i, int hold, const vector<int>& prices) {
        if (i == static_cast<int>(prices.size())) return 0;
        int& res = memo[i][hold];
        if (res != INT_MIN) return res;
        if (hold == 0) {
            res = max(dfs(i + 1, 0, prices), -prices[i] + dfs(i + 1, 1, prices));
        } else {
            res = max(dfs(i + 1, 1, prices), prices[i] + dfs(i + 1, 0, prices));
        }
        return res;
    }
public:
    int maxProfit(vector<int>& prices) {
        memo.assign(prices.size(), {INT_MIN, INT_MIN});
        return dfs(0, 0, prices);
    }
};
```

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(i,*)` depends on `f(i+1,*)`, so iterate `i` from `n-1` down to `0`.

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = static_cast<int>(prices.size());
        vector<array<int, 2>> dp(n + 1, {0, 0});

        for (int i = n - 1; i >= 0; --i) {
            dp[i][0] = max(dp[i + 1][0], -prices[i] + dp[i + 1][1]);
            dp[i][1] = max(dp[i + 1][1],  prices[i] + dp[i + 1][0]);
        }
        return dp[0][0];
    }
};
```

### Step 9: Ensure base states pre-filled

`dp[n][0] = dp[n][1] = 0` is pre-filled and used by day `n-1` transitions.

### Pass 3 - Space Optimization

### Step 10: Check compressibility

Each day uses only the next day, so `O(1)` rolling state works.

### Step 11: Apply compression pattern

Keep two values for next day:
- `nextCash = f(i+1,0)`
- `nextHold = f(i+1,1)`

Compute current day and roll forward.

### Step 12: Re-validate after compression

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int nextCash = 0, nextHold = 0;

        for (int i = static_cast<int>(prices.size()) - 1; i >= 0; --i) {
            int curCash = max(nextCash, -prices[i] + nextHold);
            int curHold = max(nextHold, prices[i] + nextCash);
            nextCash = curCash;
            nextHold = curHold;
        }
        return nextCash;
    }
};
```

### Pattern Cheatsheet

Stock II is classic two-state machine DP (`cash/hold`) over time.

### State Signature

`f(i, hold)` where `hold` is binary mode.

### If Stuck

Write actions by mode: from `cash` you can buy/skip, from `hold` you can sell/skip.

### Interview Script

1. I define `f(i,hold)` as best profit from day `i` onward in mode `hold`.
2. Transition is buy/skip in cash mode and sell/skip in hold mode.
3. Base case is zero profit after last day.
4. Complexity is `O(n * 2)` time and `O(n * 2)` space.
5. Since only next-day states are needed, I compress to `O(1)` space.
