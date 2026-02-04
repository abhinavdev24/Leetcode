#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool dfs(int u, vector<vector<int>> &graph, vector<char> &state)
    {
        if (state[u] == 1)
            return false; // found a cycle => unsafe
        if (state[u] == 2)
            return true; // already known safe

        state[u] = 1; // mark visiting
        for (int v : graph[u])
        {
            if (!dfs(v, graph, state))
                return false;
        }
        state[u] = 2; // all neighbors safe => safe
        return true;
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = (int)graph.size();
        vector<char> state(n, 0);
        vector<int> safe;
        safe.reserve(n);

        for (int i = 0; i < n; ++i)
        {
            if (dfs(i, graph, state))
                safe.push_back(i);
        }
        return safe; // already in ascending order
    }
    bool dfsDetectCycle(int node, vector<vector<int>> &graph, vector<bool> &vis, vector<bool> &path, vector<int> &safenodes)
    {
        vis[node] = true;
        path[node] = true;
        for (auto nei : graph[node])
        {
            if (!vis[nei])
            {
                if (dfsDetectCycle(nei, graph, vis, path, safenodes))
                    return true;
            }
            else if (path[nei])
                return true;
        }
        safenodes.push_back(node);
        path[node] = false;
        return false;
    }
    vector<int> eventualSafeNodes_2(vector<vector<int>> &graph)
    {
        vector<bool> vis(graph.size(), false), path(graph.size(), false);
        vector<int> safenodes;
        safenodes.reserve(graph.size());
        for (int i = 0; i < graph.size(); i++)
        {
            if (!vis[i])
                dfsDetectCycle(i, graph, vis, path, safenodes);
        }
        sort(safenodes.begin(), safenodes.end());
        return safenodes;
    }
    vector<int> eventualSafeNodes_3(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<vector<int>> rev(n);
        vector<int> outdegree(n, 0);
        for (int i = 0; i < n; i++)
        {
            outdegree[i] = graph[i].size();
            for (auto nei : graph[i])
            {
                rev[nei].push_back(i);
            }
        }
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (outdegree[i] == 0)
                q.push(i);

        vector<int> safenodes;
        safenodes.reserve(n);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            safenodes.push_back(curr);
            for (auto nei : rev[curr])
            {
                outdegree[nei]--;
                if (outdegree[nei] == 0)
                    q.push(nei);
            }
        }
        sort(safenodes.begin(), safenodes.end());
        return safenodes;
    }
};

void printVector(const vector<int> &values)
{
    cout << "[";
    for (size_t i = 0; i < values.size(); ++i)
    {
        cout << values[i];
        if (i + 1 < values.size())
            cout << ", ";
    }
    cout << "]";
}

int main()
{
    Solution sol;

    vector<vector<int>> sample1 = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<vector<int>> sample2 = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};

    auto result1 = sol.eventualSafeNodes(sample1);
    cout << "Sample 1 placeholder result: ";
    printVector(result1);
    cout << "\nSample 1 expected output: [2,4,5,6]\n\n";

    auto result2 = sol.eventualSafeNodes(sample2);
    cout << "Sample 2 placeholder result: ";
    printVector(result2);
    cout << "\nSample 2 expected output: [4]\n";

    return 0;
}
