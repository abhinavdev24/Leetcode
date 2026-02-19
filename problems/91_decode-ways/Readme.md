# Decode Ways

Source: https://leetcode.com/problems/decode-ways/

<p>You have intercepted a secret message encoded as a string of numbers. The message is <strong>decoded</strong> via the following mapping:</p>

<p><code>&quot;1&quot; -&gt; &#39;A&#39;<br />
&quot;2&quot; -&gt; &#39;B&#39;<br />
...<br />
&quot;25&quot; -&gt; &#39;Y&#39;<br />
&quot;26&quot; -&gt; &#39;Z&#39;</code></p>

<p>However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes (<code>&quot;2&quot;</code> and <code>&quot;5&quot;</code> vs <code>&quot;25&quot;</code>).</p>

<p>For example, <code>&quot;11106&quot;</code> can be decoded into:</p>

<ul>
	<li><code>&quot;AAJF&quot;</code> with the grouping <code>(1, 1, 10, 6)</code></li>
	<li><code>&quot;KJF&quot;</code> with the grouping <code>(11, 10, 6)</code></li>
	<li>The grouping <code>(1, 11, 06)</code> is invalid because <code>&quot;06&quot;</code> is not a valid code (only <code>&quot;6&quot;</code> is valid).</li>
</ul>

<p>Note: there may be strings that are impossible to decode.<br />
<br />
Given a string s containing only digits, return the <strong>number of ways</strong> to <strong>decode</strong> it. If the entire string cannot be decoded in any valid way, return <code>0</code>.</p>

<p>The test cases are generated so that the answer fits in a <strong>32-bit</strong> integer.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;12&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">2</span></p>

<p><strong>Explanation:</strong></p>

<p>&quot;12&quot; could be decoded as &quot;AB&quot; (1 2) or &quot;L&quot; (12).</p>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;226&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">3</span></p>

<p><strong>Explanation:</strong></p>

<p>&quot;226&quot; could be decoded as &quot;BZ&quot; (2 26), &quot;VF&quot; (22 6), or &quot;BBF&quot; (2 2 6).</p>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">s = &quot;06&quot;</span></p>

<p><strong>Output:</strong> <span class="example-io">0</span></p>

<p><strong>Explanation:</strong></p>

<p>&quot;06&quot; cannot be mapped to &quot;F&quot; because of the leading zero (&quot;6&quot; is different from &quot;06&quot;). In this case, the string is not a valid encoding, so return 0.</p>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 100</code></li>
	<li><code>s</code> contains only digits and may contain leading zero(s).</li>
</ul>

## Solution

### Pass 1 - Recursive + Memoization

### Step 1: Force DP type
This is linear string DP: `dp[i]` where `i` is the current index to decode.

### Step 2: Define minimal future-independent state
Let `f(i)` be the number of valid decodings for suffix `s[i..n-1]`.

### Step 3: Recurrence
- If `s[i] == '0'`, no decoding starts here: `f(i) = 0`.
- Otherwise:
  `f(i) = f(i+1) + f(i+2)` if two-digit value `10..26` is valid,
  else `f(i) = f(i+1)`.

### Step 4: Base cases + invalid states
- `i == n` -> `1` (successfully decoded full string).
- `s[i] == '0'` -> `0` (invalid standalone zero).

### Step 5: Memo + sentinel
Use `memo[i]` with `-1` as uncomputed sentinel (`answers >= 0`).

### Step 6: Compile-fast and debuggable
```cpp
class Solution {
public:
    string s;
    int n;
    vector<int> memo;

    int dfs(int i) {
        if (i == n) return 1;
        if (s[i] == '0') return 0;
        int& res = memo[i];
        if (res != -1) return res;

        int ways = dfs(i + 1); // take one digit
        if (i + 1 < n) {
            int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (val >= 10 && val <= 26) ways += dfs(i + 2); // take two digits
        }
        return res = ways;
    }

    int numDecodings(string str) {
        s = str;
        n = static_cast<int>(s.size());
        memo.assign(n, -1);
        return dfs(0);
    }
};
```
Time: `O(n)`  
Space: `O(n)` memo + recursion stack.

### Pass 2 - Memoization to Tabulation

### Step 7: Dependency direction
`f(i)` depends on `f(i+1)` and `f(i+2)`, so iterate `i` from right to left.

### Step 8: Replace recursion with loops
```cpp
int numDecodings(string s) {
    int n = static_cast<int>(s.size());
    vector<int> dp(n + 1, 0);
    dp[n] = 1;

    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '0') {
            dp[i] = 0;
            continue;
        }
        dp[i] = dp[i + 1];
        if (i + 1 < n) {
            int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (val >= 10 && val <= 26) dp[i] += dp[i + 2];
        }
    }
    return dp[0];
}
```

### Step 9: Ensure base states pre-filled
Initialize `dp[n] = 1` before the loop so complete parses contribute one valid way.

### Pass 3 - Space Optimization

### Step 10: Check compressibility
Only `i+1` and `i+2` are needed, so compress to two rolling values.

### Step 11: Apply compression pattern
```cpp
int numDecodings(string s) {
    int n = static_cast<int>(s.size());
    int next1 = 1; // dp[i+1], starts as dp[n]
    int next2 = 0; // dp[i+2]

    for (int i = n - 1; i >= 0; --i) {
        int cur = 0;
        if (s[i] != '0') {
            cur = next1;
            if (i + 1 < n) {
                int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (val >= 10 && val <= 26) cur += next2;
            }
        }
        next2 = next1;
        next1 = cur;
    }
    return next1;
}
```
Time: `O(n)`  
Space: `O(1)`

### Step 12: Re-validate after compression
- `"12"` -> `2`
- `"226"` -> `3`
- `"06"` -> `0`

### Pattern Cheatsheet
Linear suffix-count DP with single-digit and conditional two-digit transitions.

### State Signature
`f(i)` = ways to decode suffix starting at index `i`.

### If Stuck
Start with zero-rule (`'0'` invalid alone), then add one-step and valid two-step transitions.

### Interview Script
I define `f(i)` as the number of decodings for `s[i..]`.  
Transition is one-digit decode plus optional two-digit decode in range `10..26`.  
Base case is `f(n)=1`; invalid `'0'` contributes `0`.  
Complexity is `O(n)` time, then optimize from `O(n)` space to `O(1)` with rolling states.
