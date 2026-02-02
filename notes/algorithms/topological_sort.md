# Topological Sort (Directed Acyclic Graph - DAG)

Topological sorting gives a linear ordering of vertices such that for every directed edge `u -> v`, `u` appears before `v`.

---

## 1) BFS Topological Sort (Kahn's Algorithm)

Idea:

- Compute indegree of each node.
- Push all nodes with indegree `0` into a queue.
- Pop from queue, add to answer, reduce indegree of neighbors.
- If processed nodes count is less than `n`, a cycle exists.

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> topoSortBFS(int n, const vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // If order.size() != n, graph has a cycle (not a DAG).
    return order;
}
```

Time: `O(V + E)`  
Space: `O(V)`

---

## 2) DFS Topological Sort

Idea:

- Run DFS from every unvisited node.
- After exploring all neighbors of a node, push it to result.
- Reverse result at the end.
- Optional: use 3-state visited array to detect cycles.

```cpp
#include <vector>
#include <algorithm>
using namespace std;

bool dfsTopo(int u, const vector<vector<int>>& adj, vector<int>& state, vector<int>& order) {
    state[u] = 1; // visiting

    for (int v : adj[u]) {
        if (state[v] == 1) {
            return false; // cycle found
        }
        if (state[v] == 0) {
            if (!dfsTopo(v, adj, state, order)) {
                return false;
            }
        }
    }

    state[u] = 2; // visited
    order.push_back(u);
    return true;
}

vector<int> topoSortDFS(int n, const vector<vector<int>>& adj) {
    vector<int> state(n, 0); // 0=unvisited, 1=visiting, 2=visited
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            if (!dfsTopo(i, adj, state, order)) {
                return {}; // cycle exists
            }
        }
    }

    reverse(order.begin(), order.end());
    return order;
}
```

Time: `O(V + E)`  
Space: `O(V)` (plus recursion stack)
