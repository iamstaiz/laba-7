#pragma once
#include <iostream>
using namespace std;
#include "memory"

template<typename T>
struct Node2 {
    T data;
    shared_ptr<Node2<T>> next;
    shared_ptr<Node2<T>> prev;
};

template<typename T>
class DoubleList {
private:
    shared_ptr<Node2<T>> head;
    shared_ptr<Node2<T>> tail;
    size_t size;

    shared_ptr<Node2<T>> getNode(size_t index) const;

public:
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}

    void pushBack(const T& value);
    void pushFront(const T& value);

    void popBack();
    void popFront();

    void insertAt(size_t index, const T& value);
    void removeAt(size_t index);
};

template<typename T>
void DoubleList<T>::pushBack(const T& value) {
    unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
    if (tail != nullptr) {
        tail->next = move(newNode);
        tail = tail->next;
    }
    else {
        head = move(newNode);
        tail = head;
    }
    size++;
}

template<typename T>
void DoubleList<T>::pushFront(const T& value) {
    unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = move(newNode);
    }
    else {
        tail = move(newNode);
    }
    head = newNode->prev;
    size++;
}

template<typename T>
void DoubleList<T>::popBack() {
    if (tail == nullptr)
        throw std::out_of_range("List is empty");
    if (head == tail) {
        head.reset();
    }
    else {
        tail->prev->next.reset();
    }
    tail = tail->prev;
    size--;
}

template<typename T>
void DoubleList<T>::popFront() {
    if (head == nullptr)
        throw out_of_range("List is empty");
    if (head == tail) {
        tail.reset();
    }
    else {
        head->next->prev.reset();
    }
    head = head->next;
    size--;

}

template<typename T>
void DoubleList<T>::insertAt(size_t index, const T& value) {
    if (index > size)
        throw out_of_range("Index out of range");
    if (index == 0) {
        pushFront(value);
    }
    else if (index == size) {
        pushBack(value);
    }
    else {
        shared_ptr<Node2<T>> current = getNode(index);
        unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
        newNode->data = value;
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next.reset(newNode.release());
        current->prev = current->prev->next;
        size++;
    }
}

template<typename T>
void DoubleList<T>::removeAt(size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        popFront();
    }
    else if (index == size - 1) {
        popBack();
    }
    else {
        shared_ptr<Node2<T>> current = getNode(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        size--;
    }
}