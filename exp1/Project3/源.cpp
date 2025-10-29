//#include "MyVector.h"
//#include <iostream>
//#include <ctime>
//
//// �����õĺ���ָ�루��ӡԪ�أ�
//void printInt(int& e) {
//    std::cout << e << " ";
//}
//
//int main() {
//    srand((unsigned int)time(nullptr)); // ��ʼ���������
//
//    // 1. ��ԭ���캯����������
//    int arr[] = { 5, 2, 8, 1 };
//    Vector<int> vec1(arr, 4); // �������帴��
//    Vector<int> vec2(vec1, 1, 3); // �������临��
//
//    // 2. ����ԭ�ӿڣ����롢���򡢱���
//    vec1.insert(2, 6); // ����Ԫ��6����2
//    vec1.sort(); // ��������
//    std::cout << "vec1�����";
//    vec1.traverse(printInt);
//    std::cout << "\n";
//
//    // 3. ����ԭ�ӿڣ����ҡ�ɾ����ȥ��
//    Rank pos = vec1.find(6); // ����Ԫ��6
//    std::cout << "Ԫ��6��λ�ã�" << pos << "\n";
//    vec1.remove(3); // ɾ����3��Ԫ��
//    vec1.dedup(); // ����ȥ�أ��˴����ظ�������ʾ��
//
//    // 4. ����ԭ�ӿڣ�select�����ҵ�2��Ԫ�أ�0��ʼ������
//    Rank k = 2;
//    Rank kPos = vec1.select(k);
//    std::cout << "��" << k << "��Ԫ�أ�" << vec1[kPos] << "\n";
//
//    return 0;
//}

#include "MyVector.h"
#include "Complex.h"
#include "Calculator.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

