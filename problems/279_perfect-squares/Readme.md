# Perfect Squares

Source: https://leetcode.com/problems/perfect-squares/

<p>Given an integer <code>n</code>, return <em>the least number of perfect square numbers that sum to</em> <code>n</code>.</p>

<p>A <strong>perfect square</strong> is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, <code>1</code>, <code>4</code>, <code>9</code>, and <code>16</code> are perfect squares while <code>3</code> and <code>11</code> are not.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> n = 12
<strong>Output:</strong> 3
<strong>Explanation:</strong> 12 = 4 + 4 + 4.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> n = 13
<strong>Output:</strong> 2
<strong>Explanation:</strong> 13 = 4 + 9.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 10<sup>4</sup></code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is linear index DP: for each target sum `x`, choose one perfect square and reduce to a smaller subproblem.

### Step 2: Define minimal future-independent state

Let `f(x)` be the minimum number of perfect squares needed to sum to `x`.

Answer: `f(n)`.

### Step 3: Recurrence

For every square `s = i*i <= x`, try taking `s` once and solve the rest:
\[
f(x) = 1 + \min_{i^2 \le x} f(x - i^2)
\]

This is an unbounded-choice min DP.

### Step 4: Base cases + invalid states

- `f(0) = 0` (sum zero needs zero numbers).
- For `x < 0`, treat as invalid (`INF`) so it is never chosen.

### Step 5: Memo + sentinel

Use `memo[0..n]` initialized to `-1` (uncomputed). Since answer is non-negative, `-1` is safe sentinel.

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    static constexpr int INF = 1e9;
    int dfs(int x, vector<int>& memo) {
        if (x == 0) return 0;
        if (x < 0) return INF;
        if (memo[x] != -1) return memo[x];

        int best = INF;
        for (int i = 1; i * i <= x; ++i) {
            best = min(best, 1 + dfs(x - i * i, memo));
        }
        return memo[x] = best;
    }

public:
    int numSquares(int n) {
        vector<int> memo(n + 1, -1);
        return dfs(n, memo);
    }
};
```

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(x)` depends on smaller sums `f(x - i*i)`, so iterate `x` from `1` to `n`.

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int numSquares(int n) {
        const int INF = 1e9;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        for (int x = 1; x <= n; ++x) {
            for (int i = 1; i * i <= x; ++i) {
                dp[x] = min(dp[x], 1 + dp[x - i * i]);
            }
        }
        return dp[n];
    }
};
```

### Step 9: Ensure base states pre-filled

Initialize `dp[0] = 0` first; every `dp[x]` is built from that base through smaller states.

### Pass 3 - Space Optimization

### Step 10: Check compressibility

State is already 1D. No extra table exists to compress further; tabulation is already space-optimized.

### Step 11: Apply compression pattern

Use one array `dp[x]` only (same as Pass 2), because transition uses prior indices in the same dimension.

```cpp
class Solution {
public:
    int numSquares(int n) {
        const int INF = 1e9;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        for (int x = 1; x <= n; ++x) {
            for (int sq = 1; sq * sq <= x; ++sq) {
                dp[x] = min(dp[x], dp[x - sq * sq] + 1);
            }
        }
        return dp[n];
    }
};
```

### Step 12: Re-validate after compression

Complexity remains `O(n * sqrt(n))` time and `O(n)` space.

### Pattern Cheatsheet

Minimum-count unbounded composition problems usually map to `dp[target] = min(1 + dp[target - choice])`.

### State Signature

`f(x)` where `x` is remaining sum.

### If Stuck

List choices for one step (which square to pick now), then write “current cost `1` + best of remaining”.

### Interview Script

1. I define `f(x)` as minimum squares needed to form sum `x`.
2. Transition tries every square `i*i <= x`: `f(x) = 1 + min(f(x - i*i))`.
3. Base case is `f(0)=0`; negative states are invalid.
4. Complexity is number of states times choices: `O(n * sqrt(n))` time.
5. Bottom-up uses one 1D array, so space is `O(n)`.
