//using Rank = unsigned int; //秩
//#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）
//
//template <typename T> class Vector { //向量模板类
//protected:
//   Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
//   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
//   void expand(); //空间不足时扩容
//   void shrink(); //装填因子过小时压缩
//   bool bubble ( Rank lo, Rank hi ); //扫描交换
//   void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
//   Rank maxItem ( Rank lo, Rank hi ); //选取最大元素
//   void selectionSort ( Rank lo, Rank hi ); //选择排序算法
//   void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
//   void mergeSort ( Rank lo, Rank hi ); //归并排序算法
//   void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
//   Rank partition ( Rank lo, Rank hi ); //轴点构造算法
//   void quickSort ( Rank lo, Rank hi ); //快速排序算法
//   void shellSort ( Rank lo, Rank hi ); //希尔排序算法
//public:
//// 构造方法
//   Vector ( Rank c = DEFAULT_CAPACITY ) //容量为c的空向量
//   { _elem = new T[_capacity = c]; _size = 0; }
//   Vector ( Rank c, Rank s, T v ) //容量为c、规模为s、所有元素初始为v；s<=c
//   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
//   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
//   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
//   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
//   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
//// 析构方法
//   ~Vector() { delete [] _elem; } //释放内部空间
//// 只读访问接口
//   Rank size() const { return _size; } //规模
//   bool empty() const { return !_size; } //判空
//   Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
//   Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
//   Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //从无序向量中找到第k大的元素
//   Rank search( T const& e ) const //有序向量整体查找
//   { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
//   Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
//// 可写访问接口
//   T& operator[] ( Rank r ); //重载下标操作符，可以类似于数组形式引用各元素
//   const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本
//   Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
//   T remove ( Rank r ); //删除秩为r的元素
//   Rank remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
//   Rank insert ( Rank r, T const& e ); //插入元素
//   Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
//   void sort ( Rank lo, Rank hi ); //对[lo, hi)排序
//   void sort() { sort ( 0, _size ); } //整体排序
//   void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
//   void unsort() { unsort ( 0, _size ); } //整体置乱
//   Rank dedup(); //无序去重
//   Rank uniquify(); //有序去重
//// 遍历
//   void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
//   template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
//}; //Vector
//
//
//template <typename T> //T为基本类型，或已重载赋值操作符'='
//void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //以数组区间A[lo, hi)为蓝本复制向量
//    _elem = new T[_capacity = max<Rank>(DEFAULT_CAPACITY, (hi - lo) * 2)]; //分配空间
//    for (_size = 0; lo < hi; _size++, lo++) //A[lo, hi)内的元素逐一
//        _elem[_size] = A[lo]; //复制至_elem[0, hi-lo)：T为基本类型，或已重载赋值操作符'='
//} //用const修饰，保证A中的元素不致被篡改；运行时间 = O(hi-lo)
//
//
//template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //深复制
//    if (_elem) delete[] _elem; //释放原有内容
//    copyFrom(V._elem, 0, V.size()); //整体复制
//    return *this; //返回当前对象的引用，以便链式赋值
//}
//
//
//template <typename T> void Vector<T>::expand() { //向量空间不足时扩容
//    if (_size < _capacity) return; //尚未满员时，不必扩容
//    T* oldElem = _elem; copyFrom(oldElem, 0, _capacity); //容量加倍
//    /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
//    delete[] oldElem; //释放原空间
//}
//
//
//template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占空间
//    if (_capacity < DEFAULT_CAPACITY << 1) return; //不致收缩到DEFAULT_CAPACITY以下
//    if (_size << 2 > _capacity) return; //以25%为界
//    T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半
//    for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
//    delete[] oldElem; //释放原空间
//}
//
//
//template <typename T> T& Vector<T>::operator[] (Rank r) //重载下标操作符
//{
//    return _elem[r];
//} // assert: 0 <= r < _size
//
//
//template <typename T> void permute(Vector<T>& V) { //随机置乱向量，使各元素等概率出现于各位置
//    for (int i = V.size(); i > 0; i--) //自后向前
//        swap(V[i - 1], V[rand() % i]); //V[i - 1]与V[0, i)中某一随机元素交换
//}
//
//
//template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //随机置乱区间[lo, hi)
//    T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
//    for (Rank i = hi - lo; 1 < i; --i) //自后向前
//        swap(V[i - 1], V[rand() % i]); //将V[i - 1]与V[0, i)中某一元素随机交换
//}
//
//
//template <typename T> //在无序向量中顺序查找e：0 <= lo < hi <= _size
//Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { //O(hi-lo)
//    while ((lo < hi--) && (e != _elem[hi])); //从后向前，顺序查找
//    return hi; //最靠后的命中者，或lo-1示意失败（lo == 0时呢？）
//}
//
//
//template <typename T> //将e插入至[r]
//Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
//    //print( e );
//    expand(); //如必要，先扩容
//    for (Rank i = _size; r < i; i--) //自后向前，后继元素
//        _elem[i] = _elem[i - 1]; //顺次后移一个单元
//    _elem[r] = e; _size++; //置入新元素并更新容量
//    return r; //返回秩
//}
//
//
//template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
//    if (lo == hi) return 0; //出于效率考虑，单独处理退化情况
//    while (hi < _size) _elem[lo++] = _elem[hi++]; //后缀[hi, _size)顺次前移hi-lo位
//    _size = lo; shrink(); //更新规模，lo=_size之后的内容无需清零；如必要，则缩容
//    //若有必要，则缩容
//    return hi - lo; //返回被删除元素的数目
//}
//
//
//template <typename T> T Vector<T>::remove(Rank r) { //删除向量中秩为r的元素，0 <= r < size
//    T e = _elem[r]; //备份被删除元素
//    remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
//    return e; //返回被删除元素
//}
//
//
//template <typename T> Rank Vector<T>::dedup() { //删除无序向量中重复元素（高效版）
//    Rank oldSize = _size; //记录原规模
//    for (Rank i = 1; i < _size; ) //自前向后逐个考查_elem[1,_size)
//        if (-1 == find(_elem[i], 0, i)) //在前缀[0,i)中寻找与[i]雷同者（至多一个），O(i)
//            i++; //若无雷同，则继续考查其后继
//        else
//            remove(i); //否则删除[i]，O(_size-i)
//    return oldSize - _size; //被删除元素总数
//}
//
//
//template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //借助函数指针机制
//{
//    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
//} //遍历向量
//
//
//template <typename T> template <typename VST> //元素类型、操作器
//void Vector<T>::traverse(VST& visit) //借助函数对象机制
//{
//    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
//} //遍历向量
//
//
//template <typename T> Rank Vector<T>::uniquify() { //有序向量重复元素剔除算法（高效版）
//    Rank i = 0, j = 0; //各对互异“相邻”元素的秩
//    while (++j < _size) //逐一扫描，直至末元素
//        if (_elem[i] != _elem[j]) //跳过雷同者
//            _elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
//    _size = ++i; shrink(); //直接截除尾部多余元素
//    return j - i; //向量规模变化量，即被删除元素总数
//}
//
//
//template <typename T> //在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
//Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { // 0 <= lo < hi <= _size
//    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
//} //等概率地随机使用二分查找、Fibonacci查找
//
//
////二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
//template <typename T> static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
//    /*DSA*/printf("BIN search (C)\n");
//    while (lo < hi) { //每步迭代仅需做一次比较判断，有两个分支
//        /*DSA*/ //for ( int i = 0; i < lo; i++ ) printf ( "     " ); if ( lo >= 0 ) for ( int i = lo; i < hi; i++ ) printf ( "....^" ); printf ( "\n" );
//        Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度折半，等效于其数值表示的右移一位）
//        (e < S[mi]) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
//    } //成功查找不能提前终止
//    /*DSA*/ //for ( int i = 0; i < lo - 1; i++ ) printf ( "     " ); if ( lo > 0 ) printf ( "....|\n" ); else printf ( "<<<<|\n" );
//    return lo - 1; //至此，[lo]为大于e的最小者，故[lo-1]即为不大于e的最大者
//} //有多个命中元素时，返回最靠后者；查找失败时，返回失败的位置
//
//
//#include "fibonacci/Fib.h" //引入Fib数列类
////Fibonacci查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
//template <typename T> static Rank fibSearch(T* S, T const& e, Rank lo, Rank hi) {
//    /*DSA*/printf("FIB search (B)\n");
//    for (Fib fib(hi - lo); lo < hi; ) { //Fib制表备查；此后每步迭代仅一次比较、两个分支
//        /*DSA*/ //for ( int i = 0; i < lo; i++ ) printf ( "     " ); if ( lo >= 0 ) for ( int i = lo; i < hi; i++ ) printf ( "....^" ); else printf ( "<<<<|" ); printf ( "\n" );
//        while (hi - lo < fib.get()) fib.prev(); //自后向前顺序查找（分摊O(1)）
//        Rank mi = lo + fib.get() - 1; //确定形如Fib(k) - 1的轴点
//        (e < S[mi]) ? hi = mi : lo = mi + 1; //比较后确定深入前半段[lo, mi)或后半段(mi, hi)
//    } //即便已经找到，也不能提前终止
//    /*DSA*/ //for( int i = 0; i < lo - 1; i++ ) printf ( "     " ); if ( lo > 0 ) printf ( "....|\n" ); else printf ( "<<<<|\n" );
//    return lo - 1; //至此，[lo]为大于e的最小者，故[lo-1]即为不大于e的最大者
//} //有多个命中元素时，返回最靠后者；查找失败时，返回失败的位置
//
//
//template <typename T> void Vector<T>::sort(Rank lo, Rank hi) { //向量区间[lo, hi)排序
//    /*DSA*/switch (5) {
//        //switch ( rand() % 6 ) {
//    case 1: bubbleSort(lo, hi); break; //起泡排序
//    case 2: selectionSort(lo, hi); break; //选择排序（习题）
//    case 3: mergeSort(lo, hi); break; //归并排序
//    case 4: heapSort(lo, hi); break; //堆排序（第12章）
//    case 5: quickSort(lo, hi); break; //快速排序（第14章）
//    default: shellSort(lo, hi); break; //希尔排序（第14章）
//    } //随机选择算法以充分测试。实用时可视具体问题的特点灵活确定或扩充
//}
//
//
//template <typename T> //向量的起泡排序（基本版）
//void Vector<T>::bubbleSort(Rank lo, Rank hi) { //assert: 0 <= lo < hi <= size
//    while (lo < --hi) //反复起泡扫描
//        for (Rank i = lo; i < hi; i++) //逐个检查相邻元素
//            if (_elem[i] > _elem[i + 1]) //若逆序，则
//                swap(_elem[i], _elem[i + 1]); //经交换使局部有序
//}
//
//
//template <typename T> //向量归并排序
//void Vector<T>::mergeSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
//    /*DSA*/ // printf ( "\tMERGEsort [%3d, %3d)\n", lo , hi );
//    if (hi - lo < 2) return; //单元素区间自然有序，否则...
//    Rank mi = (lo + hi) / 2; //以中点为界
//    mergeSort(lo, mi); mergeSort(mi, hi); //前缀、后缀分别排序
//    merge(lo, mi, hi); //归并
//}
//
//
//template <typename T> //对各自有序的[lo, mi)和[mi, hi)做归并
//void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { // lo < mi < hi
//    Rank i = 0; T* A = _elem + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
//    Rank j = 0, lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
//    for (Rank i = 0; i < lb; i++) B[i] = A[i]; //复制出A的前缀
//    Rank k = 0, lc = hi - mi; T* C = _elem + mi; //后缀C[0, lc) = _elem[mi, hi)就地
//    while ((j < lb) && (k < lc)) //反复地比较B、C的首元素
//        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++]; //将更小者归入A中
//    while (j < lb) //若C先耗尽，则
//        A[i++] = B[j++]; //将B残余的后缀归入A中——若B先耗尽呢？
//    delete[] B; //释放临时空间：mergeSort()过程中，如何避免此类反复的new/delete？
//}
//
//
//template <typename T> //向量选择排序
//void Vector<T>::selectionSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
//    /*DSA*/ // printf( "Selectionsort [%3d, %3d)\n", lo, hi );
//    while (lo < --hi)
//        swap(_elem[maxItem(lo, hi)], _elem[hi]); //将[hi]与[lo, hi]中的最大者交换
//}
//
//template <typename T> Rank Vector<T>::maxItem(Rank lo, Rank hi) { //在[lo, hi]内找出最大者
//    Rank mx = hi;
//    while (lo < hi--) //逆向扫描
//        if (_elem[hi] > _elem[mx]) //且严格比较
//            mx = hi; //故能在max有多个时保证后者优先，进而保证selectionSort稳定
//    return mx;
//}



