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
    // Добавление элментов
    void push_tail(const T& value);
    void push_head(const T& value);
    // Удаление элементов
    T pop_head();
    T pop_tail();

};
template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}
template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void LinkedList<T>::push_tail(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    if (head == nullptr) {
        head = new_node;
    }
    else {
        Node<T>* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

template<typename T>
void LinkedList<T>::push_head(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
}

template<typename T>
T LinkedList<T>::pop_head() {
    if (head == nullptr)
        throw std::out_of_range("pop_head: list is empty");

    Node<T>* temp = head;
    T value = temp->data;
    head = head->next;
    delete temp;
    return value;
}

template<typename T>
T LinkedList<T>::pop_tail() {
    if (head == nullptr)
        throw std::out_of_range("pop_tail: list is empty");

    if (head->next == nullptr) {
        T value = head->data;
        delete head;
        head = nullptr;
        return value;
    }

    Node<T>* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    T value = curr->next->data;
    delete curr->next;
    curr->next = nullptr;
    return value;
}