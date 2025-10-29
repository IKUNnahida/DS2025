//#include "MyVector.h"
//#include <iostream>
//#include <ctime>
//
//// 遍历用的函数指针（打印元素）
//void printInt(int& e) {
//    std::cout << e << " ";
//}
//
//int main() {
//    srand((unsigned int)time(nullptr)); // 初始化随机种子
//
//    // 1. 用原构造函数创建向量
//    int arr[] = { 5, 2, 8, 1 };
//    Vector<int> vec1(arr, 4); // 数组整体复制
//    Vector<int> vec2(vec1, 1, 3); // 向量区间复制
//
//    // 2. 调用原接口：插入、排序、遍历
//    vec1.insert(2, 6); // 插入元素6到秩2
//    vec1.sort(); // 整体排序
//    std::cout << "vec1排序后：";
//    vec1.traverse(printInt);
//    std::cout << "\n";
//
//    // 3. 调用原接口：查找、删除、去重
//    Rank pos = vec1.find(6); // 查找元素6
//    std::cout << "元素6的位置：" << pos << "\n";
//    vec1.remove(3); // 删除秩3的元素
//    vec1.dedup(); // 无序去重（此处无重复，仅演示）
//
//    // 4. 调用原接口：select（查找第2大元素，0开始计数）
//    Rank k = 2;
//    Rank kPos = vec1.select(k);
//    std::cout << "第" << k << "大元素：" << vec1[kPos] << "\n";
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

