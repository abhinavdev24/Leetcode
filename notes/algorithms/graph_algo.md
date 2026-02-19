# Graph Algorithms Cheat Sheet

## 0) Repeatable Framework for Any Graph Problem

### A) 20-second classifier (before coding)

1. **Is it a grid or explicit edges?**
   - grid ⇒ implicit graph neighbors
   - edges ⇒ adjacency list
2. **Directed or undirected?**
3. **Weights?**
   - none ⇒ BFS/DFS
   - 0/1 ⇒ 0-1 BFS
   - positive ⇒ Dijkstra
   - negative ⇒ Bellman–Ford (rare on LC)
4. **What’s being asked?**
   - existence? count? min/max? ordering? connectivity after ops?

This narrows most problems to 1–2 patterns.

### B) Translate problem → canonical graph model (write these 5 lines)

- **Nodes =** what is a state? (cell / city / word / `(node, mask)` / `(node, k)`)
- **Edges =** how do you move? what costs?
- **Start(s) =** single vs multi-source
- **Goal =** reach? shortest? count? best value? detect cycle?
- **Constraints =** `V` up to? `E` up to? need `O(E log V)` vs `O(VE)`?

If you can’t state “Nodes/Edges” clearly, you’re not ready to code.

### C) Pick the solver family (deterministic mapping)

**Shortest path / minimum steps / minimum cost**
- unweighted ⇒ BFS
- 0/1 weights ⇒ 0-1 BFS
- positive weights ⇒ Dijkstra
- “visiting all nodes” / stateful shortest path ⇒ BFS/Dijkstra on a **state graph**
- all-pairs shortest (small `n`) ⇒ Floyd–Warshall (rare on LC)

**Dependency / ordering / prerequisites**
- need valid order ⇒ topological sort (Kahn/DFS)
- detect cycle ⇒ directed 3-color DFS or topo-size check
- “safe nodes” (don’t reach cycles) ⇒ reverse graph + outdegree trimming OR SCC compression

**Connectivity / grouping / components**
- static components ⇒ DFS/BFS
- dynamic unions / edges added over time ⇒ DSU
- minimum cost to connect ⇒ MST (Kruskal/Prim)

**Critical edges / single point of failure**
- bridges / articulation points ⇒ Tarjan low-link

**Mutual reachability / cycles as groups**
- SCC (Tarjan/Kosaraju) ⇒ compress to DAG ⇒ solve on DAG

**Two groups / conflicts**
- bipartite / 2-color ⇒ BFS/DFS coloring

### D) Hard graph problems usually hide a “state graph”

If it feels hard, the **node is not just a vertex**.

Common state upgrades:
- `(node, mask)` → visiting all nodes, TSP-like (e.g., LC 847)
- `(node, remainingK)` → k stops, k walls, k discounts
- `(node, time)` / `(node, parity)` → periodic constraints
- `(node, lastColor)` → alternating constraints
- `(i, j, dir)` in grids → direction-based transitions

Rule: if the answer depends on “what you already used / have left”, add it to the state.

### E) Write invariants before code (prevents bugs)

- **Visited definition:** visited *what*? (`vis[u]` vs `vis[u][mask]`)
- **Relaxation rule:** when do we update `dist`? (`if dist[v] > dist[u] + w`)
- **Termination / early exit:** BFS first-reach, Dijkstra first-pop target (when non-negative)

If visited is wrong, everything is wrong.

### F) Most “hard” questions are 2 patterns glued together

- topo + DP (e.g., longest path in DAG)
- Dijkstra + state (shortest path with extra dimension)
- SCC + topo (condense SCCs → DAG → solve)
- DSU + sorting (Kruskal MST, offline queries)
- BFS + reverse graph (eventual safe nodes)

When stuck: “what is the second pattern?”

### G) Debug checklist (graph-specific)

1. Directed vs undirected edges added correctly?
2. Indexing (0-based vs 1-based)?
3. Visited/dist updated at the right time?
   - BFS: mark visited when pushed
   - Dijkstra: allow multiple relaxations; finalize on min-pop (stale-check)
4. Missing state dimension? (most common in hard)
5. Complexity: did `V` explode after state expansion?

### H) Recall system under pressure

