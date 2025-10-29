#pragma once
#pragma once
#include "Stack.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <cmath>

class Calculator {
public:
    // 静态方法：计算表达式（支持+、-、*、/、()）
    static double evaluate(const std::string& expr) {
        Stack<double> numStack;  // 数字栈
        Stack<char> opStack;    // 运算符栈
        std::string trimmedExpr;

        // 1. 去除表达式空格
        for (char c : expr) {
            if (c != ' ') trimmedExpr += c;
        }
        int n = trimmedExpr.size();

        // 2. 优先级表（参考示例代码）
        auto getPriority = [](char op) -> int {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            if (op == '(') return 0;
            if (op == ')') return -1;
            throw std::invalid_argument("未知运算符: " + std::string(1, op));
            };

        // 3. 处理表达式
        for (int i = 0; i < n; ++i) {
            char c = trimmedExpr[i];
            // 3.1 处理数字（含负号、小数）
            if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || trimmedExpr[i - 1] == '('))) {
                int j = i;
                if (c == '-') j++; // 负号跳过
                while (j < n && (isdigit(trimmedExpr[j]) || trimmedExpr[j] == '.')) j++;
                std::string numStr = trimmedExpr.substr(i, j - i);
                numStack.push(std::stod(numStr));
                i = j - 1; // 更新i，跳过已处理数字
            }
            // 3.2 处理左括号
            else if (c == '(') {
                opStack.push(c);
            }
            // 3.3 处理右括号：计算到左括号
            else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    calculate(numStack, opStack);
                }
                if (opStack.empty()) throw std::invalid_argument("括号不匹配");
                opStack.pop(); // 弹出左括号
            }
            // 3.4 处理运算符：按优先级计算
            else {
                while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(c)) {
                    calculate(numStack, opStack);
                }
                opStack.push(c);
            }
        }

        // 4. 处理剩余运算符
        while (!opStack.empty()) {
            calculate(numStack, opStack);
        }

        // 5. 结果校验
        if (numStack.size() != 1) throw std::invalid_argument("表达式无效");
        return numStack.top();
    }

private:
    // 辅助函数：弹出两个数和一个运算符，计算后压栈
    static void calculate(Stack<double>& numStack, Stack<char>& opStack) {
        if (numStack.size() < 2 || opStack.empty()) {
            throw std::invalid_argument("表达式格式错误");
        }
        double b = numStack.top(); numStack.pop();
        double a = numStack.top(); numStack.pop();
        char op = opStack.top(); opStack.pop();
        double res = 0.0;

        switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/':
            if (fabs(b) < 1e-6) throw std::invalid_argument("除数为0");
            res = a / b;
            break;
        default: throw std::invalid_argument("未知运算符: " + std::string(1, op));
        }
        numStack.push(res);
    }
};