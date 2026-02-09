# Dynamic Programming (1D) Notes

## Problem Pattern

Use DP when the problem asks for:

- Number of ways
- Minimum or maximum cost/value
- Best result among multiple choices with overlapping subproblems

A common flow is:

1. Write recursion
2. Add memoization
3. Convert to tabulation
4. Optimize space

## Example: Climbing Stairs

Given `n` stairs, each move can be `+1` or `+2`. Return the number of distinct ways to reach stair `n`.

## State Definition

Let `f(i)` = number of ways to reach stair `i`.

## Recurrence

To reach `i`, you can come from:

- `i - 1` (1-step move)
- `i - 2` (2-step move)

So:
`f(i) = f(i - 1) + f(i - 2)`

## Base Cases

- `f(0) = 1` (one way: do nothing)
- `f(1) = 1`

## Approach 1: Plain Recursion (Exponential)

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

## Approach 2: Memoization (Top-Down DP)

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

## Approach 3: Tabulation (Bottom-Up DP)

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

## Approach 4: Space Optimized DP

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

## Template for 1D DP Thinking

1. Define state: what does `dp[i]` mean?
2. Write recurrence: from which previous states can you reach `i`?
3. Set base cases.
4. Choose combination rule:

- Count ways -> sum
- Min problem -> `min(...)`
- Max problem -> `max(...)`

5. Implement and optimize space if transition depends on few previous states.

## Quick Variants

- Count ways (like Climbing Stairs): usually sum of choices.
- Min cost (e.g., Min Cost Climbing Stairs): `dp[i] = cost[i] + min(...)`.
- Max value (e.g., House Robber): transition with include/exclude choice.