Trigger phrase → pattern:
- “minimum steps” → BFS
- “minimum cost, positive” → Dijkstra
- “weights are 0/1” → 0-1 BFS
- “order / prerequisites” → topo
- “can finish? cycle?” → directed cycle / topo-size check
- “two groups / dislike” → bipartite
- “merge groups / swap within groups” → DSU
- “critical connection / removing one edge disconnects” → bridges
- “mutual reachability / cycles collapsed” → SCC
- “doesn’t lead to cycle / eventually ends” → reverse trim / SCC

Practice method (fast): for every solved problem, write one line:
`Trigger → Pattern → State definition`

### I) Mini “hard graph” interview workflow

1. Classifier (directed? weighted?)
2. Define state graph (nodes/edges/start/goal)
3. Choose template (BFS/Dijkstra/topo/DSU/Tarjan)
4. Confirm visited/dist definition
5. Implement template
6. Test tiny custom cases (cycle, disconnected, multi-source)

## 1) BFS (Shortest path in unweighted graph)

**Use for:** shortest steps, levels, min edges, bipartite check base, flood-fill on graph.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs_shortest_unweighted(int n, vector<vector<int>>& g, int src) {
    const int INF = 1e9;                 // Sentinel for "unreached" nodes.
    vector<int> dist(n, INF);            // dist[i] = shortest edge-count from src to i.
    queue<int> q;                        // FIFO queue gives level-order traversal.

    dist[src] = 0;                       // Source is 0 edges away from itself.
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();      // Process next node in BFS order.
        for (int v : g[u]) {             // Try all outgoing edges u -> v.
            if (dist[v] == INF) {        // First visit is guaranteed shortest in unweighted graph.
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;                         // INF remains for unreachable nodes.
}
```

---

## 2) DFS (Connected components / reachability)

**Use for:** components, checking connectivity, counting, exploring.

```cpp
#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<vector<int>>& g, vector<int>& vis) {
    vis[u] = 1;                          // Mark current node as visited.
    for (int v : g[u])                   // Explore every neighbor recursively.
        if (!vis[v])
            dfs(v, g, vis);
}

int count_components(int n, vector<vector<int>>& g) {
    vector<int> vis(n, 0);               // 0 = not visited, 1 = visited.
    int comps = 0;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {                   // New DFS means a new connected component.
            comps++;
            dfs(i, g, vis);
        }
    }
    return comps;
}
```

---

## 3) Cycle detection (Undirected)

**Use for:** “is there a cycle?” in undirected graph.

```cpp
#include <bits/stdc++.h>
using namespace std;

bool dfs_cycle_undirected(int u, int parent, vector<vector<int>>& g, vector<int>& vis) {
    vis[u] = 1;                          // Enter node u.

    for (int v : g[u]) {
        if (!vis[v]) {
            if (dfs_cycle_undirected(v, u, g, vis))
                return true;             // Cycle already found deeper in DFS tree.
        } else if (v != parent) {
            return true;                 // Back-edge to a non-parent visited node => cycle.
        }
    }
    return false;
}

bool has_cycle_undirected(int n, vector<vector<int>>& g) {
    vector<int> vis(n, 0);

    for (int i = 0; i < n; i++) {
        // Need outer loop because graph can be disconnected.
        if (!vis[i] && dfs_cycle_undirected(i, -1, g, vis))
            return true;
    }
    return false;
}
```

---

## 4) Cycle detection (Directed) + Topological validity

**Use for:** “can finish courses?”, deadlocks, DAG check.

```cpp
#include <bits/stdc++.h>
using namespace std;

bool dfs_cycle_directed(int u, vector<vector<int>>& g, vector<int>& state) {
    // state: 0 = unvisited, 1 = currently in recursion stack, 2 = fully processed.
    state[u] = 1;

    for (int v : g[u]) {
        if (state[v] == 0) {
            if (dfs_cycle_directed(v, g, state))
                return true;
        } else if (state[v] == 1) {
            return true;                 // Edge to an active node => directed cycle.
        }
    }

    state[u] = 2;                        // Done exploring all descendants.
    return false;
}

bool has_cycle_directed(int n, vector<vector<int>>& g) {
    vector<int> state(n, 0);

    for (int i = 0; i < n; i++) {
        if (state[i] == 0 && dfs_cycle_directed(i, g, state))
            return true;
    }
    return false;
}
```

---

## 5) Topological sort (Kahn BFS)

**Use for:** ordering with prerequisites, detect cycle if not all processed.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> topo_kahn(int n, vector<vector<int>>& g) {
    vector<int> indeg(n, 0);             // indeg[v] = number of incoming edges to v.

    for (int u = 0; u < n; u++)
        for (int v : g[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);                   // Start with all nodes that have no prerequisites.

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);

        for (int v : g[u]) {
            if (--indeg[v] == 0)         // Remove edge u -> v; if no incoming left, enqueue.
                q.push(v);
        }
    }

    if ((int)order.size() != n)
        return {};                       // Not all nodes processed => cycle exists.
    return order;
}
```

