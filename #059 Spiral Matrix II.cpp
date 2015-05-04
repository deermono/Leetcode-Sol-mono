/**
 * Given an integer n, generate a square matrix filled with elements from 1 to
 * n^2 in spiral order.
 *
 * For example,
 * Given n = 3,
 *
 * You should return the following matrix:
 * [
 *  [ 1, 2, 3 ],
 *  [ 8, 9, 4 ],
 *  [ 7, 6, 5 ]
 * ]
 *
 * Tags: Array
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //方法同Spiral Matrix，使用四个方向标记
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n, vector<int>(n, 0));
        int num=1;
        int left=0, right=n-1, up=0, down=n-1;
        while(left<=right){
            for(int i=left;i<=right;i++)
                ret[up][i]=num++;
            up++;
            for(int i=up;i<=down;i++)
                ret[i][right]=num++;
            right--;
            for(int i=right;i>=left;i--)
                ret[down][i]=num++;
            down--;
            for(int i=down;i>=up;i--)
                ret[i][left]=num++;
            left++;
        }
        return ret;
    }
    
    //实际上因为矩阵形状是固定的正方形，所以可以算出走到了哪一行哪一列
    vector<vector<int>> generateMatrix_I(int n) {
        vector<vector<int>> ret(n, vector<int>(n, 0));
        int num=1;
        for(int i=0;i<(1+n)/2;i++){
            for(int j=i;j<n-i;j++)
                ret[i][j]=num++;
            for(int j=i+1;j<n-i;j++)
                ret[j][n-i-1]=num++;
            for(int j=n-i-2;j>=i;j--)
                ret[n-i-1][j]=num++;
            for(int j=n-i-2;j>i;j--)
                ret[j][i]=num++;
        }
        return ret;
    }
};
