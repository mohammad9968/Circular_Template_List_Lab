//
//
//

#ifndef CIRCULAR_TEMPLATED_LIST_H
#define CIRCULAR_TEMPLATED_LIST_H

#include <iostream>
using namespace std;

// =====================
// Node (Templated)
// =====================
template <typename T>
struct Node {
    T* data;
    Node* next;

    explicit Node(T* newData) : data(newData), next(nullptr) {}
};

// =====================
// LinkedList (Templated, NOT circular yet)
// =====================
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node<T>* current = head;
        while(current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current->data;     // polymorphic delete
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Insert at end (forward only for now)
    void insert(T* newItem) {
        Node<T>* newNode = new Node<T>(newItem);
        if(head == nullptr) {
            head = newNode;
        } else {
            Node<T>* cur = head;
            while(cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
    }

    // Display contents
    void displayList() const {
        if(head == nullptr) {
            cout << "\n[Playlist is empty.]\n";
            return;
        }

        cout << "\n-- Playlist --\n";
        Node<T>* cur = head;
        int idx = 1;

        while(cur != nullptr) {
            cout << idx++ << ". " << cur->data->toString() << endl;
            cur = cur->next;
        }
    }

    // Play the FIRST item only (this will change later)
    void playCurrent() const {
        if(head != nullptr) {
            head->data->play();
        } else {
            cout << "[Playlist empty]\n";
        }
    }
};

#endif