---

## 6) Bipartite check (2-coloring)

**Use for:** odd cycle detection, partitioning, “possible to divide into 2 groups”.

```cpp
#include <bits/stdc++.h>
using namespace std;

bool is_bipartite(int n, vector<vector<int>>& g) {
    vector<int> color(n, -1);            // -1 = uncolored, 0/1 are the two partitions.
    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (color[i] != -1)
            continue;                    // Already covered by previous BFS component.

        color[i] = 0;
        q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1; // Neighbor must be opposite color.
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;        // Adjacent same color => not bipartite.
                }
            }
        }
    }
    return true;
}
```

---

## 7) Dijkstra (Shortest path, non-negative weights)

**Use for:** weighted shortest path, grid weighted, routing.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<long long> dijkstra(int n, vector<vector<pair<int,int>>>& g, int src) {
    const long long INF = (1LL << 62);
    vector<long long> dist(n, INF);      // Best known distance from src.

    // Min-heap of (distance, node).
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d != dist[u])
            continue;                    // Skip stale heap entries.

        for (auto [v, w] : g[u]) {      // Edge u -> v with weight w.
            if (dist[v] > d + w) {
                dist[v] = d + w;        // Relax edge.
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

---

## 8) 0-1 BFS (weights are only 0 or 1)

**Use for:** super common optimization in interviews.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> zero_one_bfs(int n, vector<vector<pair<int,int>>>& g, int src) {
    const int INF = 1e9;
    deque<int> dq;                       // Deque lets us push 0-weight edges to front.
    vector<int> dist(n, INF);

    dist[src] = 0;
    dq.push_front(src);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();

        for (auto [v, w] : g[u]) {      // w is guaranteed to be 0 or 1.
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (w == 0)
                    dq.push_front(v);    // 0-cost transition: highest priority.
                else
                    dq.push_back(v);     // 1-cost transition: process later.
            }
        }
    }
    return dist;
}
```

---

## 9) Bellman–Ford (negative weights) + negative cycle detect

**Use for:** negative edges / “is there an arbitrage cycle”.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v; long long w; };

pair<vector<long long>, bool> bellman_ford(int n, vector<Edge>& edges, int src) {
    const long long INF = (1LL << 62);
    vector<long long> dist(n, INF);
    dist[src] = 0;

    // Relax all edges up to (n-1) times.
    for (int i = 0; i < n - 1; i++) {
        bool any = false;                // Early-stop if no update in a full pass.

        for (auto &e : edges) {
            if (dist[e.u] == INF)
                continue;                // Can't relax from an unreachable node.
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                any = true;
            }
        }

        if (!any)
            break;
    }

    // One extra pass: any relaxation now means a reachable negative cycle exists.
    for (auto &e : edges) {
        if (dist[e.u] == INF)
            continue;
        if (dist[e.v] > dist[e.u] + e.w)
            return {dist, true};
    }
    return {dist, false};
}
```

---

## 10) Union-Find (DSU) for connectivity / cycle in undirected / Kruskal MST

**Use for:** dynamic connectivity, “number of components after unions”, MST.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;                    // p = parent, r = rank (approximate tree height).

    DSU(int n): p(n), r(n, 0) {
        iota(p.begin(), p.end(), 0);     // Initially each node is its own parent.
    }

    int find(int x) {
        // Path compression: flatten tree for near O(1) amortized finds.
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;                // Already in same set.

        if (r[a] < r[b])
            swap(a, b);                  // Union by rank: attach smaller depth under larger.

        p[b] = a;
        if (r[a] == r[b])
            r[a]++;

        return true;
    }
};

struct WEdge { int u, v; long long w; };

