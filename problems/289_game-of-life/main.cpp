#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    void gameOfLife(vector<vector<int>> &board)
    {
        int m = (int)board.size();
        int n = (int)board[0].size();

        static const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        static const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        // 1st pass: mark transitions using 2 and 3
        for (int r = 0; r < m; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                int live = 0;
                for (int k = 0; k < 8; ++k)
                {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;
                    int v = board[nr][nc];
                    if (v == 1 || v == 2)
                        live++; // currently alive
                }

                if (board[r][c] == 1)
                {
                    if (live < 2 || live > 3)
                        board[r][c] = 2; // live -> dead
                }
                else
                { // dead
                    if (live == 3)
                        board[r][c] = 3; // dead -> live
                }
            }
        }

        // 2nd pass: finalize to 0/1
        for (int r = 0; r < m; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                board[r][c] &= 1; // 0->0, 1->1, 2->0, 3->1
            }
        }
    }
};

string board_to_string(const vector<vector<int>> &board)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < board.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << "[";
        for (size_t j = 0; j < board[i].size(); ++j)
        {
            if (j > 0)
            {
                ss << ", ";
            }
            ss << board[i][j];
        }
        ss << "]";
    }
    ss << "]";
    return ss.str();
}

int main()
{
    Solution sol;

    vector<vector<vector<int>>> samples = {
        {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}},
        {{1, 1}, {1, 0}}};

    vector<vector<vector<int>>> expected = {
        {{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}},
        {{1, 1}, {1, 1}}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<vector<int>> board = samples[i];
        sol.gameOfLife(board);

        cout << "Sample " << (i + 1) << ": board = " << board_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << board_to_string(board) << "\n";
        cout << "Expected output: " << board_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
