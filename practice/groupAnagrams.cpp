#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


void bubbleSort(std::string &s) {
    bool swapped;
    int n = s.length();
    do {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (s[i - 1] > s[i]) {
                // Swap the characters
                std::swap(s[i - 1], s[i]);
                swapped = true;
            }
        }
        // Reduce n by 1 on each pass, as the last i elements are already sorted
        --n;
    } while (swapped);
}

unordered_map<string, vector<string>> groupAnagrams(vector<string> words){
    
    unordered_map<string, vector<string>> mp;
    for(int i = 0; i < words.size(); ++i){
        string word = words.at(i);
        bubbleSort(word);
        mp[word].push_back(words.at(i));

    }
    return mp;

}

int main(){

}