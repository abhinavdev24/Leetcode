#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *insertionSortList(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode dummy(0);
        ListNode *curr = head;
        while (curr)
        {
            ListNode *nextNode = curr->next;
            ListNode *prev = &dummy;
            while (prev->next && prev->next->val < curr->val)
                prev = prev->next;
            curr->next = prev->next;
            prev->next = curr;
            curr = nextNode;
        }
        return dummy.next;
    }
};

ListNode *build_list(const vector<int> &values)
{
    ListNode dummy(0);
    ListNode *tail = &dummy;
    for (int value : values)
    {
        tail->next = new ListNode(value);
        tail = tail->next;
    }
    return dummy.next;
}

vector<int> list_to_vector(ListNode *head)
{
    vector<int> out;
    while (head)
    {
        out.push_back(head->val);
        head = head->next;
    }
    return out;
}

string vec_to_string(const vector<int> &nums)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << nums[i];
    }
    ss << "]";
    return ss.str();
}

void free_list(ListNode *head)
{
    while (head)
    {
        ListNode *next = head->next;
        delete head;
        head = next;
    }
}

int main()
{
    Solution sol;
    vector<vector<int>> samples = {
        {4, 2, 1, 3},
        {-1, 5, 3, 4, 0},
    };
    vector<vector<int>> expected = {
        {1, 2, 3, 4},
        {-1, 0, 3, 4, 5},
    };

    for (size_t i = 0; i < samples.size(); ++i)
    {
        ListNode *head = build_list(samples[i]);
        ListNode *result_head = sol.insertionSortList(head);
        vector<int> result = list_to_vector(result_head);

        cout << "Sample " << (i + 1) << ": head = " << vec_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << vec_to_string(result) << "\n";
        cout << "Expected output: " << vec_to_string(expected[i]) << "\n\n";

        free_list(result_head);
    }

    return 0;
}
