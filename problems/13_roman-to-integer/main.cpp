#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int romanToInt(string s)
    {
        int ans = 0;

        // Iterate over the string
        for (int i = 0; i < s.size(); i++)
        {
            char c = s.at(i);
            if (c == 'I')
            {
                if (i + 1 < s.size() && s.at(i + 1) == 'V')
                {
                    ans += 4;
                    i++;
                }
                else if (i + 1 < s.size() && s.at(i + 1) == 'X')
                {
                    ans += 9;
                    i++;
                }
                else
                {
                    ans += 1;
                }
            }
            else if (c == 'V')
            {
                ans += 5;
            }
            else if (c == 'X')
            {
                if (i + 1 < s.size() && s.at(i + 1) == 'L')
                {
                    ans += 40;
                    i++;
                }
                else if (i + 1 < s.size() && s.at(i + 1) == 'C')
                {
                    ans += 90;
                    i++;
                }
                else
                {
                    ans += 10;
                }
            }
            else if (c == 'L')
            {
                ans += 50;
            }
            else if (c == 'C')
            {
                if (i + 1 < s.size() && s.at(i + 1) == 'D')
                {
                    ans += 400;
                    i++;
                }
                else if (i + 1 < s.size() && s.at(i + 1) == 'M')
                {
                    ans += 900;
                    i++;
                }
                else
                {
                    ans += 100;
                }
            }
            else if (c == 'D')
            {
                ans += 500;
            }
            else if (c == 'M')
            {
                ans += 1000;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    string sample1 = "III";
    string sample2 = "LVIII";
    string sample3 = "MCMXCIV";

    int result1 = sol.romanToInt(sample1);
    cout << "Sample 1 placeholder result: " << result1 << "\n";
    cout << "Sample 1 expected output: 3\n\n";

    int result2 = sol.romanToInt(sample2);
    cout << "Sample 2 placeholder result: " << result2 << "\n";
    cout << "Sample 2 expected output: 58\n\n";

    int result3 = sol.romanToInt(sample3);
    cout << "Sample 3 placeholder result: " << result3 << "\n";
    cout << "Sample 3 expected output: 1994\n";

    return 0;
}
