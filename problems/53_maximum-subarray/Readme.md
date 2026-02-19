# Maximum Subarray

Source: https://leetcode.com/problems/maximum-subarray

<p>Given an integer array <code>nums</code>, find the <span data-keyword="subarray-nonempty">subarray</span> with the largest sum, and return <em>its sum</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [-2,1,-3,4,-1,2,1,-5,4]
<strong>Output:</strong> 6
<strong>Explanation:</strong> The subarray [4,-1,2,1] has the largest sum 6.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [1]
<strong>Output:</strong> 1
<strong>Explanation:</strong> The subarray [1] has the largest sum 1.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [5,4,-1,7,8]
<strong>Output:</strong> 23
<strong>Explanation:</strong> The subarray [5,4,-1,7,8] has the largest sum 23.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> If you have figured out the <code>O(n)</code> solution, try coding another solution using the <strong>divide and conquer</strong> approach, which is more subtle.</p>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type

This is linear DP with state `dp[i]`.

### Step 2: Define minimal future-independent state

Let `f(i)` be the maximum subarray sum for a subarray that must end at index `i`.

### Step 3: Recurrence

At index `i`, either:
- extend the best ending at `i-1`, or
- start fresh at `i`.

\[
f(i) = \max(nums[i], nums[i] + f(i-1))
\]

Final answer is `max(f(i))` for `0 <= i < n`.

### Step 4: Base cases + invalid states

Base case: `f(0) = nums[0]` because the only subarray ending at `0` is `[nums[0]]`.

### Step 5: Memo + sentinel

Use `memo[i]` initialized with `INT_MIN` as uncomputed sentinel.

### Step 6: Compile-fast and debuggable

```cpp
class Solution {
    vector<int> memo;

    int dfs(int i, const vector<int>& nums) {
        if (i == 0) return nums[0];
        int& res = memo[i];
        if (res != INT_MIN) return res;
        res = max(nums[i], nums[i] + dfs(i - 1, nums));
        return res;
    }

public:
    int maxSubArray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        memo.assign(n, INT_MIN);

        int ans = INT_MIN;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dfs(i, nums));
        }
        return ans;
    }
};
```

Time: `O(n)` because each `f(i)` is computed once.  
Space: `O(n)` for memo + recursion stack.

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction

`f(i)` depends on `f(i-1)`, so iterate left to right from `i = 1` to `n-1`.

### Step 8: Replace recursion with loops

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> dp(n);
        dp[0] = nums[0];

        int ans = dp[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(nums[i], nums[i] + dp[i - 1]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

### Step 9: Ensure base states pre-filled

`dp[0] = nums[0]` is pre-filled before the loop and anchors all later states.

### Pass 3 - Space Optimization

### Step 10: Check compressibility

Each state uses only the immediate previous state, so `dp` array can be compressed to one variable.

### Step 11: Apply compression pattern

Keep:
- `prev = f(i-1)`
- `cur = f(i)`
- `ans = global maximum`

### Step 12: Re-validate after compression

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int prev = nums[0];
        int ans = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            int cur = max(nums[i], nums[i] + prev);
            ans = max(ans, cur);
            prev = cur;
        }
        return ans;
    }
};
```

Time: `O(n)` and space: `O(1)`.

### Pattern Cheatsheet

Maximum Subarray is linear "best ending here" DP (Kadane form): local best transition + global best tracking.

### State Signature

`f(i)` = best sum of a non-empty subarray ending at index `i`.

### If Stuck

Force subarrays to end at `i`; then only two choices remain: extend previous or restart at `i`.

### Interview Script

1. I define `f(i)` as the best subarray sum ending at `i`.
2. Transition is `f(i) = max(nums[i], nums[i] + f(i-1))`.
3. Base case is `f(0) = nums[0]`.
4. Complexity is `O(n)` time; tabulation is `O(n)` space, then optimized to `O(1)`.
5. I track a separate global answer because the optimum may end at any index.
