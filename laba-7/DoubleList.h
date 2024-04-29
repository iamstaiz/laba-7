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
};
