#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;

        for(int i=0; i< nums.size(); i++){
            int need = target - nums[i];
            if(mp.find(need) != mp.end()){
                return {mp[need], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};

string vec_to_string(const vector<int>& nums) {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }
        ss << nums[i];
    }
    ss << "]";
    return ss.str();
}

int main() {
    Solution sol;
    vector<vector<int>> samples = {
        {2, 7, 11, 15},
        {3, 2, 4},
        {3, 3}
    };
    vector<int> targets = {9, 6, 6};
    vector<vector<int>> expected = {
        {0, 1},
        {1, 2},
        {0, 1}
    };

    for (size_t i = 0; i < samples.size(); ++i) {
        vector<int> nums = samples[i];
        vector<int> result = sol.twoSum(nums, targets[i]);
        cout << "Sample " << (i + 1) << ": nums = " << vec_to_string(samples[i])
             << ", target = " << targets[i] << "\n";
        cout << "Placeholder result: " << vec_to_string(result) << "\n";
        cout << "Expected output: " << vec_to_string(expected[i]) << "\n\n";
    }

    return 0;
}
