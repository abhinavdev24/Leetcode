#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        int i = s.size() - 1;
        string result;

        while (i >= 0)
        {
            // skip spaces
            while (i >= 0 && s[i] == ' ')
                i--;

            if (i < 0)
                break;

            int j = i;
            // find start of the word
            while (j >= 0 && s[j] != ' ')
                j--;

            // append word
            if (!result.empty())
                result += ' ';
            result += s.substr(j + 1, i - j);

            i = j - 1;
        }

        return result;
    }
};

int main()
{
    Solution sol;

    string sample1 = "the sky is blue";
    string sample2 = "  hello world  ";
    string sample3 = "a good   example";

    string result1 = sol.reverseWords(sample1);
    cout << "Sample 1 placeholder result: \"" << result1 << "\"\n";
    cout << "Sample 1 expected output: \"blue is sky the\"\n\n";

    string result2 = sol.reverseWords(sample2);
    cout << "Sample 2 placeholder result: \"" << result2 << "\"\n";
    cout << "Sample 2 expected output: \"world hello\"\n\n";

    string result3 = sol.reverseWords(sample3);
    cout << "Sample 3 placeholder result: \"" << result3 << "\"\n";
    cout << "Sample 3 expected output: \"example good a\"\n";

    return 0;
}
