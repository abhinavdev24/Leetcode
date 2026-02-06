#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    TreeNode *build(const vector<int> &nums, int l, int r)
    {
        if (l > r)
            return nullptr;
        int mid = l + (r - l) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = build(nums, l, mid - 1);
        root->right = build(nums, mid + 1, r);
        return root;
    }

    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return build(nums, 0, (int)nums.size() - 1);
    }
};

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

string preorder_with_nulls(TreeNode *root)
{
    if (!root)
    {
        return "null";
    }
    return to_string(root->val) + "," + preorder_with_nulls(root->left) + "," + preorder_with_nulls(root->right);
}

void free_tree(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

int main()
{
    Solution sol;

    vector<vector<int>> samples = {
        {-10, -3, 0, 5, 9},
        {1, 3}};
    vector<string> expected = {
        "[0,-3,9,-10,null,5] or [0,-10,5,null,-3,null,9]",
        "[3,1] or [1,null,3]"};

    for (size_t i = 0; i < samples.size(); ++i)
    {
        vector<int> nums = samples[i];
        TreeNode *result = sol.sortedArrayToBST(nums);

        cout << "Sample " << (i + 1) << ": nums = " << vec_to_string(samples[i]) << "\n";
        cout << "Placeholder result (preorder with nulls): " << preorder_with_nulls(result) << "\n";
        cout << "Expected output: " << expected[i] << "\n\n";

        free_tree(result);
    }

    return 0;
}