#pragma once
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <cstdio>

using Rank = unsigned int;
#define DEFAULT_CAPACITY  3

template <typename T> class Vector {
protected:
    Rank _size; Rank _capacity;  T* _elem;
    void copyFrom(T const* A, Rank lo, Rank hi) {
        _elem = new T[_capacity = std::max<Rank>(DEFAULT_CAPACITY, (hi - lo) * 2)];
        for (_size = 0; lo < hi; _size++, lo++)
            _elem[_size] = A[lo];
    }
    void expand() {
        if (_size < _capacity) return;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i];
        delete[] oldElem;
    }
    void shrink() {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;
        T* oldElem = _elem; _elem = new T[_capacity >>= 1];
        for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i];
        delete[] oldElem;
    }
    bool bubble(Rank lo, Rank hi) {
        bool sorted = true;
        while (++lo < hi) {
            if (_elem[lo - 1].operator>(_elem[lo])) { // 成员函数调用
                std::swap(_elem[lo - 1], _elem[lo]);
                sorted = false;
            }
        }
        return sorted;
    }
public:
    // 构造函数
    Vector(Rank c = DEFAULT_CAPACITY) { _elem = new T[_capacity = c]; _size = 0; }
    Vector(Rank c, Rank s, T v) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
    ~Vector() { delete[] _elem; }

    // 只读接口
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    Rank find(T const& e) const { return find(e, 0, _size); }
    Rank find(T const& e, Rank lo, Rank hi) const {
        while ((lo < hi--) && (e.operator!=(_elem[hi]))); // 成员函数调用
        return hi;
    }

    // 可写接口
    T& operator[] (Rank r) { assert(r < _size && r >= 0); return _elem[r]; }
    const T& operator[] (Rank r) const { assert(r < _size && r >= 0); return _elem[r]; }
    Vector<T>& operator= (Vector<T> const& V) {
        if (_elem) delete[] _elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }
    T remove(Rank r) { T e = _elem[r]; remove(r, r + 1); return e; }
    Rank remove(Rank lo, Rank hi) {
        if (lo == hi) return 0;
        while (hi < _size) _elem[lo++] = _elem[hi++];
        _size = lo; shrink();
        return hi - lo;
    }
    Rank insert(Rank r, T const& e) {
        expand();
        for (Rank i = _size; r < i; i--) _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }
    Rank insert(T const& e) { return insert(_size, e); }

    // 排序（显式调用成员函数，避免歧义）
    void bubbleSort(Rank lo, Rank hi) {
        while (lo < --hi) {
            for (Rank i = lo; i < hi; i++) {
                if (_elem[i].operator>(_elem[i + 1])) { // 成员函数调用
                    std::swap(_elem[i], _elem[i + 1]);
                }
            }
        }
    }
    void merge(Rank lo, Rank mi, Rank hi) {
        Rank i = 0; T* A = _elem + lo;
        Rank j = 0, lb = mi - lo; T* B = new T[lb];
        for (Rank i = 0; i < lb; i++) B[i] = A[i];
        Rank k = 0, lc = hi - mi; T* C = _elem + mi;
        while ((j < lb) && (k < lc)) {
            A[i++] = (B[j].operator<=(C[k])) ? B[j++] : C[k++]; // 成员函数调用
        }
        while (j < lb) A[i++] = B[j++];
        delete[] B;
    }
    void mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2) return;
        Rank mi = (lo + hi) / 2;
        mergeSort(lo, mi); mergeSort(mi, hi);
        merge(lo, mi, hi);
    }
    void sort() { mergeSort(0, _size); } // 默认归并排序
    void unsort(Rank lo, Rank hi) {
        T* V = _elem + lo;
        for (Rank i = hi - lo; 1 < i; --i)
            std::swap(V[i - 1], V[rand() % i]);
    }
    void unsort() { unsort(0, _size); }

    // 去重
    Rank uniquify() {
        Rank i = 0, j = 0;
        while (++j < _size) {
            if (_elem[i].operator!=(_elem[j])) { // 成员函数调用
                _elem[++i] = _elem[j];
            }
        }
        _size = ++i; shrink();
        return j - i;
    }
};

// 全局置乱函数
template <typename T> void permute(Vector<T>& V) {
    for (int i = V.size(); i > 0; i--)
        std::swap(V[i - 1], V[rand() % i]);
}