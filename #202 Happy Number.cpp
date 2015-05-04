/**
 * Write an algorithm to determine if a number is "happy".
 *
 * A happy number is a number defined by the following process:
 * Starting with any positive integer, replace the number by the sum of the squares of its digits,
 * and repeat the process until the number equals 1 (where it will stay), 
 * or it loops endlessly in a cycle which does not include 1. 
 * Those numbers for which this process ends in 1 are happy numbers.
 *
 * Example: 19 is a happy number
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 * Tags: HashTable, Math
 */

#include <iostream>

using namespace std;

class Solution {
public:
    //检测n的循环中是否会出现4，如果出现4就不是happy number
    //数学证明：任何数在经历一定量的过程后，都会落至[1, 99]的范围中
    //在此范围内，可以看出，任何非happy number都会进入4的循环中
    //具体证明见wiki
    bool isHappy(int n) {
        int sum=0;
        while(n>1 && n!=4){
            while(n>0){
                sum+=(n%10)*(n%10);
                n/=10;
            }
            n=sum;
            sum=0;
        }
        return n==1;
    }
    
    //Floyd cycle detection
    //和Linked List Cycle方法相同，用一个慢指针和一个快指针检测是否存在环
    int next(int n){
        int sum=0;
        while(n>0){
            sum+=(n%10)*(n%10);
            n/=10;
        }
        return sum;
    }
    
    bool isHappy_I(int n) {
        int slow=next(n), fast=next(next(n));
        while(slow!=fast){
            slow=next(slow);
            fast=next(next(fast));
        }
        return slow==1;
    }
};