long long kruskal_mst(int n, vector<WEdge>& edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return a.w < b.w;                // Greedily process edges by smallest weight.
    });

    DSU dsu(n);
    long long cost = 0;
    int used = 0;                        // Number of edges included in MST.

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            if (++used == n - 1)
                break;                   // MST complete.
        }
    }

    if (used != n - 1)
        return -1;                       // Graph disconnected, MST doesn't exist.
    return cost;
}
```

---

## 11) Flood-fill on graphs (multi-source BFS)

**Use for:** nearest distance to any source, rotten oranges, 01 matrix, etc.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> multi_source_bfs(int n, vector<vector<int>>& g, vector<int> sources) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    queue<int> q;

    for (int s : sources) {
        dist[s] = 0;                     // All sources start at distance 0.
        q.push(s);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : g[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}
```

---

## 12) “Eventual Safe Nodes” / Reverse graph + outdegree (Topological trimming)

**Use for:** nodes not leading to a cycle (your earlier question is this pattern too).

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> eventual_safe_nodes(vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<vector<int>> rg(n);           // Reverse graph: v -> list of predecessors.
    vector<int> outdeg(n, 0);            // Remaining outgoing edges in original graph.

    for (int u = 0; u < n; u++) {
        outdeg[u] = (int)g[u].size();
        for (int v : g[u])
            rg[v].push_back(u);          // Reverse edge u -> v becomes v -> u.
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (outdeg[i] == 0)
            q.push(i);                   // Terminal nodes are always safe.

    vector<int> safe;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        safe.push_back(u);

        for (int p : rg[u]) {
            if (--outdeg[p] == 0)
                q.push(p);               // p becomes safe when all outgoing paths lead to safe nodes.
        }
    }

    sort(safe.begin(), safe.end());      // Problem asks for ascending order.
    return safe;
}
```

---

## 13) Tarjan SCC (Strongly Connected Components)

**Use for:** SCC condensation DAG, “cycles groups”, 2-SAT backbone.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct TarjanSCC {
    int n, timer = 0, compCnt = 0;
    vector<vector<int>> g;
    vector<int> disc, low, onst, st, comp;

    TarjanSCC(int n): n(n), g(n), disc(n, -1), low(n, 0), onst(n, 0), comp(n, -1) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;      // discovery time + initial low-link.
        st.push_back(u);                 // Push node to stack of active DFS path.
        onst[u] = 1;

        for (int v : g[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);   // Propagate child low-link up.
            } else if (onst[v]) {
                low[u] = min(low[u], disc[v]);  // Back-edge to active stack node.
            }
        }

        // If u is root of SCC, pop until u and assign component id.
        if (low[u] == disc[u]) {
            while (true) {
                int x = st.back(); st.pop_back();
                onst[x] = 0;
                comp[x] = compCnt;
                if (x == u)
                    break;
            }
            compCnt++;
        }
    }

    // Returns component id per node; compCnt stores number of SCCs after run().
    vector<int> run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1)
                dfs(i);
        return comp;
    }
};
```

---

## 14) Bridges + Articulation Points (Tarjan on undirected)

**Use for:** critical connections, single point of failure.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct BridgesAP {
    int n, timer = 0;
    vector<vector<int>> g;
    vector<int> disc, low, parent, isAP;
    vector<pair<int,int>> bridges;

    BridgesAP(int n): n(n), g(n), disc(n, -1), low(n, 0), parent(n, -1), isAP(n, 0) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        int children = 0;                // Number of DFS tree children (needed for root AP rule).

        for (int v : g[u]) {
            if (disc[v] == -1) {
                parent[v] = u;
                children++;
                dfs(v);

                low[u] = min(low[u], low[v]);

                // No back-edge from v-subtree to u/ancestors => edge (u,v) is bridge.
                if (low[v] > disc[u])
                    bridges.push_back({u, v});

                // Non-root articulation condition.
                if (parent[u] != -1 && low[v] >= disc[u])
                    isAP[u] = 1;
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]); // Back-edge update.
            }
        }

        // Root articulation condition: 2+ DFS children.
        if (parent[u] == -1 && children > 1)
            isAP[u] = 1;
    }

    void run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1)
                dfs(i);
    }
};
```

---

## 15) Shortest path with path reconstruction (parent array)

**Use for:** “print the path”, not just distance.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> reconstruct_path(int src, int dst, vector<int>& parent) {
    vector<int> path;
    if (dst < 0)
        return path;                     // Invalid destination guard.

    for (int cur = dst; cur != -1; cur = parent[cur])
        path.push_back(cur);             // Walk backwards: dst -> ... -> src.

    reverse(path.begin(), path.end());   // Convert to src -> ... -> dst order.

    if (path.empty() || path[0] != src)
        return {};                       // dst is unreachable from src.

    return path;
}

// Example helper: BFS that records parent pointers on first visit.
vector<int> bfs_parent(int n, vector<vector<int>>& g, int src) {
    vector<int> dist(n, -1), parent(n, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;           // Store how we reached v.
                q.push(v);
            }
        }
    }
    return parent;
}
```

