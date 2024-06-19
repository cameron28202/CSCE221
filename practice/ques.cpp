#include <iostream>
# include <vector>

using namespace std;
// Question:
// --------------------------------------------------------------------------------------------
// Node class for the individual nodes
class Node {
public:
    int data;
    Node* next;

    // Constructor for Node class
    Node(int data) : data(data), next(nullptr) {}
};

// Manager class to link the nodes and manage the overall list
class LinkedList {
public:
    Node* head;

    // Constructor for LinkedList class
    LinkedList() : head(nullptr) {}

    // Push: Adds a new element at the head of the list
    void push(int data) {
        if (head == nullptr) {
            head = new Node(data);
        } else {
            Node* new_node = new Node(data);
            new_node->next = head;
            head = new_node;
        }
    }

    // Pop: Deletes the element at the front and returns the value of it
    int pop() {
        if (head == nullptr) {
            return -1; // You can return an appropriate value for an empty list
        } else {
            int popped = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
            return popped;
        }
    }

    // Returns the size of the linked list
    int size() {
        Node* temp = head;
        int count = 0;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Function to insert a node containing data at some specified position between 1 and x
    void insert(int data, int position) {
        if(position < 1){
            push(data);
        }
        else if(position > size() + 1){
            position = size() + 1;
        }
        else{
            Node* curr = head;
            int count = 1;
            while(count != position-1 && curr->next != nullptr){
                curr = curr->next;
                ++count;
            }
            Node* new_node = new Node(data);
            new_node->next = curr->next;
            curr->next = new_node;
        }
    }

    // Function to delete a node at the specified position between 1 and x
    void remove(int position) {
        if(position < 1){
            pop();
        }
        else if(position > size()){
            position = size();
        }
        else{
            Node* curr = head;
            int count = 1;
            while(count != position-1){
                curr = curr->next;
                ++count;
            }
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
    }

    // Return the element at the top of the linked list without removing it
    int top() {
        if (head == nullptr) {
            return -1; // You can return an appropriate value for an empty list
        } else {
            return head->data;
        }
    }

    // Return true if the linked list is empty, false if not
    bool isEmpty() {
        return head == nullptr;
    }

   
    void printList() {
        Node* temp = head;
        std::cout << "\nThe linked list is as follows: \n";
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

int testInsertPositionInsideRange(LinkedList& myLinkedList) {
    myLinkedList.insert(9, 1);
    myLinkedList.insert(5, 3);

    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected {9, 3, 5, 2, 1};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 15;
}

int testInsertPositionAboveRange(LinkedList& myLinkedList) {
    myLinkedList.insert(4, 4);
    myLinkedList.insert(8, 7);

    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected{3, 2, 1, 4, 8};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 5;
}

int testInsertPositionBelowRange(LinkedList& myLinkedList) {
    myLinkedList.insert(12, 0);
    myLinkedList.insert(11, -5);

    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected{11, 12, 3, 2, 1};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 5;
}

int testRemovePositionInsideRange(LinkedList& myLinkedList) {
    myLinkedList.remove(2);
    myLinkedList.remove(3);
    myLinkedList.remove(1);
    
    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected{2};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 15;
}

int testRemovePositionAboveRange(LinkedList& myLinkedList) {
    myLinkedList.remove(5);
    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected{3, 2};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 5;
}

int testRemovePositionBelowRange(LinkedList& myLinkedList) {
    myLinkedList.remove(0);
    myLinkedList.remove(-8);
    myLinkedList.printList();
    Node* curr = myLinkedList.head;
    vector<int> expected{1};
    int index = 0;
    while (curr != nullptr) {
        if (curr->data != expected[index]) {
            return 0;
        }
        index++;
        curr = curr->next;
    }

    if (index != expected.size()) {
        return 0;
    }

    return 5;
}



int main() {
    int finalScore = 0;
    try {
        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 

            finalScore += testInsertPositionInsideRange(myLinkedList);
        }

        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 

            finalScore += testInsertPositionAboveRange(myLinkedList);
        }

        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 

            finalScore += testInsertPositionBelowRange(myLinkedList);
        }
        
        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 
            myLinkedList.push(4); // 4 3 2 1 

            finalScore += testRemovePositionInsideRange(myLinkedList);
        }

        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 

            finalScore += testRemovePositionAboveRange(myLinkedList);
        }

        {
            LinkedList myLinkedList;
            myLinkedList.push(1); // 1
            myLinkedList.push(2); // 2 1
            myLinkedList.push(3); // 3 2 1 

            finalScore += testRemovePositionBelowRange(myLinkedList);
        }
    } catch(const exception& e) {
        cout << "An exception occured: " << e.what() << endl;
    }

    cout << endl;
    cout << "Your final score is: " << finalScore << " / 50" << endl;


    return 0;
}