/**
 * Count the number of prime numbers less than a non-negative number, n
 *
 * Tags: HashTable, Math
 */

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/**
 * 如果某数是质数，则将所有它的倍数都标记为true
 * 这样当遇到某数i，如果它有任何一个非i非1的因子，之前都会被标记为true，否则它就是质数
 * 注意2的倍数在检测时已经跳过，都不标记，所以可以认为check数组中偶数下标都是true，也是不必要的
 * 对质数i，任意k<i，k*i已经在之前检测k的倍数时都标记过，所以从i*i开始标记即可
 * 当i>sqrt(n)时，就没有必要进行后续检测了
 * 因为质数i必为奇数，i*i也为奇数，i*i+(2k+1)*i必为偶数，所以以2*i为跨度进行标记即可
 */

class Solution {
public:
    int countPrimes(int n) {
        if(n<3) return 0;
        int ret=1, upper=sqrt(n)+1;
        vector<bool> check(n, false);
        for(int i=3;i<n;i+=2){
            if(!check[i]){
                ret++;
                if(i<upper)
                    for(int j=i*i, k=i<<1;j<n;j+=k)
                        check[j]=true;
            }
        }
        return ret;
    }
};
