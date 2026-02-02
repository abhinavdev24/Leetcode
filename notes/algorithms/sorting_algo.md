# Sorting Algorithms (C++)

Common sorting algorithms with intuition, when to use, and compact C++ implementations.

## Quick Comparison

- `O(n^2)` simple sorts: Bubble, Selection, Insertion (good for tiny arrays / learning)
- `O(n log n)` comparison sorts: Merge, Quick (avg), Heap
- Non-comparison sorts (need constraints): Counting, Radix, Bucket
- Practical default in C++: `std::sort` (or `std::stable_sort` when stability matters)

---

## 1) Bubble Sort

Intuition:
- Repeatedly swap adjacent out-of-order elements.
- After each pass, the largest unsorted element "bubbles" to the end.

Use when:
- Mostly for teaching; rarely used in practice.

```cpp
void bubbleSort(vector<int>& a) {
    int n = (int)a.size();

    // After i-th pass, last i elements are already in correct position.
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;

        // Compare adjacent elements and swap if out of order.
        for (int j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        // Optimization: stop early if no swap happened.
        if (!swapped) break;
    }
}
```

- Time: `O(n^2)` worst, `O(n)` best (already sorted with early-exit)
- Space: `O(1)`
- Stable: Yes

---

## 2) Selection Sort

Intuition:
- For each index `i`, find the minimum element in `[i..n-1]` and place it at `i`.
- Grows the sorted prefix one element at a time.

Use when:
- Very small inputs; it minimizes number of swaps.

```cpp
void selectionSort(vector<int>& a) {
    int n = (int)a.size();

    // Expand sorted prefix from left to right.
    for (int i = 0; i < n - 1; ++i) {
        int mn = i;

        // Find index of minimum element in remaining unsorted range.
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[mn]) mn = j;
        }

        // Place minimum at current position.
        swap(a[i], a[mn]);
    }
}
```

- Time: `O(n^2)`
- Space: `O(1)`
- Stable: No (in basic form)

---

## 3) Insertion Sort

Intuition:
- Maintain a sorted left part.
- Insert each new element into its correct position by shifting larger elements right.

Use when:
- Small arrays, nearly sorted data, or as base case inside other sorts.

```cpp
void insertionSort(vector<int>& a) {
    // Start from second element and insert into sorted left side.
    for (int i = 1; i < (int)a.size(); ++i) {
        int key = a[i];
        int j = i - 1;

        // Shift larger elements one step right.
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }

        // Place current element in its correct spot.
        a[j + 1] = key;
    }
}
```

- Time: `O(n^2)` worst, `O(n)` best
- Space: `O(1)`
- Stable: Yes

---

## 4) Merge Sort

Intuition:
- Divide array into halves until size 1.
- Merge sorted halves efficiently.
- "Divide and conquer" with predictable runtime.

Use when:
- Need guaranteed `O(n log n)` and stability.

```cpp
void mergeRange(vector<int>& a, int l, int m, int r) {
    // Copy both sorted halves into temp arrays.
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);

    int i = 0, j = 0, k = l;

    // Merge by always taking the smaller current element.
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }

    // Append leftovers (only one loop will actually run).
    while (i < (int)left.size()) a[k++] = left[i++];
    while (j < (int)right.size()) a[k++] = right[j++];
}

void mergeSort(vector<int>& a, int l, int r) {
    // Base case: single element is already sorted.
    if (l >= r) return;

    int m = l + (r - l) / 2;

    // Recursively sort both halves.
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);

    // Merge two sorted halves.
    mergeRange(a, l, m, r);
}
```

- Time: `O(n log n)`
- Space: `O(n)`
- Stable: Yes

---

## 5) Quick Sort

Intuition:
- Pick a pivot, partition values to left/right groups, then recurse.
- Great cache behavior; usually very fast in practice.

Use when:
- General in-memory sorting where average performance matters.

```cpp
int partitionHoare(vector<int>& a, int l, int r) {
    // Choose middle element as pivot.
    int pivot = a[l + (r - l) / 2];
    int i = l - 1, j = r + 1;

    while (true) {
        // Move i right until element >= pivot.
        do { ++i; } while (a[i] < pivot);

        // Move j left until element <= pivot.
        do { --j; } while (a[j] > pivot);

        // Indices crossed: partition complete.
        if (i >= j) return j;

        // Swap misplaced elements.
        swap(a[i], a[j]);
    }
}

void quickSort(vector<int>& a, int l, int r) {
    if (l >= r) return;

    // Partition and recursively sort both parts.
    int p = partitionHoare(a, l, r);
    quickSort(a, l, p);
    quickSort(a, p + 1, r);
}
```

- Time: `O(n log n)` average, `O(n^2)` worst
- Space: `O(log n)` average recursion stack
- Stable: No

---

## 6) Merge Sort for Singly Linked List

Intuition:
- Use slow/fast pointers to split the list into two halves.
- Recursively sort each half.
- Merge two sorted linked lists (same idea as array merge, but pointer-based).

