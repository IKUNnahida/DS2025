#pragma once
#pragma once
#include "Stack.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <cmath>

class Calculator {
public:
    // ��̬������������ʽ��֧��+��-��*��/��()��
    static double evaluate(const std::string& expr) {
        Stack<double> numStack;  // ����ջ
        Stack<char> opStack;    // �����ջ
        std::string trimmedExpr;

        // 1. ȥ�����ʽ�ո�
        for (char c : expr) {
            if (c != ' ') trimmedExpr += c;
        }
        int n = trimmedExpr.size();

        // 2. ���ȼ����ο�ʾ�����룩
        auto getPriority = [](char op) -> int {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            if (op == '(') return 0;
            if (op == ')') return -1;
            throw std::invalid_argument("δ֪�����: " + std::string(1, op));
            };

        // 3. ������ʽ
        for (int i = 0; i < n; ++i) {
            char c = trimmedExpr[i];
            // 3.1 �������֣������š�С����
            if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || trimmedExpr[i - 1] == '('))) {
                int j = i;
                if (c == '-') j++; // ��������
                while (j < n && (isdigit(trimmedExpr[j]) || trimmedExpr[j] == '.')) j++;
                std::string numStr = trimmedExpr.substr(i, j - i);
                numStack.push(std::stod(numStr));
                i = j - 1; // ����i�������Ѵ�������
            }
            // 3.2 ����������
            else if (c == '(') {
                opStack.push(c);
            }
            // 3.3 ���������ţ����㵽������
            else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    calculate(numStack, opStack);
                }
                if (opStack.empty()) throw std::invalid_argument("���Ų�ƥ��");
                opStack.pop(); // ����������
            }
            // 3.4 ����������������ȼ�����
            else {
                while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(c)) {
                    calculate(numStack, opStack);
                }
                opStack.push(c);
            }
        }

        // 4. ����ʣ�������
        while (!opStack.empty()) {
            calculate(numStack, opStack);
        }

        // 5. ���У��
        if (numStack.size() != 1) throw std::invalid_argument("���ʽ��Ч");
        return numStack.top();
    }

private:
    // ����������������������һ��������������ѹջ
    static void calculate(Stack<double>& numStack, Stack<char>& opStack) {
        if (numStack.size() < 2 || opStack.empty()) {
            throw std::invalid_argument("���ʽ��ʽ����");
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
            if (fabs(b) < 1e-6) throw std::invalid_argument("����Ϊ0");
            res = a / b;
            break;
        default: throw std::invalid_argument("δ֪�����: " + std::string(1, op));
        }
        numStack.push(res);
    }
};