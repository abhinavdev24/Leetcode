# Combination Sum IV

Source: https://leetcode.com/problems/combination-sum-iv/

<p>Given an array of <strong>distinct</strong> integers <code>nums</code> and a target integer <code>target</code>, return <em>the number of possible combinations that add up to</em>&nbsp;<code>target</code>.</p>

<p>The test cases are generated so that the answer can fit in a <strong>32-bit</strong> integer.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,2,3], target = 4
<strong>Output:</strong> 7
<strong>Explanation:</strong>
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [9], target = 3
<strong>Output:</strong> 0
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 200</code></li>
	<li><code>1 &lt;= nums[i] &lt;= 1000</code></li>
	<li>All the elements of <code>nums</code> are <strong>unique</strong>.</li>
	<li><code>1 &lt;= target &lt;= 1000</code></li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> What if negative numbers are allowed in the given array? How does it change the problem? What limitation we need to add to the question to allow negative numbers?</p>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type
This is linear target DP: `dp[rem]` where `rem` is remaining sum.

### Step 2: Define minimal future-independent state
Let `f(rem)` be the number of ordered sequences that sum to `rem`.

### Step 3: Recurrence
Try every number as the next picked element:

`f(rem) = sum(f(rem - x)) for all x in nums where rem - x >= 0`

Order matters, so each choice of next element creates distinct sequences.

### Step 4: Base cases + invalid states
- `rem == 0` -> `1` (one completed sequence).
- `rem < 0` is invalid (not recursed into; treated as `0` ways).

### Step 5: Memo + sentinel
Use `memo[0..target]` with `-1` as uncomputed sentinel (`ways >= 0` always).

### Step 6: Compile-fast and debuggable
```cpp
class Solution {
public:
    vector<int> nums;
    vector<int> memo;

    int dfs(int rem) {
        if (rem == 0) return 1;
        int& res = memo[rem];
        if (res != -1) return res;

        long long ways = 0;
        for (int x : nums) {
            if (rem >= x) ways += dfs(rem - x);
        }
        return res = static_cast<int>(ways);
    }

    int combinationSum4(vector<int>& arr, int target) {
        nums = arr;
        memo.assign(target + 1, -1);
        memo[0] = 1;
        return dfs(target);
    }
};
```
Time: `O(target * n)` where `n = nums.size()`  
Space: `O(target)` memo + recursion stack up to `O(target)`.

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction
`f(rem)` depends on smaller remainders `f(rem - x)`, so compute `rem` from `1` to `target`.

### Step 8: Replace recursion with loops
```cpp
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned long long> dp(target + 1, 0);
    dp[0] = 1;

    for (int rem = 1; rem <= target; ++rem) {
        for (int x : nums) {
            if (rem >= x) dp[rem] += dp[rem - x];
        }
    }
    return static_cast<int>(dp[target]);
}
```

### Step 9: Ensure base states pre-filled
Initialize `dp[0] = 1` first; this seeds all future states because any exact transition to `0` contributes one valid sequence.

### Pass 3 - Space Optimization

### Step 10: Check compressibility
Tabulation already uses 1D DP. Further asymptotic compression is not possible because all `dp[0..target]` may be needed.

### Step 11: Apply compression pattern
Use the same 1D table (already space-optimized) and keep remainder ascending:

```cpp
int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int rem = 1; rem <= target; ++rem) {
        for (int x : nums) {
            if (rem >= x) dp[rem] += dp[rem - x];
        }
    }
    return dp[target];
}
```
Time: `O(target * n)`  
Space: `O(target)`

### Step 12: Re-validate after compression
- `nums=[1,2,3], target=4 -> 7`
- `nums=[9], target=3 -> 0`

### Pattern Cheatsheet
Ordered counting with unlimited picks: unbounded knapsack (permutation-count variant).

### State Signature
`f(rem)` or `dp[rem]` = number of ordered sequences summing to remainder `rem`.

### If Stuck
Write `dp[0]=1`, then for each `rem`, add contributions from all valid previous states `dp[rem-x]`.

### Interview Script
I define `dp[rem]` as the number of ordered sequences to make `rem`.  
Transition sums over every choice `x` in `nums`: `dp[rem] += dp[rem-x]` when valid.  
Base case is `dp[0]=1` representing one completed sequence.  
Complexity is `O(target * n)` time and `O(target)` space.
