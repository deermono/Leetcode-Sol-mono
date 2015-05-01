/**
 * Given two strings s and t, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 *
 * All occurrences of a character must be replaced with another character while preserving the order of characters. 
 * No two characters may map to the same character but a character may map to itself.
 * 
 * For example,
 * Given "egg", "add", return true.
 * Given "foo", "bar", return false.
 * Given "paper", "title", return true.
 *
 * Note:
 * You may assume both s and t have the same length.
 *
 * Tags: HashTable
 */

#include <iostream>

using namespace std;

/**
 * 当出现一组字母对应时，记录它们出现的位置
 * 如果有一对字母上次出现的位置不一样，则说明不满足匹配
 */

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int check[512]={0};
        for(int i=0;i<s.length();i++){
            if(check[s[i]]!=check[t[i]+256])
                return false;
            else
                check[s[i]]=check[t[i]+256]=i+1;
        }
        return true;
    }
};