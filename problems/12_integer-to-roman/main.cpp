#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    string intToRoman(int num)
    {
        string romanSymbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string ans = "";
        for (int i = 0; i < 13; i++)
        {
            while (num >= values[i])
            {
                ans += romanSymbols[i];
                num = num - values[i];
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;

    int sample1 = 3749;
    int sample2 = 58;
    int sample3 = 1994;

    string result1 = sol.intToRoman(sample1);
    cout << "Sample 1 placeholder result: \"" << result1 << "\"\n";
    cout << "Sample 1 expected output: \"MMMDCCXLIX\"\n\n";

    string result2 = sol.intToRoman(sample2);
    cout << "Sample 2 placeholder result: \"" << result2 << "\"\n";
    cout << "Sample 2 expected output: \"LVIII\"\n\n";

    string result3 = sol.intToRoman(sample3);
    cout << "Sample 3 placeholder result: \"" << result3 << "\"\n";
    cout << "Sample 3 expected output: \"MCMXCIV\"\n";

    return 0;
}