Use when:
- You need `O(n log n)` sorting for linked lists with `O(1)` extra node space.
- Preferred over quick sort for linked lists because random access is not available.

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwo(ListNode* a, ListNode* b) {
    // Dummy head to simplify pointer handling.
    ListNode dummy(0);
    ListNode* tail = &dummy;

    // Merge by always taking smaller head node.
    while (a && b) {
        if (a->val <= b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes.
    tail->next = (a ? a : b);
    return dummy.next;
}

ListNode* getMidPrev(ListNode* head) {
    // Returns node before mid to split list into two halves.
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = nullptr;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    return prev;
}

ListNode* sortList(ListNode* head) {
    // Base case: empty list or single node is already sorted.
    if (!head || !head->next) return head;

    // Split list into [head..midPrev] and [mid..end].
    ListNode* midPrev = getMidPrev(head);
    ListNode* right = midPrev->next;
    midPrev->next = nullptr;

    // Recursively sort both halves and merge.
    ListNode* leftSorted = sortList(head);
    ListNode* rightSorted = sortList(right);
    return mergeTwo(leftSorted, rightSorted);
}
```

- Time: `O(n log n)`
- Space: `O(log n)` recursion stack (`O(1)` extra node memory)
- Stable: Yes (if merge uses `<=` for left-first tie handling)

---

## 7) Heap Sort

Intuition:
- Build a max-heap, repeatedly extract max to place elements from end to start.
- Avoids worst-case quadratic behavior.

Use when:
- Need guaranteed `O(n log n)` with `O(1)` extra space.

```cpp
void heapSort(vector<int>& a) {
    // 1) Convert array into max-heap.
    make_heap(a.begin(), a.end());

    // 2) Repeatedly move max to end and restore heap for remaining prefix.
    sort_heap(a.begin(), a.end());
}
```

- Time: `O(n log n)`
- Space: `O(1)` extra
- Stable: No

---

## 8) Counting Sort (bounded integer range)

Intuition:
- Count occurrences of each value, then reconstruct output in order.
- No comparisons between elements.

Use when:
- Values are integers in a relatively small range `[0..k]`.

```cpp
vector<int> countingSort(const vector<int>& a, int maxVal) {
    // Frequency array: cnt[v] = how many times v appears.
    vector<int> cnt(maxVal + 1, 0), out;
    out.reserve(a.size());

    for (int x : a) cnt[x]++;

    // Rebuild sorted output by emitting each value count times.
    for (int v = 0; v <= maxVal; ++v) {
        while (cnt[v]--) out.push_back(v);
    }
    return out;
}
```

- Time: `O(n + k)`
- Space: `O(k)`
- Stable: Possible (with prefix-sum + reverse placement)

---

## 9) Radix Sort (LSD for non-negative ints)

Intuition:
- Sort by least-significant digit, then next digit, etc.
- Each pass must be stable (typically counting sort per digit).

Use when:
- Large integer arrays with fixed/base-limited digit width.

```cpp
void countingByExp(vector<int>& a, int exp) {
    vector<int> out(a.size());
    int cnt[10] = {0}; // base-10 digit counts

    // Count digits at current place value (exp = 1, 10, 100...).
    for (int x : a) cnt[(x / exp) % 10]++;

    // Prefix sums -> final positions.
    for (int i = 1; i < 10; ++i) cnt[i] += cnt[i - 1];

    // Traverse from right to keep this pass stable.
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        int d = (a[i] / exp) % 10;
        out[--cnt[d]] = a[i];
    }

    a = move(out);
}

void radixSort(vector<int>& a) {
    if (a.empty()) return;

    // Number of passes decided by max element digits.
    int mx = *max_element(a.begin(), a.end());
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingByExp(a, exp);
    }
}
```

- Time: `O(d * (n + b))` (`d` digits, base `b`)
- Space: `O(n + b)`
- Stable: Yes (if per-pass sort is stable)

---

## 10) Bucket Sort

Intuition:
- Scatter elements into buckets by value range.
- Sort each bucket, then concatenate.

Use when:
- Data is uniformly distributed over known range (e.g., `[0,1)`).

```cpp
vector<double> bucketSort(vector<double> a) {
    int n = (int)a.size();
    vector<vector<double>> buckets(n);

    // Map each value to a bucket index.
    for (double x : a) {
        int idx = min(n - 1, (int)(x * n));
        buckets[idx].push_back(x);
    }

    // Sort each bucket individually.
    for (auto& b : buckets) {
        sort(b.begin(), b.end());
    }

    // Concatenate buckets in order.
    vector<double> out;
    out.reserve(n);
    for (auto& b : buckets) {
        for (double x : b) out.push_back(x);
    }
    return out;
}
```

- Time: `O(n)` average (uniform), up to `O(n log n)` worst
- Space: `O(n)`
- Stable: Depends on bucket-internal sort and insertion strategy

---

## 11) Shell Sort

Intuition:
- Perform insertion sort on elements far apart (`gap`), then shrink gap.
- Pre-reduces disorder so final insertion pass is faster.

Use when:
- In-place sort needed, moderate size arrays, and simple implementation preferred.

```cpp
void shellSort(vector<int>& a) {
    int n = (int)a.size();

    // Start with a large gap, then reduce toward 1.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Gapped insertion sort for this gap.
        for (int i = gap; i < n; ++i) {
            int temp = a[i];
            int j = i;

            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}
```

- Time: Gap-sequence dependent (commonly between ~`O(n^1.3)` and `O(n^2)`)
- Space: `O(1)`
- Stable: No

---

## 12) `std::sort` and `std::stable_sort`

Intuition:
- Let STL pick optimized, battle-tested strategies.

```cpp
// Fast general-purpose sort (not stable).
sort(a.begin(), a.end());

// Stable sort (relative order of equal keys is preserved).
stable_sort(a.begin(), a.end());
```

Use when:
- Almost always in interviews/contests/production unless asked to implement manually.

- `std::sort`: very fast default, not stable
- `std::stable_sort`: stable ordering for equal keys

---

## Rule of Thumb

- Need stability + guaranteed `O(n log n)`: Merge sort / `std::stable_sort`
- Need in-place guaranteed `O(n log n)`: Heap sort
- Need fastest general-purpose average: Quick sort / `std::sort`
- Small or nearly sorted arrays: Insertion sort
- Integers with small value range: Counting sort
- Fixed-width integer keys: Radix sort
