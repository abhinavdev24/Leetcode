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
    ListNode *merge(ListNode *a, ListNode *b)
    {
        ListNode dummy(0);
        ListNode *curr = &dummy;
        while (a && b)
        {
            if (a->val < b->val)
            {
                curr->next = a;
                a = a->next;
            }
            else
            {
                curr->next = b;
                b = b->next;
            }
            curr = curr->next;
        }
        if (a)
            curr->next = a;
        if (b)
            curr->next = b;
        return dummy.next;
    }
    ListNode *sortList(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode *slow = head, *fast = head, *prev = 0, *left, *right;
        while (fast && fast->next)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = 0;            // partition the list into two parts
        left = sortList(head);     // sort the left half of the list
        right = sortList(slow);    // sort the right half of the list
        return merge(left, right); // merge the two sorted lists
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
        {}};
    vector<vector<int>> expected = {
        {1, 2, 3, 4},
        {-1, 0, 3, 4, 5},
        {}};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        ListNode *head = build_list(samples[i]);
        ListNode *result_head = sol.sortList(head);
        vector<int> result = list_to_vector(result_head);

        cout << "Sample " << (i + 1) << ": head = " << vec_to_string(samples[i]) << "\n";
        cout << "Placeholder result: " << vec_to_string(result) << "\n";
        cout << "Expected output: " << vec_to_string(expected[i]) << "\n\n";

        free_list(result_head);
    }

    return 0;
}
