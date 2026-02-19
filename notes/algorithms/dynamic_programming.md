# Dynamic Programming Notes

## When To Use DP

Use DP when the problem asks for:

- Number of ways (counting)
- Minimum or maximum cost/value (optimization)
- Best result among multiple choices with overlapping subproblems

If the naive recursion repeats the same subproblems, DP usually applies.

## Standard Workflow

1. **State**: what minimum information defines a subproblem?
2. **Transition**: how to build this state from smaller states?
3. **Base cases**: smallest states you know directly.
4. **Answer**: which state(s) represent the final result?
5. **Order**:
   - Top-down: write recursion, then memoize.
   - Bottom-up: fill states in an order that guarantees dependencies are ready.
6. **Complexity + space**:
   - If `dp[i]` depends on a small window (`i-1`, `i-2`, ...), roll variables.

Combination rule (common):

- Count ways: sum over choices.
- Min: `min(...)` over choices.
- Max: `max(...)` over choices.

## Worked Example: Climbing Stairs

Given `n` stairs, each move can be `+1` or `+2`. Return the number of distinct ways to reach stair `n`.

**State**: `f(i)` = number of ways to reach stair `i`.

**Transition**: to reach `i`, come from `i - 1` or `i - 2`:
`f(i) = f(i - 1) + f(i - 2)`

**Base cases**:

- `f(0) = 1` (one way: do nothing)
- `f(1) = 1`

### Approach 1: Plain Recursion (Exponential)

```cpp
int solve(int i) {
    if (i == 0 || i == 1) return 1;
    return solve(i - 1) + solve(i - 2);
}

int climbStairs(int n) {
    return solve(n);
}
```

- Time: `O(2^n)`
- Space: `O(n)` recursion stack

### Approach 2: Memoization (Top-Down DP)

```cpp
#include <vector>
using namespace std;

int solve(int i, vector<int>& dp) {
    if (i == 0 || i == 1) return 1;
    if (dp[i] != -1) return dp[i];
    dp[i] = solve(i - 1, dp) + solve(i - 2, dp);
    return dp[i];
}

int climbStairs(int n) {
    vector<int> dp(n + 1, -1);
    return solve(n, dp);
}
```

- Time: `O(n)`
- Space: `O(n)` (`dp`) + recursion stack

### Approach 3: Tabulation (Bottom-Up DP)

```cpp
#include <vector>
using namespace std;

int climbStairs(int n) {
    if (n <= 1) return 1;

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}
```

- Time: `O(n)`
- Space: `O(n)`

### Approach 4: Space Optimized DP

```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;

    int prev2 = 1; // f(i - 2)
    int prev1 = 1; // f(i - 1)

    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}
```

- Time: `O(n)`
- Space: `O(1)`

## Hard DP Framework (12-Step Playbook)

Use this when the DP is not obvious, the state feels "too big", or transitions are messy.

### 1) Restate As Optimization / Counting / Feasibility

Force one of these forms (one line):

- **Max/Min** value subject to rules
- **#Ways** subject to rules
- **Feasibility** (true/false) subject to rules

If you cannot express the target cleanly, the state is usually wrong.

### 2) Identify The Hardness Source

Hard DP is usually hard because of one of these:

- You need **2+ dimensions** of state (time + resource + last choice)
- Overlap is hidden (looks greedy/graph-like)
- Constraints require compression (rolling, hashing, bitmask)
- Transition requires **splitting** (interval DP) or **merging** (tree DP)

Pick the hardness source; it points to the pattern.

### 3) List Degrees Of Freedom (Decisions)

Ask: what do I choose at each step?

- take/skip
- next index
- partition point `k`
- buy/sell/hold mode
- digit choice
- subset / assignment choice

Degrees of freedom often map directly to DP state.

### 4) Define The Smallest Markov State

Rule: include exactly what the future needs (no more, no less).

Common future dependencies checklist:

- current index / position
- remaining capacity / budget / `k`
- last chosen item / last value / last direction
- holding / not holding
- strings: `(i, j)` pointers or substring bounds
- trees: `node` + (take/skip) or parent info
- intervals: `(l, r)`
- subsets: `mask`

If you need the whole past, the state is missing a variable.

### 5) Pick Style: Top-Down vs Bottom-Up

