#include <iostream>
#include "deque.h"
using namespace std;

int main() {
    {
        Deque<int> q;
        q.insertFirst(8);
        q.insertFirst(3);
        q.insertFirst(2);

        Deque<int> p;
        p.insertFirst(8);
        p.insertFirst(3);
        p.insertFirst(2);
        //cout << p.get(1);
    }
    return 0;
}