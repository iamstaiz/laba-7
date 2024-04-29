#pragma once
#include <iostream>
using namespace std;
#include "memory"

template<typename T>
struct Node {
    T data;
    shared_ptr<Node<T>> next;

    Node(const T& value) : data(value), next(nullptr) {}

};

template<typename T>
class SingleList {
private:
    shared_ptr<Node<T>> head;
    size_t size;
public:

    SingleList() :head(nullptr), size(0) {}

    void pushFront(const T& value);
    void pushBack(const T& value);

    void popFront();
    void popBack();

    T& operator[](size_t index)const;

    void insertAt(size_t index, const T& value);
    void removeAt(size_t index);

    bool isEmpty() const;
    size_t Size() const;

    bool Find(const T& value)const;

    // friend operators
    friend ostream& operator<<(ostream& os, const SingleList<T> list) {
        shared_ptr<Node<T>> current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};

template<typename T>
void SingleList<T>::pushBack(const T& value) {
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(value);
    if (head == nullptr) {
        head = move(newNode);
    }
    else {
        shared_ptr<Node<T>> current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = move(newNode);
    }
    size++;
}

template<typename T>
void SingleList<T>::pushFront(const T& value) {
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(value);
    newNode->next = move(head);
    head = move(newNode);
    size++;
}

template<typename T>
void SingleList<T>::popBack() {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    if (head->next == nullptr) {
        head.reset();
    }
    else {
        shared_ptr<Node<T>> current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        current->next.reset();
    }
    size--;
}

template<typename T>
void SingleList<T>::popFront() {
    if (head == nullptr)
        throw out_of_range("List is empty");
    head = move(head->next);
    size--;
}

template<typename T>
T& SingleList<T>::operator[](size_t index) const {
    if (index >= size)
        throw out_of_range("Index out of range");
    shared_ptr<Node<T>> current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
void SingleList<T>::insertAt(size_t index, const T& value) {
    if (index > size)
        throw out_of_range("Index out of range");
    if (index == 0) {
        pushFront(value);
    }
    else {
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(value);
        shared_ptr<Node<T>> current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template<typename T>
void SingleList<T>::removeAt(size_t index) {
    if (index >= size)
        throw out_of_range("Index out of range");
    if (index == 0) {
        popFront();
    }
    else {
        shared_ptr<Node<T>> current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        current->next = current->next->next;
        size--;
    }
}

template<typename T>
size_t SingleList<T>::Size() const {
    return size;
}

template<typename T>
bool SingleList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
bool SingleList<T>::Find(const T& value) const {
    shared_ptr<Node<T>> current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}