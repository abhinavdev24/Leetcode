# Agent Dynamic Programming Interview Solver

Your default job is to solve DP problems rigorously and update the matching problem `Readme.md`
with a `## Solution` section.

If the user says something like:

- `use AGENT_DP.md for 746,min-cost-climbing-stairs`
- `use AGENT_DP.md for 746`
- `solve 746 min-cost-climbing-stairs with AGENT_DP`

you must run this workflow end-to-end automatically.

---

## Input Parsing Rules

1. Accept input in these forms:
   - single `id,slug` (example: `746,min-cost-climbing-stairs`)
   - single `id` (example: `746`)
2. For `id`-only input, resolve `slug` from `problems.csv` using the `id` column.
3. Resolve target directory as `problems/{id}_{slug}/`.
4. Target file to edit is `problems/{id}_{slug}/Readme.md`.
5. If `id` is missing in `problems.csv`, report it and stop.
6. If `problems.csv` and an existing folder disagree, treat `problems.csv` as source of truth for slug.
7. This agent handles exactly one problem per invocation.

---

## Repository Output Rules

1. Keep original problem statement content untouched.
2. Add one `## Solution` section near the end only when missing.
3. If `## Solution` already exists, skip that problem and report it as already solved.
4. Do not modify `main.cpp`, `main.rs`, or other files unless explicitly asked.
5. Keep explanations concise but interview-ready (not minimal placeholders).

---

## Required Framework

Use this framework for every DP solve. Keep section headings and ordering.

### A. 3-Pass Workflow

Always run DP in 3 passes:

1. Top-down recursion + memoization (correctness first)
2. Bottom-up tabulation (iterative conversion)
3. Space optimization (only after tabulation is correct)

### Pass 1 - Recursive + Memoization

#### Step 1: Force DP type

Classify by state signature:

- `dp[i]` (linear)
- `dp[i][j]` (grid/string)
- `dp[l][r]` (interval)
- `dp[node][state]` (tree)
- `dp[mask]` / `dp[mask][last]` (bitmask)
- `dp[pos][tight][...]` (digit)
- small finite states (stocks/state machine)

If unclear, list degrees of freedom (next choices).

#### Step 2: Define minimal future-independent state

Write a function form:

- `f(i)`, `f(i, k)`, `f(i, cap)`
- `f(i, j)`
- `f(l, r)`
- `f(node, state)`
- `f(mask)`, `f(mask, last)`
- `f(pos, tight, started, prev, ...)`

If history seems required, add missing dimension (`prev`, `state`, `k`, etc.).

#### Step 3: Recurrence

Write recurrence in English first, then code:

- enumerate choices
- compute next state
- combine via min/max/sum

#### Step 4: Base cases + invalid states

Lock these early:

- end reached -> return `0` / `1` / `-INF` / `INF` by objective
- invalid -> return `INF` / `-INF`
- interval -> handle `l > r` or `l == r`
- bitmask -> handle terminal full mask
- digit -> handle `pos == len`

#### Step 5: Memo + sentinel

- Memo size equals number of states.
- Sentinel rules:
  - use `LLONG_MIN` for uncomputed when answers may be negative
  - use `-1` only if valid answers cannot be `-1`

#### Step 6: Compile-fast and debuggable

- Keep recurrence comment near `dfs`.
- Test tiny cases by hand before full implementation.

Universal top-down skeleton:

```cpp
long long dfs(/* state */) {
    if (/* base */) return /* value */;
    auto &res = memo[/* state */];
    if (res != UNK) return res;
    res = /* init: -INF/INF/0 depending objective */;
    for (/* each choice */) {
        if (/* valid */) {
            res = /* combine(res, transition) */;
        }
    }
    return res;
}
```

### Pass 2 - Memoization to Tabulation

#### Step 7: Dependency direction

From recursion, derive evaluation order:

- `dfs(i)` calls `dfs(i+1)` -> iterate `i` backward
- `dfs(l, r)` calls smaller intervals -> iterate interval length upward
- `dfs(mask)` calls `mask | bit` -> iterate masks upward
- `dfs(pos,...)` calls `pos+1` -> choose matching forward/backward position order

Tabulation order must be a topological order of dependencies.

#### Step 8: Replace recursion with loops

- Create DP table with same dimensions as memo state.
- Fill base cases first.
- Iterate in dependency-safe order.
- Translate recurrence body directly.

Conversion trick: `dfs(a,b,c)` becomes `dp[a][b][c]`.

#### Step 9: Ensure base states pre-filled

Examples:

- interval DP: initialize length-1 states before longer ranges
- string/grid DP: initialize boundary row/column
- knapsack DP: initialize `dp[0]` or equivalent neutral base

### Pass 3 - Space Optimization

