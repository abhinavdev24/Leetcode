#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = 0;
        unordered_set<int> rows;
        unordered_set<int> cols;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        };
        for (auto i : rows)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = 0;
            }
        }
        for (auto j : cols)
        {
            for (int i = 0; i < m; i++)
            {
                matrix[i][j] = 0;
            }
        }
    }
};

void printMatrix(const vector<vector<int>> &matrix)
{
    cout << "[";
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        cout << "[";
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            cout << matrix[i][j];
            if (j + 1 < matrix[i].size())
                cout << ", ";
        }
        cout << "]";
        if (i + 1 < matrix.size())
            cout << ", ";
    }
    cout << "]";
}

int main()
{
    Solution sol;

    vector<vector<int>> sample1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    vector<vector<int>> sample2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};

    sol.setZeroes(sample1);
    cout << "Sample 1 placeholder result: ";
    printMatrix(sample1);
    cout << "\nSample 1 expected output: [[1,0,1],[0,0,0],[1,0,1]]\n\n";

    sol.setZeroes(sample2);
    cout << "Sample 2 placeholder result: ";
    printMatrix(sample2);
    cout << "\nSample 2 expected output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]\n";

    return 0;
}
