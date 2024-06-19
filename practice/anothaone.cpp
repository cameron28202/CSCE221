#include <unordered_map>
#include <string>

using namespace std;
/*
Problem: First Unique Character in a String
Description: Given a string, find the first non-repeating character in it and return its index. If it doesn't exist, return -1.

Example:

Input: "leetcode"
Output: 0

Explanation: 'l' is the first character that does not repeat elsewhere in the string.

*/


char solution(string s){
    unordered_map<char, int> mp;
    string ans;

    for(int i = 0; i < s.length(); ++i){
        mp[s[i]] = i;
    }

    for(int j = 0; j < s.length(); ++j){
        if(mp[s[j]] == j){
            return s[j];
        }
    }

    return -1;

}