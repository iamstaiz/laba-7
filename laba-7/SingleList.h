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


};