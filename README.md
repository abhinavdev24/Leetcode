## Overview

This repository is a personal LeetCode practice workspace. It focuses on building repeatable scaffolding for every problem so that metadata, descriptions, and language stubs stay consistent over time.

## Workflow

1. Run `python scripts/create_problem.py <leetcode-problem-url>` to fetch the problem via the LeetCode GraphQL API.
2. The helper script writes a new folder under `problems/` containing:
   - `Readme.md` with the official description, examples, and constraints.
   - `metadata.json` with tags, difficulty, spaced-repetition review dates, and other tracking fields.
   - An updated `problems.csv` log entry so attempts stay organized.
3. After scaffolding, add language stubs (currently C++ and Rust) that exercise the official samples. These stubs live beside the metadata and only provide placeholders so solutions can be implemented later.

### Automation Agent

Detailed guidance for the automation process (what to run and what each artifact contains) lives in `agent_new_problem.md`. That document should be used by any tooling or contributor responsible for creating new problem skeletons so the steps stay consistent.

## Repository Layout

- `problems/` – Auto-generated folders `id_slug/` for each problem.
- `scripts/create_problem.py` – Automation script that drives metadata collection and file creation.
- `summaries/` – Space for personal solution write-ups or post-mortems.
- `templates/` – Shared snippets used by the automation tooling.

## Goals

- Maintain a single source of truth for problem data and review schedules.
- Keep language stubs ready so solving a problem requires minimal setup.
- Encourage deliberate practice by logging every attempt and scheduling follow-up reviews.

## Problems

The table below is generated from `problems.csv`; each entry links to the auto-generated problem folder.

| id | slug | difficulty | topics | url |
| --- | --- | --- | --- | --- |
| 1 | [two-sum](problems/1_two-sum/Readme.md) | easy | array, hash-table | https://leetcode.com/problems/two-sum/description/ |
| 11 | [container-with-most-water](problems/11_container-with-most-water/Readme.md) | medium | array, two-pointers, greedy | https://leetcode.com/problems/container-with-most-water/description |
| 12 | [integer-to-roman](problems/12_integer-to-roman/Readme.md) | medium | hash-table, math, string | https://leetcode.com/problems/integer-to-roman/description/ |
| 13 | [roman-to-integer](problems/13_roman-to-integer/Readme.md) | easy | hash-table, math, string | https://leetcode.com/problems/roman-to-integer/ |
| 49 | [group-anagrams](problems/49_group-anagrams/Readme.md) | medium | array, hash-table, string, sorting | https://leetcode.com/problems/group-anagrams/ |
| 56 | [merge-intervals](problems/56_merge-intervals/Readme.md) | medium | array, sorting | https://leetcode.com/problems/merge-intervals |
| 57 | [insert-interval](problems/57_insert-interval/Readme.md) | medium | array | https://leetcode.com/problems/insert-interval |
| 73 | [set-matrix-zeroes](problems/73_set-matrix-zeroes/Readme.md) | medium | array, hash-table, matrix | https://leetcode.com/problems/set-matrix-zeroes/description/ |
| 147 | [insertion-sort-list](problems/147_insertion-sort-list/Readme.md) | medium | linked-list, sorting | https://leetcode.com/problems/insertion-sort-list/ |
| 148 | [sort-list](problems/148_sort-list/Readme.md) | medium | linked-list, two-pointers, divide-and-conquer, sorting, merge-sort | https://leetcode.com/problems/sort-list/ |
| 151 | [reverse-words-in-a-string](problems/151_reverse-words-in-a-string/Readme.md) | medium | two-pointers, string | https://leetcode.com/problems/reverse-words-in-a-string/ |
| 219 | [contains-duplicate-ii](problems/219_contains-duplicate-ii/Readme.md) | easy | array, hash-table, sliding-window | https://leetcode.com/problems/contains-duplicate-ii |
| 228 | [summary-ranges](problems/228_summary-ranges/Readme.md) | easy | array | https://leetcode.com/problems/summary-ranges |
| 310 | [minimum-height-trees](problems/310_minimum-height-trees/Readme.md) | medium | depth-first-search, breadth-first-search, graph, topological-sort | https://leetcode.com/problems/minimum-height-trees/ |
| 802 | [find-eventual-safe-states](problems/802_find-eventual-safe-states/Readme.md) | medium | depth-first-search, breadth-first-search, graph, topological-sort | https://leetcode.com/problems/find-eventual-safe-states/ |
| 851 | [loud-and-rich](problems/851_loud-and-rich/Readme.md) | medium | array, depth-first-search, graph, topological-sort | https://leetcode.com/problems/loud-and-rich/ |