// ����1�������������ԣ��ο�ʾ�����룩
void task1() {
    cout << "=== ����1�������������� ===" << endl;

    // �������������������ظ��
    Vector<Complex> vec;
    srand(static_cast<unsigned int>(time(NULL)));

    // �������10������
    for (int i = 0; i < 10; i++) {
        double real = rand() % 10;  // ʵ��0~9
        double imag = rand() % 10;  // �鲿0~9
        vec.insert(Complex(real, imag));
    }

    cout << "ԭʼ����: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (1) ��������
    vec.unsort();
    cout << "���Һ�: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (1) ���Բ���
    Complex searchTarget(3, 4);
    Rank pos = vec.find(searchTarget);
    if (pos != static_cast<Rank>(-1)) { // ƥ��unsigned����
        cout << "�ҵ� " << searchTarget << " ��λ�� " << pos << endl;
    }
    else {
        cout << "δ�ҵ� " << searchTarget << endl;
    }

    // (1) ���Բ���
    vec.insert(Complex(7, 8));
    cout << "���� " << Complex(7, 8) << " ���С: " << vec.size() << endl;

    // (1) ����ɾ��
    if (vec.size() > 0) {
        Complex delVal = vec.remove(0);
        cout << "ɾ����һ��Ԫ�� " << delVal << " ���С: " << vec.size() << endl;
    }

    // (1) ����Ψһ����������
    vec.sort(); // �鲢����
    cout << "���������: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    int removed = vec.uniquify();
    cout << "Ψһ����ɾ���ظ�Ԫ��: " << removed << " ��" << endl;
    cout << "Ψһ��������: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (2) �Ƚ�����Ч�ʣ�����vs�鲢��
    cout << "\n=== ����Ч�ʱȽϣ���������1000�������� ===" << endl;
    const int TEST_SIZE = 1000;

    // ����˳��������������
    Vector<Complex> ordered, reversed, random;
    for (int i = 0; i < TEST_SIZE; i++) {
        ordered.insert(Complex(i, i));                  // ˳��
        reversed.insert(Complex(TEST_SIZE - 1 - i, TEST_SIZE - 1 - i)); // ����
        random.insert(Complex(rand() % 100, rand() % 100)); // ����
    }

    // ��������Ч��
    Vector<Complex> bubbleTest = ordered;
    clock_t start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    clock_t end = clock();
    cout << "˳��-��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    bubbleTest = reversed;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "����-��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    bubbleTest = random;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "����-��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    // �鲢����Ч��
    Vector<Complex> mergeTest = ordered;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "˳��-�鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    mergeTest = reversed;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "����-�鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    mergeTest = random;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "����-�鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    // (3) ������ң�ģ����[5, 10)��
    cout << "\n=== ������ң�ģ��Χ��[5.0, 10.0)�� ===" << endl;
    Vector<Complex> sortedVec;
    for (int i = 0; i < 20; i++) {
        sortedVec.insert(Complex(rand() % 15, rand() % 15)); // �������
    }
    sortedVec.sort(); // ������ȷ���������

    cout << "������������ģ��: ";
    for (int i = 0; i < sortedVec.size(); i++) {
        cout << sortedVec[i] << "(ģ:" << sortedVec[i].modulus() << ") ";
    }
    cout << endl;

    // ����ģ��[5,10)��Ԫ��
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> result;
    for (int i = 0; i < sortedVec.size(); i++) {
        double mod = sortedVec[i].modulus();
        if (mod >= m1 && mod < m2) {
            result.insert(sortedVec[i]);
        }
    }

    cout << "ģ��[" << m1 << ", " << m2 << ")��Χ�ڵ�Ԫ��: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

// ����2�����������ԣ��ο�ʾ�����룩
void task2() {
    cout << "\n=== ����2���ַ������������� ===" << endl;

    // ����������֧��+��-��*��/��()��
    Vector<string> testCases;
    testCases.insert("2 + 3 * 4");
    testCases.insert("(2 + 3) * 4");
    testCases.insert("10 / 2 - 1");
    testCases.insert("3 * (4 + 5) / 2");
    testCases.insert("10 / (2 - 2)"); // ����Ϊ0���쳣��
    testCases.insert("2 + 3 * (4 - 1"); // ���Ų�ƥ�䣨�쳣��

    for (int i = 0; i < testCases.size(); i++) {
        string expr = testCases[i];
        try {
            double result = Calculator::evaluate(expr);
            cout << expr << " = " << result << endl;
        }
        catch (const exception& e) {
            cout << expr << " -> ����: " << e.what() << endl;
        }
    }
}

// ����3����״ͼ���������ο�ʾ�����룬���ڵ���ջ��
int largestRectangleArea(const Vector<int>& heights) {
    Stack<int> stk; // �洢�������������ָ߶ȵ���
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        // ��ǰ�߶�С��ջ��������ջ�����ӵ�������
        while (!stk.empty() && (i == n || heights[i] < heights[stk.top()])) {
            int height = heights[stk.top()];
            stk.pop();
            // �����ȣ�ջ������Ϊi������Ϊi - ��ջ�� - 1
            int width = stk.empty() ? i : (i - stk.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        stk.push(i);
    }
    return maxArea;
}

void task3() {
    cout << "\n=== ����3����״ͼ���������� ===" << endl;
    srand(static_cast<unsigned int>(time(NULL)));
    const int TEST_CASES = 5; // 5���������

    for (int test = 1; test <= TEST_CASES; test++) {
        int n = rand() % 10 + 5; // ����������5~14��
        Vector<int> heights;

        cout << "����" << test << " - " << n << "�����Ӹ߶�: ";
        for (int i = 0; i < n; i++) {
            int h = rand() % 20 + 1; // �߶ȣ�1~20
            heights.insert(h);
            cout << h << " ";
        }

        int area = largestRectangleArea(heights);
        cout << "-> ������: " << area << endl;
    }

    // ʾ��������֤
    Vector<int> example1;
    example1.insert(2); example1.insert(1); example1.insert(5);
    example1.insert(6); example1.insert(2); example1.insert(3);
    cout << "\nʾ��1��heights=[2,1,5,6,2,3]��-> ������: " << largestRectangleArea(example1) << "��Ԥ��10��" << endl;

    Vector<int> example2;
    example2.insert(2); example2.insert(4);
    cout << "ʾ��2��heights=[2,4]��-> ������: " << largestRectangleArea(example2) << "��Ԥ��4��" << endl;
}

// ������
int main() {
    cout << "C++���ݽṹѧϰ������ʾ" << endl;
    cout << "=========================" << endl;

    task1(); // ������������
    task2(); // ����������
    task3(); // ��״ͼ����������

    return 0;
}