- Use **top-down (memo)** when state design is unclear, transitions complex, or pruning helps.
- Use **bottom-up** when fill order is natural (prefix, grid, interval length, topo order).

Interview default: start top-down; convert later if time.

### 6) Write Recurrence In English First

Examples:

- "Answer at `i` is best of choosing option A vs option B"
- "Answer at `(l, r)` is min/max over all splits `k`"
- "Answer at `node` merges children answers"

If you cannot say it cleanly, do not code yet.

### 7) Lock Base Cases Aggressively

Base cases are not an afterthought. Common ones:

- index hits end: return `0 / 1 / -INF` depending on objective
- `capacity == 0`
- invalid state: return `INF / -INF`
- `l == r` for intervals
- `null` node for trees
- digit DP: `pos == len`, `tight`, `started`, `prev...` flags

Most hard DP bugs are base cases or sentinel values.

### 8) Decide Enumeration vs Optimization

If transitions loop a lot, consider:

- prefix/suffix minima
- monotonic queue
- binary search
- bitset tricks

In interviews, ship the correct `O(n^2)` if constraints allow; optimize only if forced.

### 9) Validate On Tiny Examples By Hand

Manually test 2-3 tiny inputs (and corner cases):

- `n = 1, 2, 3`
- all same, strictly decreasing, zeros, empty

If the recurrence fails here, fix it before implementing.

### 10) Choose Memory Layout + Sentinels

- Use `long long` if sums can overflow `int`.
- Prefer `INF = 1e18`, `NEG = -1e18` (or `LLONG_MAX / LLONG_MIN` carefully).
- Memo init with `-1` only if `-1` cannot be a valid answer.

### 11) Complexity Check vs Constraints

DP passes if `states * transitions` fits:

- `~1e7` usually fine
- `~1e8` borderline in C++
- `~1e9` too slow (needs a different approach)

### 12) Implement With Debug Hooks

While coding locally:

- assert indices and bounds
- sanity-print small dp tables for tiny cases
- keep the English recurrence above the code

## Pattern Recall System (Classifier)

When you see a hard DP, classify it quickly:

### Q1) Is the state a range `(l, r)`?

Clues: remove/merge/cut, "optimal parenthesization", burst/merge/cut.

- Pattern: **Interval DP**
- State: `dp[l][r]`
- Transition: try split `k`

### Q2) Is it subset/assignment/visit-all with `n <= 20`?

Clues: "use each once", "visit all", "min cost match".

- Pattern: **Bitmask DP**
- State: `dp[mask]` or `dp[mask][last]`

### Q3) Is it time steps with a few modes?

Clues: buy/sell/cooldown/fee/transactions, holding/not-holding.

- Pattern: **State machine DP**
- State: small fixed states per day

If none of those:

- Two pointers over strings/arrays: **String DP** (`dp[i][j]`)
- Tree with independent subtrees: **Tree DP** (postorder merge)
- Index + resource (cap/sum/k): **Knapsack/resource DP**
- Count numbers `<= N`: **Digit DP** (`pos`, `tight`, `started`, `prev...`)

## Pattern Memory: State Signatures

Memorize patterns as state signatures (not as problem titles):

1. Linear: `dp[i]`
2. Grid: `dp[i][j]` from top/left
3. Knapsack: `dp[cap]` (reverse loop = 0/1, forward = unbounded)
4. Subsequence: `dp[i]` depends on `j < i`
5. String: `dp[i][j]`
6. Interval: `dp[l][r]` + split `k`
7. Tree: `dfs(node) -> (take, skip)` (or 3-state)
8. Stocks: `hold/cash/sold/rest` small states
9. Bitmask: `dp[mask]` / `dp[mask][last]`
10. Digit: `dp[pos][tight][...]`

## Hard DP Transformation Tricks

If you're stuck, force one of these:

1. Add a dimension for the missing dependency (last value, previous choice, mode).
2. Flip perspective (build vs remove), often reveals interval DP.
3. Sort to remove a dimension (job scheduling, envelopes).
4. Coordinate compress values when values are large but count is small.

## Interview Explanation Script

1. "I'll define dp state as ... because it captures all info needed for the future."
2. "Transition is ... (options/splits/merge)."
3. "Base cases are ..."
4. "Complexity: states * transitions = ..."
5. "We can optimize by ... if needed."

