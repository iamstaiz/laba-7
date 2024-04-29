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