// 任务1：复数向量测试（参考示例代码）
void task1() {
    cout << "=== 任务1：复数向量测试 ===" << endl;

    // 创建无序复数向量（含重复项）
    Vector<Complex> vec;
    srand(static_cast<unsigned int>(time(NULL)));

    // 随机生成10个复数
    for (int i = 0; i < 10; i++) {
        double real = rand() % 10;  // 实部0~9
        double imag = rand() % 10;  // 虚部0~9
        vec.insert(Complex(real, imag));
    }

    cout << "原始向量: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (1) 测试置乱
    vec.unsort();
    cout << "置乱后: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (1) 测试查找
    Complex searchTarget(3, 4);
    Rank pos = vec.find(searchTarget);
    if (pos != static_cast<Rank>(-1)) { // 匹配unsigned类型
        cout << "找到 " << searchTarget << " 在位置 " << pos << endl;
    }
    else {
        cout << "未找到 " << searchTarget << endl;
    }

    // (1) 测试插入
    vec.insert(Complex(7, 8));
    cout << "插入 " << Complex(7, 8) << " 后大小: " << vec.size() << endl;

    // (1) 测试删除
    if (vec.size() > 0) {
        Complex delVal = vec.remove(0);
        cout << "删除第一个元素 " << delVal << " 后大小: " << vec.size() << endl;
    }

    // (1) 测试唯一化（先排序）
    vec.sort(); // 归并排序
    cout << "排序后向量: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    int removed = vec.uniquify();
    cout << "唯一化后删除重复元素: " << removed << " 个" << endl;
    cout << "唯一化后向量: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // (2) 比较排序效率（起泡vs归并）
    cout << "\n=== 排序效率比较（数据量：1000个复数） ===" << endl;
    const int TEST_SIZE = 1000;

    // 构造顺序、逆序、乱序向量
    Vector<Complex> ordered, reversed, random;
    for (int i = 0; i < TEST_SIZE; i++) {
        ordered.insert(Complex(i, i));                  // 顺序
        reversed.insert(Complex(TEST_SIZE - 1 - i, TEST_SIZE - 1 - i)); // 逆序
        random.insert(Complex(rand() % 100, rand() % 100)); // 乱序
    }

    // 起泡排序效率
    Vector<Complex> bubbleTest = ordered;
    clock_t start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    clock_t end = clock();
    cout << "顺序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    bubbleTest = reversed;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "逆序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    bubbleTest = random;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "乱序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    // 归并排序效率
    Vector<Complex> mergeTest = ordered;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "顺序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    mergeTest = reversed;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "逆序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    mergeTest = random;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "乱序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    // (3) 区间查找（模介于[5, 10)）
    cout << "\n=== 区间查找（模范围：[5.0, 10.0)） ===" << endl;
    Vector<Complex> sortedVec;
    for (int i = 0; i < 20; i++) {
        sortedVec.insert(Complex(rand() % 15, rand() % 15)); // 随机复数
    }
    sortedVec.sort(); // 先排序，确保结果有序

    cout << "有序向量（含模）: ";
    for (int i = 0; i < sortedVec.size(); i++) {
        cout << sortedVec[i] << "(模:" << sortedVec[i].modulus() << ") ";
    }
    cout << endl;

    // 查找模在[5,10)的元素
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> result;
    for (int i = 0; i < sortedVec.size(); i++) {
        double mod = sortedVec[i].modulus();
        if (mod >= m1 && mod < m2) {
            result.insert(sortedVec[i]);
        }
    }

    cout << "模在[" << m1 << ", " << m2 << ")范围内的元素: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

// 任务2：计算器测试（参考示例代码）
void task2() {
    cout << "\n=== 任务2：字符串计算器测试 ===" << endl;

    // 测试用例（支持+、-、*、/、()）
    Vector<string> testCases;
    testCases.insert("2 + 3 * 4");
    testCases.insert("(2 + 3) * 4");
    testCases.insert("10 / 2 - 1");
    testCases.insert("3 * (4 + 5) / 2");
    testCases.insert("10 / (2 - 2)"); // 除数为0（异常）
    testCases.insert("2 + 3 * (4 - 1"); // 括号不匹配（异常）

    for (int i = 0; i < testCases.size(); i++) {
        string expr = testCases[i];
        try {
            double result = Calculator::evaluate(expr);
            cout << expr << " = " << result << endl;
        }
        catch (const exception& e) {
            cout << expr << " -> 错误: " << e.what() << endl;
        }
    }
}

// 任务3：柱状图最大面积（参考示例代码，基于单调栈）
int largestRectangleArea(const Vector<int>& heights) {
    Stack<int> stk; // 存储柱子索引，保持高度递增
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        // 当前高度小于栈顶，计算栈顶柱子的最大面积
        while (!stk.empty() && (i == n || heights[i] < heights[stk.top()])) {
            int height = heights[stk.top()];
            stk.pop();
            // 计算宽度：栈空则宽度为i，否则为i - 新栈顶 - 1
            int width = stk.empty() ? i : (i - stk.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        stk.push(i);
    }
    return maxArea;
}

void task3() {
    cout << "\n=== 任务3：柱状图最大面积测试 ===" << endl;
    srand(static_cast<unsigned int>(time(NULL)));
    const int TEST_CASES = 5; // 5组测试数据

    for (int test = 1; test <= TEST_CASES; test++) {
        int n = rand() % 10 + 5; // 柱子数量：5~14个
        Vector<int> heights;

        cout << "测试" << test << " - " << n << "个柱子高度: ";
        for (int i = 0; i < n; i++) {
            int h = rand() % 20 + 1; // 高度：1~20
            heights.insert(h);
            cout << h << " ";
        }

        int area = largestRectangleArea(heights);
        cout << "-> 最大面积: " << area << endl;
    }

    // 示例用例验证
    Vector<int> example1;
    example1.insert(2); example1.insert(1); example1.insert(5);
    example1.insert(6); example1.insert(2); example1.insert(3);
    cout << "\n示例1（heights=[2,1,5,6,2,3]）-> 最大面积: " << largestRectangleArea(example1) << "（预期10）" << endl;

    Vector<int> example2;
    example2.insert(2); example2.insert(4);
    cout << "示例2（heights=[2,4]）-> 最大面积: " << largestRectangleArea(example2) << "（预期4）" << endl;
}

// 主函数
int main() {
    cout << "C++数据结构学习任务演示" << endl;
    cout << "=========================" << endl;

    task1(); // 复数向量测试
    task2(); // 计算器测试
    task3(); // 柱状图最大面积测试

    return 0;
}