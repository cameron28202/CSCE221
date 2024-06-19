#include <unordered_map>
#include <vector>

using namespace std;

vector<int> findIntersection(vector<int> arr1, vector<int> arr2){

    unordered_map<int, int> mp;
    vector<int> intersections;
    for(int i = 0; i < arr1.size(); ++i){
        ++mp[arr1[i]];
    }
    for(int j = 0; j < arr2.size(); ++j){
        if(mp[arr2[j]] > 0){
            intersections.push_back(arr2[j]);
            --mp[arr2[j]];
        }
    }
    return intersections;
}