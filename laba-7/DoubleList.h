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