/**
 * There are N gas stations along a circular route, where the amount of gas at
 * station i is gas[i].
 *
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to
 * travel from station i to its next station (i+1). You begin the journey with
 * an empty tank at one of the gas stations.
 *
 * Return the starting gas station's index if you can travel around the circuit
 * once, otherwise return -1.
 *
 * Note:
 * The solution is guaranteed to be unique.
 *
 * Tags: Greedy
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit_I(vector<int> &gas, vector<int> &cost) {
        int start=0, end=gas.size()-1;
        int sum=gas[end]-cost[end];
        while(start<end){
            if(sum>=0){
                sum+=gas[start]-cost[start];
                start++;
            }else{
                end--;
                sum+=gas[end]-cost[end];
            }
        }
        return (sum>=0)?start:-1;
    }
    
    int canCompleteCircuit_II(vector<int> &gas, vector<int> &cost) {
        int start=0;
        int sum=0, preNeed=0;
        for(int i=0;i<gas.size();i++){
            sum+=gas[i]-cost[i];
            if(sum<0){
                preNeed+=sum;
                sum=0;
                start=i+1;
            }
        }
        return (sum+preNeed>=0)?start:-1;
    }
};