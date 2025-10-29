#pragma once
#include "MyVector.h"

template <typename T>
class Stack {
private:
    Vector<T> _vec; // µ×²ãÓÃMyVector´æ´¢
public:
    void push(const T& val) { _vec.insert(val); }
    void pop() { if (!empty()) _vec.remove(_vec.size() - 1); }
    T& top() { if (empty()) throw std::runtime_error("Stack is empty!"); return _vec[_vec.size() - 1]; }
    bool empty() const { return _vec.empty(); }
    int size() const { return _vec.size(); }
};