## DP Templates (Patterns)

These are copy-pasteable skeletons; adapt state meaning, base cases, and the transition.

### 0) Checklist

- **State**: what minimum info defines a subproblem?
- **Transition**: how to go from smaller → bigger?
- **Base cases**
- **Answer**: which state(s) represent final?
- **Order**: recursion + memo, or tabulation order?

### 1) 1D DP (Linear / Prefix)

**Use when:** “best up to i”, “ways up to i”, “min cost up to i”.

```cpp
// dp[i] depends on dp[i-1], dp[i-2], ... (linear)
int solve(vector<int>& a) {
    int n = (int)a.size();
    const int INF = 1e9;
    vector<int> dp(n, INF);

    // base
    dp[0] = /* ... */;

    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1]; // option 1
        // dp[i] = min(dp[i], dp[i-2] + cost) etc...
    }
    return dp[n-1];
}
```

**Space-optimized (rolling variables):**

```cpp
int solve(vector<int>& a) {
    int n = (int)a.size();
    int prev2 = /*dp[i-2]*/, prev1 = /*dp[i-1]*/;

    for (int i = 2; i < n; i++) {
        int cur = min(prev1, prev2 + a[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

### 2) 2D Grid DP

**Use when:** paths in matrix, min path sum, obstacles.

```cpp
long long solve(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    const long long INF = (1LL<<60);
    vector<vector<long long>> dp(m, vector<long long>(n, INF));

    dp[0][0] = grid[0][0];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;
            long long best = INF;
            if (i > 0) best = min(best, dp[i-1][j]);
            if (j > 0) best = min(best, dp[i][j-1]);
            dp[i][j] = best + grid[i][j];
        }
    }
    return dp[m-1][n-1];
}
```

**Space optimize to 1D:**

```cpp
long long solve(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    const long long INF = (1LL<<60);
    vector<long long> dp(n, INF);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) dp[j] = grid[0][0];
            else {
                long long up = (i > 0) ? dp[j] : INF;
                long long left = (j > 0) ? dp[j-1] : INF;
                dp[j] = min(up, left) + grid[i][j];
            }
        }
    }
    return dp[n-1];
}
```

### 3) Pick / Not Pick (Subsequence DP)

**Use when:** LIS-ish, subset style, delete/keep decisions.

```cpp
int solve(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1); // dp[i] = best subseq ending at i

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    return *max_element(dp.begin(), dp.end());
}
```

**Common variant:** dp over index + last choice → use memoization if needed.

### 4) Knapsack Family (0/1, Unbounded, Bounded)

#### 4A) 0/1 Knapsack (each item once)

```cpp
int knap01(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

#### 4B) Unbounded Knapsack (item unlimited)

```cpp
int knapUnbounded(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int cap = w[i]; cap <= W; cap++) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

#### 4C) Subset Sum / Partition (boolean DP)

```cpp
bool subsetSum(vector<int>& a, int S) {
    vector<char> dp(S + 1, false);
    dp[0] = true;
    for (int x : a) {
        for (int s = S; s >= x; s--) dp[s] = dp[s] || dp[s - x];
    }
    return dp[S];
}
```

### 5) Interval DP (DP on ranges [l..r])

**Use when:** “burst balloons”, “merge stones”, “matrix chain multiplication”.

```cpp
long long intervalDP(int n) {
    const long long INF = (1LL<<60);
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] /*+ cost(l,k,r)*/);
            }
        }
    }
    return dp[0][n-1];
}
```

### 6) DP on Trees (Postorder)

**Use when:** “rob houses on tree”, “max independent set-ish”, “subtree combine”.

```cpp
struct TreeNode { int val; TreeNode* left; TreeNode* right; };

pair<long long,long long> dfs(TreeNode* u) {
    // returns {take, skip}
    if (!u) return {0, 0};

    auto [lt, ls] = dfs(u->left);
    auto [rt, rs] = dfs(u->right);

    long long take = u->val + ls + rs;
    long long skip = max(lt, ls) + max(rt, rs);
    return {take, skip};
}

