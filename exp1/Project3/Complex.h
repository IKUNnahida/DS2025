#pragma once
#include <cmath>
#include <iostream>

class Complex {
public:
    double _real;
    double _imag;

    // 构造函数
    Complex(double real = 0.0, double imag = 0.0) : _real(real), _imag(imag) {}

    // 计算模（与示例代码的modulus()统一，可根据需求改名）
    double modulus() const {
        return sqrt(_real * _real + _imag * _imag);
    }

    // 成员函数版运算符（无全局版，避免歧义）
    bool operator==(const Complex& other) const {
        return fabs(_real - other._real) < 1e-6 && fabs(_imag - other._imag) < 1e-6;
    }
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    bool operator<(const Complex& other) const {
        if (fabs(this->modulus() - other.modulus()) > 1e-6) {
            return this->modulus() < other.modulus();
        }
        else {
            return _real < other._real;
        }
    }
    bool operator<=(const Complex& other) const {
        return (*this < other) || (*this == other);
    }
    bool operator>(const Complex& other) const {
        if (fabs(this->modulus() - other.modulus()) > 1e-6) {
            return this->modulus() > other.modulus();
        }
        else {
            return _real > other._real;
        }
    }

    // 友元<<运算符，支持打印
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c._real << (c._imag >= 0 ? "+" : "") << c._imag << "i";
        return os;
    }
};