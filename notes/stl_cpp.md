# C++ STL (Standard Template Library) Notes

## Introduction to C++ STL

STL (Standard Template Library) is a collection of algorithms, containers, iterators, and functions in C++ that saves time and effort by providing pre-defined components.

### Basic C++ Skeleton

A typical C++ program structure for competitive programming:

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    // Your code here
    return 0;
}
```

- `#include <bits/stdc++.h>`: Includes all standard C++ libraries.
- `using namespace std;`: Avoids the need to prefix standard library elements with `std::`.

### Functions

- **void functions**: Do not return any value.
  ```cpp
  void printName() {
      cout << "Raj" << endl;
  }
  ```
- **Return type functions**: Return a value of a specified data type.
  ```cpp
  int sum(int a, int b) {
      return a + b;
  }
  ```

## C++ STL Components

The STL is primarily composed of four parts:

1.  **Algorithms**: Sorting, searching, etc.
2.  **Containers**: Data structures like vectors, lists, maps, etc.
3.  **Functions**
4.  **Iterators**: Objects that point to an element in a container.

## Pairs (Utility Library)

Pairs are used to store two values together.

```cpp
// Declaration
pair<int, int> p = {1, 3};

// Accessing elements
cout << p.first << " " << p.second; // Output: 1 3

// Nested pairs
pair<int, pair<int, int>> p_nested = {1, {3, 4}};
cout << p_nested.first << " " << p_nested.second.first << " " << p_nested.second.second; // Output: 1 3 4

// Array of pairs
pair<int, int> arr[] = {{1, 2}, {2, 5}, {5, 1}};
cout << arr[1].second; // Output: 5
```

## Containers

### Vectors

Vectors are dynamic arrays that can change their size.

- **Declaration**: `vector<int> v;`
- **Adding elements**:
  - `v.push_back(1);` // Adds 1 to the end
  - `v.emplace_back(2);` // Similar to push_back, but often faster
- **Vector of pairs**: `vector<pair<int, int>> vec;`
- **Declaration with size and initial value**:
  - `vector<int> v(5, 100);` // Creates a vector of size 5 with all elements as 100
  - `vector<int> v(5);` // Creates a vector of size 5 with all elements as 0 (or garbage value)
- **Copying a vector**: `vector<int> v2(v1);`
- **Accessing elements**: `v[0]`, `v.at(0)`
- **Iterators**:
  - `v.begin()`: Points to the first element.
  - `v.end()`: Points to the memory location after the last element.
  - `v.rbegin()`: Points to the last element (for reverse iteration).
  - `v.rend()`: Points to the memory location before the first element (for reverse iteration).
- **Looping**:

  ```cpp
  // Index-based
  for (int i = 0; i < v.size(); i++) {
      cout << v[i] << " ";
  }

  // Using iterators
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
      cout << *(it) << " ";
  }

  // Using auto
  for (auto it = v.begin(); it != v.end(); it++) {
      cout << *(it) << " ";
  }

  // For-each loop
  for (auto it : v) {
      cout << it << " ";
  }
  ```

- **Deletion**:
  - `v.erase(v.begin() + 1);` // Deletes the element at index 1
  - `v.erase(v.begin() + 2, v.begin() + 4);` // Deletes elements from index 2 to 3
- **Insertion**:
  - `v.insert(v.begin(), 300);` // Inserts 300 at the beginning
  - `v.insert(v.begin() + 1, 2, 10);` // Inserts two 10s at index 1
- **Other functions**:
  - `v.size()`: Returns the size of the vector.
  - `v.pop_back()`: Removes the last element.
  - `v1.swap(v2)`: Swaps the contents of two vectors.
  - `v.clear()`: Erases all elements.
  - `v.empty()`: Returns true if the vector is empty.

### List

Similar to a vector, but allows for front operations. Implemented as a doubly linked list.

- `list<int> ls;`
- `ls.push_front(5);` // Adds 5 to the front

### Deque

Double-ended queue, similar to list and vector.

### Stack (LIFO - Last In, First Out)

- `stack<int> st;`
- `st.push(1);`
- `st.pop();` // Deletes the top element
- `st.top();` // Returns the top element
- Time complexity: O(1) for all operations.

### Queue (FIFO - First In, First Out)

- `queue<int> q;`
- `q.push(1);`
- `q.pop();` // Deletes the front element
- `q.front();` // Returns the front element
- `q.back();` // Returns the back element
- Time complexity: O(1) for all operations.

### Priority Queue

A queue where the largest element (by default) is always at the top.

- **Max Heap (default)**: `priority_queue<int> pq;`
- **Min Heap**: `priority_queue<int, vector<int>, greater<int>> pq;`
- `pq.push(5);`
- `pq.pop();` // Removes the top element
- `pq.top();` // Returns the top element
- Time complexity: `push()`/`pop()` - O(log n), `top()` - O(1).

### Set

Stores unique elements in sorted order.

- `set<int> s;`
- `s.insert(1);`
- `s.find(3);` // Returns an iterator to the element, or `s.end()` if not found
- `s.erase(5);` // Erases the element 5
- `s.count(1);` // Returns 1 if the element exists, 0 otherwise
- Time complexity: O(log n) for most operations.

### Multiset

Stores elements in sorted order but allows for duplicate values.

### Unordered Set

Stores unique elements in a random order.

- Time complexity: O(1) on average, O(n) in the worst case.
- `lower_bound()` and `upper_bound()` do not work.

## Map

Stores key-value pairs, where keys are unique and sorted.

- `map<int, int> mpp;`
- `mpp[1] = 2;`
- `mpp.emplace(3, 1);`
- `mpp.insert({2, 4});`
- **Iteration**:
  ```cpp
  for (auto it : mpp) {
      cout << it.first << " " << it.second << endl;
  }
  ```
- `mpp.find(3);` // Returns an iterator to the key-value pair
- Time complexity: O(log n).

### Multimap

Allows for duplicate keys, stored in sorted order.

### Unordered Map

Stores key-value pairs with unique keys in a random order.

- Time complexity: O(1) on average, O(n) in the worst case.

## Algorithms

### `sort()`

- `sort(a, a + n);` // Sorts an array
- `sort(v.begin(), v.end());` // Sorts a vector
- `sort(v.begin(), v.end(), greater<int>());` // Sorts in descending order
- **Custom Comparator**:
  ```cpp
  bool comp(pair<int, int> p1, pair<int, int> p2) {
      if (p1.second < p2.second) return true;
      if (p1.second > p2.second) return false;
      // if they are same
      if (p1.first > p2.first) return true;
      return false;
  }
  sort(a, a + n, comp);
  ```

### `__builtin_popcount()`

Counts the number of set bits (1s) in the binary representation of an integer.

- `int num = 7; // binary 111`
- `int cnt = __builtin_popcount(num); // cnt is 3`
- For `long long`, use `__builtin_popcountll()`.

### `next_permutation()`

Generates the next lexicographically greater permutation of a sequence.

```cpp
string s = "123";
do {
    cout << s << endl;
} while (next_permutation(s.begin(), s.end()));
```

### `max_element()` / `min_element()`

Finds the maximum or minimum element in a range.

- `int maxi = *max_element(a, a + n);`
- `int mini = *min_element(a, a + n);`