long long solve(TreeNode* root) {
    auto [t, s] = dfs(root);
    return max(t, s);
}
```

### 7) DP on DAG / Topological Order

**Use when:** dependencies, longest path in DAG, counting paths in DAG.

```cpp
long long dagDP(int n, vector<vector<int>>& adj, vector<int>& topo) {
    vector<long long> dp(n, 0);
    // base: dp[source]=1 or dp[i]=value
    for (int u : topo) {
        for (int v : adj[u]) {
            dp[v] = max(dp[v], dp[u] + 1); // or += for counting
        }
    }
    return *max_element(dp.begin(), dp.end());
}
```

### 8) Digit DP (count numbers with constraints)

**Use when:** “count <= N with property”, “no consecutive ones”, etc.

```cpp
// Count numbers in [0..N] satisfying some property.
// Replace the "ok" transition with your constraint.
long long memo[20][2][2]; // pos, tight, started (example)
string s;

long long f(int pos, int tight, int started) {
    if (pos == (int)s.size()) return 1; // adjust if you want to exclude "all leading zeros"
    long long &res = memo[pos][tight][started];
    if (res != -1) return res;
    res = 0;

    int limit = tight ? (s[pos] - '0') : 9;
    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == limit);
        int nstarted = started || (d != 0);

        // constraint example: allow all digits
        bool ok = true;

        if (ok) res += f(pos + 1, ntight, nstarted);
    }
    return res;
}

