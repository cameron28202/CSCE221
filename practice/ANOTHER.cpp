#include <unordered_map>
#include <queue>

using namespace std;

/*
Problem: Top K Frequent Elements
Description: Given an integer array and a number k, return the k most frequent elements. You should return the answer in any order.

Example:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Explanation: '1' appears three times and '2' appears twice, making them the most frequent elements.

Input: nums = [1], k = 1
Output: [1]

Explanation: '1' is the only element and thus is the most frequent.

Requirements:
The answer should be unique elements.
k is always valid.


*/

vector<int> topKFrequent(vector<int>& nums, int k) {
    // Map to count frequency of each element
    unordered_map<int, int> counts;
    for (int num : nums) {
        ++counts[num];
    }

    // Min-heap to keep the top k elements with highest frequency
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    for (auto& count : counts) {
        minHeap.push({count.second, count.first});  // Push frequency and element
        if (minHeap.size() > k) {
            minHeap.pop();  // Remove the element with the lowest frequency
        }
    }

    // Extract the top k elements from the heap
    vector<int> topK;
    while (!minHeap.empty()) {
        topK.push_back(minHeap.top().second);
        minHeap.pop();
    }

    return topK;
}