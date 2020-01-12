#include "StackedList.h"
template <class T>
void StackedList<T>::push(Node* newNode) {
    newNode->next = head;
    head = newNode;
}

template <class T>
typename StackedList<T>::Node* StackedList<T>::pop() {
    Node* top = head;
    head = head->next;
    return top;
}