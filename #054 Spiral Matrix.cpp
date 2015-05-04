/**
 * Given a matrix of m x n elements (m rows, n columns), return all elements of
 * the matrix in spiral order.
 *
 * For example,
 * Given the following matrix:
 *
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * You should return [1,2,3,6,9,8,7,4,5].
 *
 * Tags: Array
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //使用四个标记来确定一个外圈所走的范围
    //走完一圈后，各标记减1，继续走下一圈
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        if(matrix.empty()) return ret;
        int left=0, right=matrix[0].size()-1, up=0, down=matrix.size()-1;
        while(left<=right && up<=down){
            for(int i=left;i<=right;i++)
                ret.push_back(matrix[up][i]);
            up++;
            for(int i=up;i<=down;i++)
                ret.push_back(matrix[i][right]);
            right--;
            if(up<=down)
                for(int i=right;i>=left;i--)
                    ret.push_back(matrix[down][i]);
            down--;
            if(left<=right)
                for(int i=down;i>=up;i--)
                    ret.push_back(matrix[i][left]);
            left++;
        }
        return ret;
    }
};