#### Step 10: Check compressibility

Compress only when each state depends on previous layer(s), not overwritten same-layer data needed later.

#### Step 11: Apply compression pattern

- 1D predecessor dependency -> rolling variables (`prev2`, `prev1`, `cur`)
- 2D row dependency -> rolling rows (`prev`, `cur`)
- knapsack 2D -> 1D with loop direction:
  - 0/1 knapsack: capacity descending
  - unbounded knapsack: capacity ascending
- interval DP usually stays 2D
- bitmask compress only if secondary dimension is unnecessary

#### Step 12: Re-validate after compression

Run same tiny tests again; compression bugs are common.

### B. Pattern-Specific Conversion Cheatsheet

1. Interval DP: `dfs(l,r)` -> `dp[l][r]`, iterate by interval length.
2. Bitmask DP: `dfs(mask,last)` -> `dp[mask][last]`, iterate masks upward.
3. String DP: `dfs(i,j)` -> `dp[i][j]`, loop direction follows dependency.
4. Index+resource: `dfs(i,cap)` -> `dp[i][cap]`, often compressible to 1D.
5. Digit DP: keep memo recursion in interviews unless iterative form is requested.

### C. Pressure Recall Script (10 seconds)

1. What is the state signature (`i`, `i,j`, `l,r`, `mask`, `node`, `pos+tight`)?
2. In recursion, do states move forward, shrink range, or add bits?
3. Does each state depend only on previous layer(s) for space compression?

### D. Interview Verbatim Structure

1. "I define DP state as ... because it captures all future-needed info."
2. "Transition is ... (choice/split/merge)."
3. "Base case is ..."
4. "Complexity is states times transitions = ..."
5. "Then I convert memo to tabulation, and compress space if dependency allows."

---

## Required `Readme.md` Solution Format

When updating a problem `Readme.md`, write:

- `## Solution`
- `### Pass 1 - Recursive + Memoization`
- exact headings:
  - `### Step 1: Force DP type`
  - `### Step 2: Define minimal future-independent state`
  - `### Step 3: Recurrence`
  - `### Step 4: Base cases + invalid states`
  - `### Step 5: Memo + sentinel`
  - `### Step 6: Compile-fast and debuggable`
- `### Pass 2 - Memoization to Tabulation`
- exact headings:
  - `### Step 7: Dependency direction`
  - `### Step 8: Replace recursion with loops`
  - `### Step 9: Ensure base states pre-filled`
- `### Pass 3 - Space Optimization`
- exact headings:
  - `### Step 10: Check compressibility`
  - `### Step 11: Apply compression pattern`
  - `### Step 12: Re-validate after compression`
- Then a short:
  - `### Pattern Cheatsheet`
  - `### State Signature`
  - `### If Stuck`
  - `### Interview Script`

Keep these concise and problem-specific (do not paste generic boilerplate in full).

---

## Minimum Acceptable Depth (Hard Requirements)

For each generated `## Solution`, all checks below must pass:

1. Include at least one problem-specific recurrence equation in text/math form.
2. Include at least one explicit complexity statement: time and space.
3. Include at least three fenced code blocks total:
   - one code block in Pass 1 (memoized recursion),
   - one code block in Pass 2 (tabulation),
   - one code block in Pass 3 (space-optimized).
4. Use the exact step headings listed above (with labels), not only `### Step N`.
5. Explain base case and table initialization explicitly for that problem.
6. If any item above is missing, the output is invalid and must be regenerated.

Use `problems/122_best-time-to-buy-and-sell-stock-ii/Readme.md` as the quality bar for depth and structure.

---

## Quality Constraints

- Do not skip reasoning steps.
- Do not jump directly to code.
- Be precise and structured.
- Assume Google L4/L5 interview rigor.
- Optimize only if constraints require it.
- Reject low-detail outputs that merely restate formulas without code-backed 3-pass conversion.

---

## Execution Instruction

When invoked for a repository problem:

1. Parse input for exactly one problem (`id,slug` or `id`).
2. For `id` input, read `problems.csv` and map `id -> slug`.
3. Before editing, check whether `problems/{id}_{slug}/Readme.md` already contains `## Solution`.
4. If `## Solution` already exists, skip and return: `{id}_{slug} already solved`.
5. If `## Solution` is missing, edit only `problems/{id}_{slug}/Readme.md` and add `## Solution` using this framework.
6. Run post-generation validation before accepting:
   - exact required headings exist (`Pass 1/2/3`, all 12 labeled step headings, and 4 closing sections),
   - at least 3 fenced code blocks exist,
   - recurrence, base case, and complexity statements exist.
7. If validation fails, regenerate once for the same problem with stricter adherence to this file and re-check.
8. If still failing after one regeneration, report failure with failed checks.
