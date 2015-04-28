/**
 * Implement regular expression matching with support for '.' and '*'.
 *
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 *
 * The matching should cover the entire input string (not partial).
 *
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch("aa","a") → false
 * isMatch("aa","aa") → true
 * isMatch("aaa","aa") → false
 * isMatch("aa", "a*") → true
 * isMatch("aa", ".*") → true
 * isMatch("ab", ".*") → true
 * isMatch("aab", "c*a*b") → true
 *
 * Note:
 * "*" only works on the preceding one element, not the whole string.
 *
 * Tags: DP, Backtracking, String
 */

#include <iostream>

using namespace std;

/**
 * dp[i+1][j+1]代表s[0..i]与p[0..j]匹配
 * 对于dp[i+1][j+1]取真值，考虑如下几种情况：
 * (1) p[j]!='*'，则p[j]必须和s[i]匹配（最后一个字符），并且s[0..i-1]和p[0..j-1]匹配
 * (2) p[j]=='*'，共三种情况：
 *     1. 这个'*'匹配了零次，则s[0..i]和p[0..j-2]匹配，然后这个'*'对它之前的字符取了零次
 *     2. 这个'*'匹配了一次，则s[0..i]和p[0..j-1]匹配，然后这个'*'对它之前的字符取了一次，相当于没有作用
 *     3. 这个'*'匹配了二到多次，则s[0..i-1]和p[0..j]匹配，且s[i]和'*'之前的字符，也就是p[j-1]匹配，相当于'*'增加重复了一次
 * 所以对于dp[i+1][j+1]，需要知道dp[i][j], dp[i+1][j-1], dp[i+1][j], dp[i][j+1]
 * 
 * 将dp的大小设置为m+1, n+1，初始化的几种情况如下
 * (1) dp[0][0]代表空串和空串匹配
 * (2) dp[i+1][0]==false代表s串只要出现字符，就无法和空串匹配
 * (3) dp[0][j+1]==true代表p[0..j]可以和空串匹配，也就是p[j]=='*'，这个'*'把前一个字符p[j-1]取了零次，且p[0..j-2]也可以匹配到空串
 *
 * 本题默认字符串s中只出现字符没有符号，且p中不会出现无意义的排列比如'**'或第一个字符就是'*'
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        int m=s.length(), n=p.length();
        bool dp[m+1][n+1];
        dp[0][0]=true;
        for(int i=0;i<m;i++)
            dp[i+1][0]=false;
        for(int j=0;j<n;j++)
            dp[0][j+1]=(p[j]=='*' && dp[0][j-1]==true);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                if(p[j]!='*')
                    dp[i+1][j+1]=dp[i][j] && (p[j]=='.' || s[i]==p[j]);
                else
                    dp[i+1][j+1]=dp[i+1][j-1] || dp[i+1][j] || (dp[i][j+1] && (s[i]==p[j-1] || p[j-1]=='.'));
            }
        return dp[m][n];
    }
};
