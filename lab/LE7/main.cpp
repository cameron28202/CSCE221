#include "skiplist.h"

int main() {
    int maxLevel = 10;
    double probability = 0.5;
    SkipList skipList(maxLevel, probability);

    int n = 20;
    srand(time(0));
    vector<int> v;

    for (int i = 0; i < n; i++) {
        int r = rand() % 10;
        if (r < 4) { // insert 
            int x = rand() % 1000000;
            skipList.insertElement(x);
            v.push_back(x);
            
            bool found = skipList.searchElement(x);
            if (found == false) {
                cout << "failed test at first check";
            }
        } else if (r < 8) { // search
            if (v.size() > 0) {
                int r = rand() % v.size();
                bool found = skipList.searchElement(v[r]);
                if (found == false) {
                    cout << "failed test at second check";
                }
            }
        }
    }
    skipList.displayList();
}