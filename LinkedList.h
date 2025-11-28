#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head = nullptr;

public:
    LinkedList() = default;
    ~LinkedList();

    // Очистка списка
    void clear();
    void LinkedList::clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    LinkedList::~LinkedList() {
        clear();
    }
};