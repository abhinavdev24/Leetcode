# LeetCode Problem Automation Agent

Given a single LeetCode problem URL, create the local scaffold with one script run, then add C++/Rust non-solution stubs.

## Fast Path (default)

1. Run exactly:
   `python scripts/create_problem.py <leetcode-problem-url>`
2. If the command fails, stop and report the exact error text.
3. On success, immediately create:
   - `problems/{id}_{slug}/main.cpp`
   - `problems/{id}_{slug}/main.rs`

Do not browse other URLs. Use only the URL provided by the user.

---

## What `scripts/create_problem.py` already does

The script fetches problem data from LeetCode GraphQL and writes:

- `problems/{id}_{slug}/Readme.md`
- `problems/{id}_{slug}/metadata.json`
- a new row in `problems.csv`

`metadata.json` includes:

- `id`, `slug`, `difficulty`, `topics`
- `date_solved` (today, local date)
- `url` (exact input URL)
- `attempts` initialized to `1`
- `cpp` and `rust` initialized to `false`
- spaced review dates (`1d`, `7d`, `30d`)

---

## Stub Requirements (must follow)

After scaffolding succeeds, create stubs only (no algorithm implementation):

### `main.cpp`

- Use canonical `class Solution { ... }` method signature for the problem.
- Keep method body as placeholder only (`// TODO` + placeholder return).
- Add a small `main()` that runs **all official sample inputs**.
- For each sample, print:
  - placeholder result
  - expected output

### `main.rs`

- Use canonical Rust signature in `impl Solution`.
- Keep method body as placeholder only (`todo!()` or placeholder return with TODO).
- In `fn main()`, run **all official sample inputs**.
- For each sample, print:
  - placeholder result
  - expected output

Never provide a working solution.

---

## URL Handling

Accept these forms:

- `https://leetcode.com/problems/<slug>/`
- `https://leetcode.com/problems/<slug>/description/`
- with or without trailing slash

Use the exact input URL in `metadata.json` and CSV logging.

---

## Error Handling

- If script fails (invalid URL, network/API issue, GraphQL error), report the script error and stop.
- Do not create partial stubs when scaffolding fails.

---

## Expected Agent Output

Keep output concise:

1. Whether scaffold command succeeded.
2. Which files were created/updated.
3. If failed, exact error and where it failed.