long long solve(long long N) {
    s = to_string(N);
    memset(memo, -1, sizeof(memo));
    return f(0, 1, 0);
}
```

### 9) Bitmask DP (Subset DP)

**Use when:** small n (≤20), assignment, TSP, “visit all”.

#### 9A) TSP style (min cost visit all)

```cpp
long long tsp(vector<vector<int>>& cost) {
    int n = cost.size();
    const long long INF = (1LL<<60);
    int FULL = (1<<n);
    vector<vector<long long>> dp(FULL, vector<long long>(n, INF));

    dp[1<<0][0] = 0; // start at 0
    for (int mask = 0; mask < FULL; mask++) {
        for (int u = 0; u < n; u++) if (dp[mask][u] < INF) {
            for (int v = 0; v < n; v++) if (!(mask & (1<<v))) {
                int nmask = mask | (1<<v);
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + cost[u][v]);
            }
        }
    }
    long long ans = INF;
    for (int u = 0; u < n; u++) ans = min(ans, dp[FULL-1][u]);
    return ans;
}
```

#### 9B) Assignment DP (min cost match)

```cpp
long long assignMin(vector<vector<int>>& a) {
    int n = a.size();
    const long long INF = (1LL<<60);
    int FULL = 1<<n;
    vector<long long> dp(FULL, INF);
    dp[0] = 0;

    for (int mask = 0; mask < FULL; mask++) {
        int i = __builtin_popcount((unsigned)mask); // assign person i
        for (int j = 0; j < n; j++) if (!(mask & (1<<j))) {
            dp[mask | (1<<j)] = min(dp[mask | (1<<j)], dp[mask] + a[i][j]);
        }
    }
    return dp[FULL-1];
}
```

### 10) String DP

#### 10A) LCS (classic 2D)

```cpp
int lcs(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}
```

#### 10B) Edit Distance

```cpp
int editDist(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}
```

#### 10C) Palindrome DP (Longest Palindromic Subsequence)

```cpp
int lps(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) dp[l][r] = 2 + (l+1 <= r-1 ? dp[l+1][r-1] : 0);
            else dp[l][r] = max(dp[l+1][r], dp[l][r-1]);
        }
    }
    return dp[0][n-1];
}
```

### 11) State Machine DP (Buy/Sell Stocks, cooldown, fees)

**Use when:** few states per day.

```cpp
// Example: max profit with 1 transaction (easy state machine)
int maxProfit1(vector<int>& p) {
    const int NEG = -1e9;
    int hold = NEG; // max profit holding a stock
    int cash = 0;   // max profit not holding

    for (int x : p) {
        int nextHold = max(hold, cash - x);
        int nextCash = max(cash, hold + x);
        hold = nextHold;
        cash = nextCash;
    }
    return cash;
}
```

General pattern: define states like `hold`, `sold`, `rest` and update each day.

### 12) DP With HashMap (sparse states)

**Use when:** state is large but reachable states are few (diffs, sums, etc.)

```cpp
// Example: longest arithmetic subsequence length (dp[i][diff])
int longestArith(vector<int>& a) {
    int n = a.size();
    vector<unordered_map<long long,int>> dp(n);
    int ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            long long d = (long long)a[i] - a[j];
            int best = 1;
            auto it = dp[j].find(d);
            if (it != dp[j].end()) best = it->second;
            dp[i][d] = max(dp[i][d], best + 1);
            ans = max(ans, dp[i][d]);
        }
    }
    return ans;
}
```

## What To Memorize (80/20)

If you memorize only these patterns, you’ll cover most DP interview questions:

1. 1D DP + rolling
2. Grid DP (2D → 1D)
3. Knapsack (0/1 + unbounded + subset-sum)
4. Interval DP
5. Tree DP (take/skip)
6. Bitmask DP (TSP/assignment)
7. String DP (LCS/edit distance)
8. State-machine DP (stocks)

## Practice Problems (LeetCode)

### 1) 1D DP (Linear DP)

- [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
- [House Robber](https://leetcode.com/problems/house-robber/)
- [House Robber II](https://leetcode.com/problems/house-robber-ii/)
- [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)
- [Coin Change](https://leetcode.com/problems/coin-change/)
- [Coin Change II](https://leetcode.com/problems/coin-change-ii/)
- [Perfect Squares](https://leetcode.com/problems/perfect-squares/)
- [Decode Ways](https://leetcode.com/problems/decode-ways/)
- [Word Break](https://leetcode.com/problems/word-break/)
- [Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)

🔥 Core: **House Robber, Coin Change, Decode Ways, Word Break**

### 2) Grid / 2D DP

- [Unique Paths](https://leetcode.com/problems/unique-paths/)
- [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- [Maximal Square](https://leetcode.com/problems/maximal-square/)
- [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)
- [Triangle](https://leetcode.com/problems/triangle/)
- [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/)

🔥 Core: **Unique Paths, Minimum Path Sum, Maximal Square**

### 3) Pick / Not Pick (Subsequence DP)

- [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)
- [Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)
- [Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/)
- [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [Target Sum](https://leetcode.com/problems/target-sum/)
- [Partition Array for Maximum Sum](https://leetcode.com/problems/partition-array-for-maximum-sum/)

🔥 Core: **LIS, Partition Equal Subset Sum, Target Sum**

### 4) Knapsack Family

- [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)
- [Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/)
- [Coin Change](https://leetcode.com/problems/coin-change/)
- [Coin Change II](https://leetcode.com/problems/coin-change-ii/)
- [Perfect Squares](https://leetcode.com/problems/perfect-squares/)

🔥 Core: **Partition Equal Subset Sum, Coin Change**

### 5) Interval DP

- [Burst Balloons](https://leetcode.com/problems/burst-balloons/)
- [Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
- [Merge Stones](https://leetcode.com/problems/merge-stones/)
- [Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)
- [Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)

🔥 Core: **Burst Balloons, Longest Palindromic Subsequence**

### 6) String DP

- [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
- [Edit Distance](https://leetcode.com/problems/edit-distance/)
- [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)
- [Interleaving String](https://leetcode.com/problems/interleaving-string/)
- [Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)
- [Minimum Insertions to Make a String Palindrome](https://leetcode.com/problems/minimum-insertions-to-make-a-string-palindrome/)

🔥 Core: **LCS, Edit Distance, Distinct Subsequences**

### 7) Tree DP

- [House Robber III](https://leetcode.com/problems/house-robber-iii/)
- [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
- [Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/)
- [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

🔥 Core: **House Robber III, Binary Tree Maximum Path Sum**

### 8) State Machine DP (Stocks)

- [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
- [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
- [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
- [Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)
- [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
- [Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

🔥 Core: **Stock I, Stock with Cooldown, Stock IV**

### 9) Bitmask DP

- [Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- [Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)
- [Can I Win](https://leetcode.com/problems/can-i-win/)
- [Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/)
- [Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/)

🔥 Core: **Partition to K Equal Sum Subsets, Shortest Path Visiting All Nodes**

### 10) Very Hard

- [Super Egg Drop](https://leetcode.com/problems/super-egg-drop/)
- [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)
- [Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)
- [Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/)
- [Maximum Number of Events That Can Be Attended II](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/)
- [Best Team With No Conflicts](https://leetcode.com/problems/best-team-with-no-conflicts/)
