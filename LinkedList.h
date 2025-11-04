//
// Circular, Templated Linked List
//
#ifndef CIRCULAR_TEMPLATED_LIST_H
#define CIRCULAR_TEMPLATED_LIST_H

#include <iostream>
using namespace std;

/* ---------- Node (templated) ---------- */
template <typename T>
struct Node {
    T   data;
    Node next;
    explicit Node(T newData) : data(newData), next(nullptr) {}
};

/* ---------- LinkedList (templated, singly-linked CIRCULAR) ---------- */
template <typename T>
class LinkedList {
private:
    Node<T>* head;     // nullptr if empty
    Node<T>* tail;     // when non-empty: tail->next == head
    Node<T>* current;  // for playNext()

public:
    LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    ~LinkedList() {
        if (!head) return;           // empty list
        // Walk exactly once around the circle
        Node<T>* cur = head->next;
        while (cur != head) {
            Node<T>* nxt = cur->next;
            delete cur->data;        // requires virtual dtor on base type
            delete cur;
            cur = nxt;
        }
        delete head->data;
        delete head;
        head = tail = current = nullptr;
        cout << "\n[Playlist cleanup complete. All memory deallocated.]\n";
    }

    // Insert at END; keep circular invariant tail->next == head
    void insert(T newItem) {
        Node<T>* n = new Node<T>(newItem);
        if (!head) {
            head = tail = n;
            tail->next = head;       // first link closes the circle
            current = head;
        } else {
            tail->next = n;          // old tail -> new node
            tail = n;                // advance tail
            tail->next = head;       // close circle
        }
    }

    // Display items once around (stop when we return to head)
    void displayList() const {
        if (!head) { cout << "\n[Playlist is empty.]\n"; return; }
        cout << "\n-- Playlist --\n";
        const Node<T>* cur = head;
        int idx = 1;
        do {
            cout << idx++ << " - " << cur->data->toString() << '\n';
            cur = cur->next;
        } while (cur != head);
        cout << "--------------\n";
    }

    // Play current (or head if unset)
    void playCurrent() const {
        if (!head) { cout << "[Playlist is empty. Nothing to play.]\n"; return; }
        (current ? current : head)->data->play();
    }

    // Advance one step and play (wraps automatically)
    T playNext() {
    if (!current)
        current = head;
    else
        current = current->next;

    return current->data;
        
    }
};

#endif // CIRCULAR_TEMPLATED_LIST_H
