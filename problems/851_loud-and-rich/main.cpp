#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int dfs(int u, vector<vector<int>> &graph, vector<int> &quiet, vector<int> &ans)
    {
        if (ans[u] != -1)
            return ans[u];
        ans[u] = u;
        for (int v : graph[u])
        {
            int t = dfs(v, graph, quiet, ans);
            if (quiet[t] < quiet[ans[u]])
                ans[u] = t;
        }
        return ans[u];
    }

    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        vector<int> ans(n, -1);
        vector<vector<int>> graph(n);

        for (auto &e : richer)
            graph[e[1]].push_back(e[0]);

        for (int i = 0; i < n; i++)
            if (ans[i] == -1)
                dfs(i, graph, quiet, ans);

        return ans;
    }

    vector<int> loudAndRichTopological(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        vector<int> res(n);
        if (n == 0)
            return res;
        vector<vector<int>> graph(n);
        vector<int> indeg(n, 0);
        for (int i = 0; i < richer.size(); i++)
        {
            graph[richer[i][0]].push_back(richer[i][1]);
            indeg[richer[i][1]]++;
        }

        for (int i = 0; i < n; ++i)
            res[i] = i;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (auto nei : graph[curr])
            {
                if (quiet[res[curr]] < quiet[res[nei]])
                {
                    res[nei] = res[curr];
                }
                if (--indeg[nei] == 0)
                    q.push(nei);
            }
        }

        return res;
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

    vector<vector<int>> richer1 = {{1, 0}, {2, 1}, {3, 1}, {3, 7}, {4, 3}, {5, 3}, {6, 3}};
    vector<int> quiet1 = {3, 2, 5, 4, 6, 1, 7, 0};
    vector<vector<int>> richer2 = {};
    vector<int> quiet2 = {0};

    auto result1 = sol.loudAndRich(richer1, quiet1);
    cout << "Sample 1 placeholder result: ";
    printVector(result1);
    cout << "\nSample 1 expected output: [5,5,2,5,4,5,6,7]\n\n";

    auto result2 = sol.loudAndRich(richer2, quiet2);
    cout << "Sample 2 placeholder result: ";
    printVector(result2);
    cout << "\nSample 2 expected output: [0]\n";

    return 0;
}
