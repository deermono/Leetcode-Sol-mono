/**
 * Given an array of integers, find two numbers such that they add up to a
 * specific target number.
 *
 * The function twoSum should return indices of the two numbers such that they
 * add up to the target, where index1 must be less than index2. Please note
 * that your returned answers (both index1 and index2) are not zero-based.
 *
 * You may assume that each input would have <strong>exactly one</strong>
 * solution.
 *
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 *
 * Tags: Array, HashTable
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Time:O(n) Space:O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for(int i = 0; i < nums.size(); i++){
            int findNum = target - nums[i];
            if(hash.find(findNum) != hash.end())
                return {hash[findNum], i + 1};
            else
                hash[nums[i]] = i + 1;
        }
        return {-1, -1};
    }
};