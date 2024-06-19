#include "PriorityQueueHeap.h"
using namespace std;

#ifndef TEST
int main() {
    PriorityQueueHeap<int> pq;

    pq.pq_insert(1);
    pq.pq_insert(2);
    pq.pq_insert(0);
    pq.pq_delete();
    for(int i = 0; i < pq.pq_size(); ++i){
        cout << pq.get(i) << endl;
    }
    return 0;
}
#endif