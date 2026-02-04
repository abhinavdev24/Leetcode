#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> mp;
        for (int i = 0; i < strs.size(); i++)
        {
            string sorted = strs[i]; // create a copy for sorting
            sort(sorted.begin(), sorted.end());
            mp[sorted].push_back(strs[i]);
        }
        vector<vector<string>> res;
        res.reserve(mp.size());
        for (auto &kv : mp)
        {
            res.push_back(kv.second);
        }
        return res;
    }
};

void printGroups(const vector<vector<string>> &groups)
{
    cout << "[";
    for (size_t i = 0; i < groups.size(); ++i)
    {
        cout << "[";
        for (size_t j = 0; j < groups[i].size(); ++j)
        {
            cout << '"' << groups[i][j] << '"';
            if (j + 1 < groups[i].size())
                cout << ", ";
        }
        cout << "]";
        if (i + 1 < groups.size())
            cout << ", ";
    }
    cout << "]";
}

int main()
{
    Solution sol;

    vector<string> sample1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> sample2 = {""};
    vector<string> sample3 = {"a"};

    auto result1 = sol.groupAnagrams(sample1);
    cout << "Sample 1 placeholder result: ";
    printGroups(result1);
    cout << "\nSample 1 expected output: [[\"bat\"],[\"nat\",\"tan\"],[\"ate\",\"eat\",\"tea\"]]\n\n";

    auto result2 = sol.groupAnagrams(sample2);
    cout << "Sample 2 placeholder result: ";
    printGroups(result2);
    cout << "\nSample 2 expected output: [[\"\"]]\n\n";

    auto result3 = sol.groupAnagrams(sample3);
    cout << "Sample 3 placeholder result: ";
    printGroups(result3);
    cout << "\nSample 3 expected output: [[\"a\"]]\n";

    return 0;
}