---

## Practice: “Google Graph Set” (high ROI)

1. BFS + multi-source BFS
2. DFS components
3. Directed cycle detection (3-state) + Topo (Kahn)
4. Bipartite
5. Dijkstra + 0-1 BFS
6. DSU + Kruskal
7. SCC (Tarjan)
8. Bridges / articulation
9. Reverse-graph trimming (eventual safe nodes)
10. Path reconstruction

---

## Graph Patterns → Clickable LeetCode List (Google SDE)

---

### 1️⃣ BFS / DFS Basics

- [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)
- [733. Flood Fill](https://leetcode.com/problems/flood-fill/)
- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- [1971. Find if Path Exists in Graph](https://leetcode.com/problems/find-if-path-exists-in-graph/)

---

### 2️⃣ Multi-Source BFS

- [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [286. Walls and Gates](https://leetcode.com/problems/walls-and-gates/)
- [1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)

---

### 3️⃣ Cycle Detection (Directed & Undirected)

#### Undirected

- [261. Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)
- [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)

#### Directed

- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)

---

### 4️⃣ Topological Sort / Dependencies

- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
- [1203. Sort Items by Groups Respecting Dependencies](https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/)

---

### 5️⃣ Bipartite Graph

- [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)
- [886. Possible Bipartition](https://leetcode.com/problems/possible-bipartition/)
- [1042. Flower Planting With No Adjacent](https://leetcode.com/problems/flower-planting-with-no-adjacent/)

---

### 6️⃣ Shortest Path (BFS / Dijkstra / 0-1 BFS)

#### BFS

- [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/)
- [127. Word Ladder](https://leetcode.com/problems/word-ladder/)

#### Dijkstra

- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
- [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)
- [1514. Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/)

#### 0-1 BFS

- [1368. Minimum Cost to Make at Least One Valid Path](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)

---

### 7️⃣ Union-Find (DSU)

- [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)
- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- [721. Accounts Merge](https://leetcode.com/problems/accounts-merge/)
- [1202. Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/)
- [1579. Remove Max Number of Edges to Keep Graph Fully Traversable](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)

---

### 8️⃣ Minimum Spanning Tree (Kruskal / Prim)

- [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
- [1135. Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/)
- [1168. Optimize Water Distribution in a Village](https://leetcode.com/problems/optimize-water-distribution-in-a-village/)

---

### 9️⃣ Strongly Connected Components / Graph Connectivity

- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)

---

### 🔟 Bridges & Articulation Points

- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [1568. Minimum Number of Days to Disconnect Island](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/)

---

### 1️⃣1️⃣ Grid → Graph Modeling

- [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)
- [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)
- [529. Minesweeper](https://leetcode.com/problems/minesweeper/)
- [934. Shortest Bridge](https://leetcode.com/problems/shortest-bridge/)

---

### 1️⃣2️⃣ Hard / High-Signal Graph Problems

- [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
- [1368. Minimum Cost to Make at Least One Valid Path](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)
- [1203. Sort Items by Groups Respecting Dependencies](https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/)
- [847. Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- [2246. Longest Path With Different Adjacent Characters](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/)

---

## 🏆 Google “Do These First” (Direct Links)

1. [200 Number of Islands](https://leetcode.com/problems/number-of-islands/)
2. [207 Course Schedule](https://leetcode.com/problems/course-schedule/)
3. [210 Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
4. [269 Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
5. [127 Word Ladder](https://leetcode.com/problems/word-ladder/)
6. [743 Network Delay Time](https://leetcode.com/problems/network-delay-time/)
7. [994 Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
8. [785 Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)
9. [684 Redundant Connection](https://leetcode.com/problems/redundant-connection/)
10. [721 Accounts Merge](https://leetcode.com/problems/accounts-merge/)
11. [1584 Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
12. [1192 Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
13. [802 Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)
14. [1368 Minimum Cost to Make at Least One Valid Path in a Grid](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)
15. [934 Shortest Bridge](https://leetcode.com/problems/shortest-bridge/)
