/**
 * A peak element is an element that is greater than its neighbors.
 *
 * Given an input array where num[i] ≠ num[i+1], find a peak element and return
 * its index.
 *
 * You may imagine that num[-1] = num[n] = -∞.
 *
 * For example, in array [1, 2, 3, 1], 3 is a peak element and your function
 * should return the index number 2.
 *
 * Note:
 * Your solution should be in logarithmic complexity.
 *
 * Tags: Array, Binary Search
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * 因为两侧可以认为是负无穷，所以0和nums.size()-1肯定大于它们的外侧
 * 考虑mid位置的情况，如果mid>mid+1，那么在[0, mid]这个范围内
 * 如果0和mid的两侧比它们大，即0和mid不是peak的话，那么从它们出发往内侧走肯定是双向递增的
 * 又因为这个序列里没有重复的数值，当两个方向的递增序列相遇时一定会有一个peak
 * 所以[0, mid]内一定有peak
 * 同理mid<mid+1
 * 因为low和high的选取条件决定了它们一定比它们外侧的数值大，所以[low, high]中一定有peak
 * 需注意的是，因为mid=low+(high-low)/2，所以mid的取值偏向较小的一侧，检查mid和mid+1不会越界
 * 如果检查mid和mid-1可能会越界
 */

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low=0, high=nums.size()-1;
        while(low<high){
            int mid=low+(high-low)/2;
            if(nums[mid]>nums[mid+1])
                high=mid;
            else
                low=mid+1;
        }
        return low;
    }
};
