/**
 * Given a range [m, n] where 0 <= m <= n <= 2147483647,
 * return the bitwise AND of all numbers in this range, inclusive.
 *
 * Tags: Bit Manipulation
 */

#include <iostream>

using namespace std;

/**
 * 实质就是检测m,n中从头开始有多少位连续的相同的1
 * 例如：n=15(1111), m=12(1100)
 * 这个范围内：
 * 1 1 1 1
 * 1 1 1 0
 * 1 1 0 1
 * 1 1 0 0
 * -->> return 1100
 */

class Solution {
public:
    //右移i位直到两个数相同
    int rangeBitwiseAnd(int m, int n) {
        int i=0;
        while(m!=n){
            m>>=1;
            n>>=1;
            i++;
        }
        return m<<i;
    }
    
    //n每次去掉末位的1，直到n<=m
    int rangeBitwiseAnd_I(int m, int n) {
        while(n>m)
            n&=n-1;
        return n;
    }
    
    //逐渐去掉末尾不一样的部分，直到两个数相同
    int rangeBitwiseAnd_II(int m, int n) {
        int mask=INT_MAX;
        while((m&mask)!=(n&mask))
            mask<<=1;
        return m&mask;
    }
};
