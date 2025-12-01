#pragma once

#include <iostream>
#include <stdexcept>
#include <random>
#include <type_traits>

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
    // Доступ по индексу (для чтения и записи)
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    // Копирование и присваивание
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    // Удаление всех узлов с заданным значением
    void delete_node(const T& value);
    // Добавление другого списка в конец/начало
    void push_tail(const LinkedList& other);
    void push_head(const LinkedList& other);
    // Заполнение списка случайными значениями
    explicit LinkedList(size_t count, const T& min_val = T(), const T& max_val = T());
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

template<typename T>
T& LinkedList<T>::operator[](size_t index) {
    Node<T>* curr = head;
    for (size_t i = 0; i < index; ++i) {
        if (curr == nullptr)
            throw std::out_of_range("operator[]: index out of range");
        curr = curr->next;
    }
    if (curr == nullptr)
        throw std::out_of_range("operator[]: index out of range");
    return curr->data;
}

template<typename T>
const T& LinkedList<T>::operator[](size_t index) const {
    Node<T>* curr = head;
    for (size_t i = 0; i < index; ++i) {
        if (curr == nullptr)
            throw std::out_of_range("operator[] const: index out of range");
        curr = curr->next;
    }
    if (curr == nullptr)
        throw std::out_of_range("operator[] const: index out of range");
    return curr->data;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr) {
    Node<T>* curr = other.head;
    while (curr != nullptr) {
        push_tail(curr->data);
        curr = curr->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this == &other) return *this;
    clear();
    Node<T>* curr = other.head;
    while (curr != nullptr) {
        push_tail(curr->data);
        curr = curr->next;
    }
    return *this;
}

template<typename T>
void LinkedList<T>::delete_node(const T& value) {
    // Удаляем с головы, пока совпадает
    while (head != nullptr && head->data == value) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // Удаляем в середине/хвосте
    Node<T>* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->next->data == value) {
            Node<T>* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
        else {
            curr = curr->next;
        }
    }
}

template<typename T>
void LinkedList<T>::push_tail(const LinkedList& other) {
    Node<T>* curr = other.head;
    while (curr != nullptr) {
        push_tail(curr->data);
        curr = curr->next;
    }
}

template<typename T>
void LinkedList<T>::push_head(const LinkedList& other) {
    // Самый элегантный способ: копируем и разворачиваем вручную
    Node<T>* prev = nullptr;
    Node<T>* curr = other.head;

    while (curr != nullptr) {
        Node<T>* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // prev — это теперь голова развёрнутого списка
    if (prev != nullptr) {
        Node<T>* tail_of_reversed = prev;
        while (tail_of_reversed->next != nullptr) {
            tail_of_reversed = tail_of_reversed->next;
        }
        tail_of_reversed->next = head;
        head = prev;
    }
}

template<typename T>
LinkedList<T>::LinkedList(size_t count, const T& min_val, const T& max_val) : head(nullptr) {
    if (count == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min_val, max_val);
        for (size_t i = 0; i < count; ++i) {
            push_tail(dist(gen));
        }
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        for (size_t i = 0; i < count; ++i) {
            push_tail(dist(gen));
        }
    }
    else {
        // Для всех остальных типов — просто копируем min_val
        for (size_t i = 0; i < count; ++i) {
            push_tail(min_val);
        }
    }
}
