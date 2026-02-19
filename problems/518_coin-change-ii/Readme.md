# Coin Change II

Source: https://leetcode.com/problems/coin-change-ii/

<p>You are given an integer array <code>coins</code> representing coins of different denominations and an integer <code>amount</code> representing a total amount of money.</p>

<p>Return <em>the number of combinations that make up that amount</em>. If that amount of money cannot be made up by any combination of the coins, return <code>0</code>.</p>

<p>You may assume that you have an infinite number of each kind of coin.</p>

<p>The answer is <strong>guaranteed</strong> to fit into a signed <strong>32-bit</strong> integer.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> amount = 5, coins = [1,2,5]
<strong>Output:</strong> 4
<strong>Explanation:</strong> there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> amount = 3, coins = [2]
<strong>Output:</strong> 0
<strong>Explanation:</strong> the amount of 3 cannot be made up just with coins of 2.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> amount = 10, coins = [10]
<strong>Output:</strong> 1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= coins.length &lt;= 300</code></li>
	<li><code>1 &lt;= coins[i] &lt;= 5000</code></li>
	<li>All the values of <code>coins</code> are <strong>unique</strong>.</li>
	<li><code>0 &lt;= amount &lt;= 5000</code></li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type
This is index + remaining target, so use `dp[i][rem]`.

### Step 2: Define minimal future-independent state
Let `f(i, rem)` be the number of combinations to build `rem` using coins from index `i...n-1`.

### Step 3: Recurrence
At each state, either skip coin `i` or take it (unbounded use):

`f(i, rem) = f(i + 1, rem) + f(i, rem - coins[i])` (if `rem >= coins[i]`)

### Step 4: Base cases + invalid states
- `rem == 0` -> `1` (one valid way: choose nothing more)
- `i == n` and `rem > 0` -> `0`

### Step 5: Memo + sentinel
Use `memo[n][amount + 1]` initialized with `-1` (`-1` is safe because answers are non-negative).

### Step 6: Compile-fast and debuggable
```cpp
class Solution {
public:
    int n;
    vector<int> c;
    vector<vector<int>> memo;

    int dfs(int i, int rem) {
        if (rem == 0) return 1;
        if (i == n) return 0;
        int& res = memo[i][rem];
        if (res != -1) return res;

        long long ways = dfs(i + 1, rem); // skip coin i
        if (rem >= c[i]) {
            ways += dfs(i, rem - c[i]); // take coin i again (unbounded)
        }
        return res = static_cast<int>(ways);
    }

    int change(int amount, vector<int>& coins) {
        c = coins;
        n = static_cast<int>(coins.size());
        memo.assign(n, vector<int>(amount + 1, -1));
        return dfs(0, amount);
    }
};
```
Time: `O(n * amount)` states, each `O(1)` work.  
Space: `O(n * amount)` memo + recursion stack.

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction
`f(i, rem)` depends on `f(i+1, rem)` and `f(i, rem-coins[i])`, so:
- iterate `i` from `n-1` down to `0`
- iterate `rem` from `0` up to `amount`

### Step 8: Replace recursion with loops
```cpp
int change(int amount, vector<int>& coins) {
    int n = static_cast<int>(coins.size());
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

    for (int i = 0; i <= n; ++i) dp[i][0] = 1;

    for (int i = n - 1; i >= 0; --i) {
        for (int rem = 0; rem <= amount; ++rem) {
            long long ways = dp[i + 1][rem];
            if (rem >= coins[i]) ways += dp[i][rem - coins[i]];
            dp[i][rem] = static_cast<int>(ways);
        }
    }
    return dp[0][amount];
}
```

### Step 9: Ensure base states pre-filled
`dp[i][0] = 1` for all `i` must be initialized first, because making sum `0` always has exactly one combination.

### Pass 3 - Space Optimization

### Step 10: Check compressibility
This is unbounded knapsack counting combinations, so 2D `dp[i][rem]` compresses to 1D `dp[rem]`.

### Step 11: Apply compression pattern
Use coin loop outside and amount loop ascending to allow reusing the same coin multiple times without changing order semantics.

```cpp
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int rem = coin; rem <= amount; ++rem) {
            dp[rem] += dp[rem - coin];
        }
    }
    return dp[amount];
}
```
Time: `O(n * amount)`  
Space: `O(amount)`

### Step 12: Re-validate after compression
For samples:
- `amount=5, [1,2,5] -> 4`
- `amount=3, [2] -> 0`
- `amount=10, [10] -> 1`

### Pattern Cheatsheet
Index + remaining-sum counting with infinite reuse: unbounded knapsack (combinations).

### State Signature
`f(i, rem)` / `dp[i][rem]` where `i` is coin index and `rem` is remaining amount.

### If Stuck
Write the two choices first: skip coin or take coin, then enforce base `rem==0 -> 1`.

### Interview Script
I define state `dp[i][rem]` as number of combinations to form `rem` using coins from `i` onward.  
Transition is skip (`i+1`) plus take (`i, rem-coin`) since each coin is unlimited.  
Base is `rem=0` gives one way, and no coins left with positive remainder gives zero.  
Complexity is `O(n*amount)`, then compress to 1D with ascending amount loop for unbounded knapsack.
