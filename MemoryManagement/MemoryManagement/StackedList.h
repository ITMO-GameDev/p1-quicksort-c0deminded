#pragma once
template <class T>
class StackedList {
public:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
public:
    StackedList() = default;
    StackedList(StackedList & stackLinkedList) = delete;
    void push(Node * newNode);
    Node* pop();
};

