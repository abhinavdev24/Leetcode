#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        vector<int> dp(n + 1, -1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '0')
            {
                dp[i] = 0;
                continue;
            }
            dp[i] = dp[i + 1];
            if (i + 1 < n)
            {
                int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (val >= 10 && val <= 26)
                    dp[i] += dp[i + 2];
            }
        }
        return dp[0];
    }
};

int main()
{
    Solution solution;

    vector<pair<string, int>> samples = {
        {"12", 2},
        {"226", 3},
        {"06", 0},
    };

    for (size_t i = 0; i < samples.size(); ++i)
    {
        const string &s = samples[i].first;
        int expected = samples[i].second;
        int result = solution.numDecodings(s);

        cout << "Example " << (i + 1) << " result: " << result
             << ", expected: " << expected << '\n';
    }

    return 0;
}
