# Fibonacci Number

Source: https://leetcode.com/problems/fibonacci-number/

<p>The <b>Fibonacci numbers</b>, commonly denoted <code>F(n)</code> form a sequence, called the <b>Fibonacci sequence</b>, such that each number is the sum of the two preceding ones, starting from <code>0</code> and <code>1</code>. That is,</p>

<pre>
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n &gt; 1.
</pre>

<p>Given <code>n</code>, calculate <code>F(n)</code>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> n = 2
<strong>Output:</strong> 1
<strong>Explanation:</strong> F(2) = F(1) + F(0) = 1 + 0 = 1.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> n = 3
<strong>Output:</strong> 2
<strong>Explanation:</strong> F(3) = F(2) + F(1) = 1 + 1 = 2.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> n = 4
<strong>Output:</strong> 3
<strong>Explanation:</strong> F(4) = F(3) + F(2) = 2 + 1 = 3.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>0 &lt;= n &lt;= 30</code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is linear DP with a single index state `dp[i]`.

### Step 2: Define minimal future-independent state

Let `f(i)` be the Fibonacci value at index `i`.

### Step 3: Recurrence

For `i > 1`, Fibonacci is defined by:

\[
f(i) = f(i-1) + f(i-2)
\]

We need `f(n)`.

### Step 4: Base cases + invalid states

Base cases:
- `f(0) = 0`
- `f(1) = 1`

No invalid states are needed since `n >= 0` and recursion only calls smaller non-negative indices.

### Step 5: Memo + sentinel

Use `memo[i] = -1` as uncomputed sentinel (valid Fibonacci values are non-negative).

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    vector<int> memo;

    int dfs(int i) {
        if (i <= 1) return i;
        int& res = memo[i];
        if (res != -1) return res;
        res = dfs(i - 1) + dfs(i - 2);
        return res;
    }

public:
    int fib(int n) {
        memo.assign(n + 1, -1);
        return dfs(n);
    }
};
```

Time: `O(n)` because each state is computed once.  
Space: `O(n)` for memo plus recursion stack.

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(i)` depends on `f(i-1)` and `f(i-2)`, so fill from small to large `i` (left to right).

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;

        vector<int> dp(n + 1, 0);
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```

### Step 9: Ensure base states pre-filled

Initialize `dp[0] = 0` (default) and `dp[1] = 1` before starting from `i = 2`.

### Pass 3 - Space Optimization

### Step 10: Check compressibility

Each `f(i)` only needs the previous two values, so full array storage is unnecessary.

### Step 11: Apply compression pattern

Use rolling variables:
- `prev2 = f(i-2)`
- `prev1 = f(i-1)`
- `cur = f(i)`

### Step 12: Re-validate after compression

```cpp
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;

        int prev2 = 0;
        int prev1 = 1;

        for (int i = 2; i <= n; ++i) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};
```

Time: `O(n)` and space: `O(1)`.

### Pattern Cheatsheet

Classic linear predecessor DP: each state depends on the previous two states.

### State Signature

`f(i)` where `i` is the Fibonacci index.

### If Stuck

Write the two fixed bases (`0`, `1`) first, then apply the same two-term addition for all larger indices.

### Interview Script

1. I define `f(i)` as the Fibonacci number at index `i`.
2. Transition is `f(i) = f(i-1) + f(i-2)`.
3. Base cases are `f(0)=0` and `f(1)=1`.
4. Complexity is `O(n)` time and `O(n)` space for tabulation/memo.
5. Since only two previous states are needed, I compress to `O(1)` space.
