#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (n == 0 || n == 1)
            return {0};
        vector<int> indegree(n, 0);
        vector<vector<int>> graph(n);
        for (auto e : edges)
        {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
            indegree[e[1]]++;
            indegree[e[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 1)
                q.push(i); // push all the root nodes possible
        int remaining = n;
        while (remaining > 2)
        { // Removing leaves layer by layer
            int sz = (int)q.size();
            remaining -= sz;

            while (sz--)
            {
                int leaf = q.front();
                q.pop();
                for (int nei : graph[leaf])
                {
                    if (--indegree[nei] == 1)
                        q.push(nei);
                }
            }
        }

        vector<int> res;
        while (!q.empty())
        {
            res.push_back(q.front());
            q.pop();
        }
        return res;
    }
};

static void printVector(const vector<int> &values)
{
    cout << "[";
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i > 0)
        {
            cout << ",";
        }
        cout << values[i];
    }
    cout << "]";
}

int main()
{
    Solution solution;

    vector<vector<int>> edges1 = {{1, 0}, {1, 2}, {1, 3}};
    vector<int> result1 = solution.findMinHeightTrees(4, edges1);
    cout << "Sample 1 placeholder result: ";
    printVector(result1);
    cout << "\nSample 1 expected output: [1]\n";

    vector<vector<int>> edges2 = {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
    vector<int> result2 = solution.findMinHeightTrees(6, edges2);
    cout << "Sample 2 placeholder result: ";
    printVector(result2);
    cout << "\nSample 2 expected output: [3,4]\n";

    return 0;
}
