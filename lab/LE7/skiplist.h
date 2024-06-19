#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Node {
public:
    int key;
    std::vector<Node*> forward;
    Node(int key, int level) : key(key), forward(level + 1, nullptr) {}
};

class SkipList {
private: 
    double P; 
    int MAXLVL;
    Node* header;
    int level;

public:
    SkipList(int max_lvl, double p);
    ~SkipList();
    int randomLevel();
    void insertElement(int key);
    void deleteElement(int search_key);
    bool searchElement(int key);
    void displayList();
};


SkipList::SkipList(int max_lvl, double p) : MAXLVL(max_lvl), P(p), level(0) {
    header = new Node(-1, MAXLVL);
}

SkipList::~SkipList() {
   Node* current = header;
   while(current != nullptr){
        Node* temp = current;
        current = current->forward[0];
        delete temp;
   }

} 

int SkipList::randomLevel() {
    double num = static_cast<double>(rand()) / RAND_MAX;
    int levels = 0;
    while(num < P && levels < MAXLVL){
        ++levels;
        num = static_cast<double>(rand()) / RAND_MAX;
    }
    return levels;

}

void SkipList::insertElement(int key){
    std::vector<Node*> prev(MAXLVL + 1, header);
    Node* curr = header;
    int curr_lv = level;
    while(curr_lv >= 0){
        while(curr->forward[curr_lv] != nullptr && curr->forward[curr_lv]->key < key){
            curr = curr->forward[curr_lv];
        }
        prev[curr_lv] = curr;
        --curr_lv;
    }

    if(curr->forward[0] == nullptr || curr->forward[0]->key != key){
        int randLevel = randomLevel();
        if (randLevel > level) {
            level = randLevel;
        }
        Node* toInsert = new Node(key, randLevel);
        for(int i = 0; i <= randLevel; ++i){
            toInsert->forward[i] = prev[i]->forward[i];
            prev[i]->forward[i] = toInsert;
        }
    }
}

void SkipList::deleteElement(int search_key) {
    std::vector<Node*> prev(MAXLVL + 1);
    Node* curr = header;
    int curr_lv = level;
    while(curr_lv >= 0){
        while(curr->forward[curr_lv] != nullptr && curr->forward[curr_lv]->key < search_key){
            curr = curr->forward[curr_lv];
        }
        prev[curr_lv] = curr;
        --curr_lv;
    }

    curr = curr->forward[0];
    if(curr != nullptr && curr->key == search_key){
        for(int i = 0; i <= level; ++i){
            if(prev[i]->forward[i] != curr){
                break;
            }
            else{
                prev[i]->forward[i] = curr->forward[i];
            }
            //delete curr;
        }

        while(level > 0 && header->forward[level] == nullptr){
            --level;
        }

        delete curr;
    }

    // while(level > 0 && header->forward[level] == nullptr){
    //     --level;
    // }
}

bool SkipList::searchElement(int key) {
    Node* curr = header;
    int curr_lv = level;
    while(curr_lv >= 0){
        while(curr->forward[curr_lv] != nullptr && curr->forward[curr_lv]->key < key){
            curr = curr->forward[curr_lv];
        }
        --curr_lv;
    }
    curr = curr->forward[0];
    if(curr != nullptr && curr->key == key){
        return true;
    }

    return false;
}

void SkipList::displayList() {
    std::cout << "\n*****Skip List******" << std::endl;
    Node* head = header;
    for (int lvl = 0; lvl <= level; lvl++) {
        std::cout << "Level " << lvl << ": ";
        Node* node = head->forward[lvl];
        while (node != nullptr) {
            std::cout << node->key << " ";
            node = node->forward[lvl];
        }
        std::cout << std::endl;
    }
}

#endif