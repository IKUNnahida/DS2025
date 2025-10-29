//using Rank = unsigned int; //��
//#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
//
//template <typename T> class Vector { //����ģ����
//protected:
//   Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
//   void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
//   void expand(); //�ռ䲻��ʱ����
//   void shrink(); //װ�����ӹ�Сʱѹ��
//   bool bubble ( Rank lo, Rank hi ); //ɨ�轻��
//   void bubbleSort ( Rank lo, Rank hi ); //���������㷨
//   Rank maxItem ( Rank lo, Rank hi ); //ѡȡ���Ԫ��
//   void selectionSort ( Rank lo, Rank hi ); //ѡ�������㷨
//   void merge ( Rank lo, Rank mi, Rank hi ); //�鲢�㷨
//   void mergeSort ( Rank lo, Rank hi ); //�鲢�����㷨
//   void heapSort ( Rank lo, Rank hi ); //�������Ժ�����ȫ�ѽ��⣩
//   Rank partition ( Rank lo, Rank hi ); //��㹹���㷨
//   void quickSort ( Rank lo, Rank hi ); //���������㷨
//   void shellSort ( Rank lo, Rank hi ); //ϣ�������㷨
//public:
//// ���췽��
//   Vector ( Rank c = DEFAULT_CAPACITY ) //����Ϊc�Ŀ�����
//   { _elem = new T[_capacity = c]; _size = 0; }
//   Vector ( Rank c, Rank s, T v ) //����Ϊc����ģΪs������Ԫ�س�ʼΪv��s<=c
//   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
//   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //�������帴��
//   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //����
//   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //�������帴��
//   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //����
//// ��������
//   ~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�
//// ֻ�����ʽӿ�
//   Rank size() const { return _size; } //��ģ
//   bool empty() const { return !_size; } //�п�
//   Rank find ( T const& e ) const { return find ( e, 0, _size ); } //���������������
//   Rank find ( T const& e, Rank lo, Rank hi ) const; //���������������
//   Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //�������������ҵ���k���Ԫ��
//   Rank search( T const& e ) const //���������������
//   { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
//   Rank search ( T const& e, Rank lo, Rank hi ) const; //���������������
//// ��д���ʽӿ�
//   T& operator[] ( Rank r ); //�����±������������������������ʽ���ø�Ԫ��
//   const T& operator[] ( Rank r ) const; //����������ֵ�����ذ汾
//   Vector<T> & operator= ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
//   T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
//   Rank remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
//   Rank insert ( Rank r, T const& e ); //����Ԫ��
//   Rank insert ( T const& e ) { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���
//   void sort ( Rank lo, Rank hi ); //��[lo, hi)����
//   void sort() { sort ( 0, _size ); } //��������
//   void unsort ( Rank lo, Rank hi ); //��[lo, hi)����
//   void unsort() { unsort ( 0, _size ); } //��������
//   Rank dedup(); //����ȥ��
//   Rank uniquify(); //����ȥ��
//// ����
//   void traverse ( void (* ) ( T& ) ); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
//   template <typename VST> void traverse ( VST& ); //������ʹ�ú������󣬿�ȫ�����޸ģ�
//}; //Vector
//
//
//template <typename T> //TΪ�������ͣ��������ظ�ֵ������'='
//void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������A[lo, hi)Ϊ������������
//    _elem = new T[_capacity = max<Rank>(DEFAULT_CAPACITY, (hi - lo) * 2)]; //����ռ�
//    for (_size = 0; lo < hi; _size++, lo++) //A[lo, hi)�ڵ�Ԫ����һ
//        _elem[_size] = A[lo]; //������_elem[0, hi-lo)��TΪ�������ͣ��������ظ�ֵ������'='
//} //��const���Σ���֤A�е�Ԫ�ز��±��۸ģ�����ʱ�� = O(hi-lo)
//
//
//template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //���
//    if (_elem) delete[] _elem; //�ͷ�ԭ������
//    copyFrom(V._elem, 0, V.size()); //���帴��
//    return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
//}
//
//
//template <typename T> void Vector<T>::expand() { //�����ռ䲻��ʱ����
//    if (_size < _capacity) return; //��δ��Աʱ����������
//    T* oldElem = _elem; copyFrom(oldElem, 0, _capacity); //�����ӱ�
//    /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
//    delete[] oldElem; //�ͷ�ԭ�ռ�
//}
//
//
//template <typename T> void Vector<T>::shrink() { //װ�����ӹ�Сʱѹ��������ռ�ռ�
//    if (_capacity < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
//    if (_size << 2 > _capacity) return; //��25%Ϊ��
//    T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //��������
//    for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
//    delete[] oldElem; //�ͷ�ԭ�ռ�
//}
//
//
//template <typename T> T& Vector<T>::operator[] (Rank r) //�����±������
//{
//    return _elem[r];
//} // assert: 0 <= r < _size
//
//
//template <typename T> void permute(Vector<T>& V) { //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
//    for (int i = V.size(); i > 0; i--) //�Ժ���ǰ
//        swap(V[i - 1], V[rand() % i]); //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
//}
//
//
//template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�����������[lo, hi)
//    T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
//    for (Rank i = hi - lo; 1 < i; --i) //�Ժ���ǰ
//        swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
//}
//
//
//template <typename T> //������������˳�����e��0 <= lo < hi <= _size
//Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { //O(hi-lo)
//    while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳�����
//    return hi; //���������ߣ���lo-1ʾ��ʧ�ܣ�lo == 0ʱ�أ���
//}
//
//
//template <typename T> //��e������[r]
//Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
//    //print( e );
//    expand(); //���Ҫ��������
//    for (Rank i = _size; r < i; i--) //�Ժ���ǰ�����Ԫ��
//        _elem[i] = _elem[i - 1]; //˳�κ���һ����Ԫ
//    _elem[r] = e; _size++; //������Ԫ�ز���������
//    return r; //������
//}
//
//
//template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
//    if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����
//    while (hi < _size) _elem[lo++] = _elem[hi++]; //��׺[hi, _size)˳��ǰ��hi-loλ
//    _size = lo; shrink(); //���¹�ģ��lo=_size֮��������������㣻���Ҫ��������
//    //���б�Ҫ��������
//    return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
//}
//
//
//template <typename T> T Vector<T>::remove(Rank r) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
//    T e = _elem[r]; //���ݱ�ɾ��Ԫ��
//    remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
//    return e; //���ر�ɾ��Ԫ��
//}
//
//
//template <typename T> Rank Vector<T>::dedup() { //ɾ�������������ظ�Ԫ�أ���Ч�棩
//    Rank oldSize = _size; //��¼ԭ��ģ
//    for (Rank i = 1; i < _size; ) //��ǰ����������_elem[1,_size)
//        if (-1 == find(_elem[i], 0, i)) //��ǰ׺[0,i)��Ѱ����[i]��ͬ�ߣ�����һ������O(i)
//            i++; //������ͬ���������������
//        else
//            remove(i); //����ɾ��[i]��O(_size-i)
//    return oldSize - _size; //��ɾ��Ԫ������
//}
//
//
//template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //��������ָ�����
//{
//    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
//} //��������
//
//
//template <typename T> template <typename VST> //Ԫ�����͡�������
//void Vector<T>::traverse(VST& visit) //���������������
//{
//    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
//} //��������
//
//
//template <typename T> Rank Vector<T>::uniquify() { //���������ظ�Ԫ���޳��㷨����Ч�棩
//    Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
//    while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
//        if (_elem[i] != _elem[j]) //������ͬ��
//            _elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
//    _size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
//    return j - i; //������ģ�仯��������ɾ��Ԫ������
//}
//
//
//template <typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
//Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { // 0 <= lo < hi <= _size
//    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
//} //�ȸ��ʵ����ʹ�ö��ֲ��ҡ�Fibonacci����
//
//
////���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
//template <typename T> static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
//    /*DSA*/printf("BIN search (C)\n");
//    while (lo < hi) { //ÿ������������һ�αȽ��жϣ���������֧
//        /*DSA*/ //for ( int i = 0; i < lo; i++ ) printf ( "     " ); if ( lo >= 0 ) for ( int i = lo; i < hi; i++ ) printf ( "....^" ); printf ( "\n" );
//        Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�������۰룬��Ч������ֵ��ʾ������һλ��
//        (e < S[mi]) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
//    } //�ɹ����Ҳ�����ǰ��ֹ
//    /*DSA*/ //for ( int i = 0; i < lo - 1; i++ ) printf ( "     " ); if ( lo > 0 ) printf ( "....|\n" ); else printf ( "<<<<|\n" );
//    return lo - 1; //���ˣ�[lo]Ϊ����e����С�ߣ���[lo-1]��Ϊ������e�������
//} //�ж������Ԫ��ʱ����������ߣ�����ʧ��ʱ������ʧ�ܵ�λ��
//
//
//#include "fibonacci/Fib.h" //����Fib������
////Fibonacci�����㷨���汾B��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
//template <typename T> static Rank fibSearch(T* S, T const& e, Rank lo, Rank hi) {
//    /*DSA*/printf("FIB search (B)\n");
//    for (Fib fib(hi - lo); lo < hi; ) { //Fib�Ʊ��飻�˺�ÿ��������һ�αȽϡ�������֧
//        /*DSA*/ //for ( int i = 0; i < lo; i++ ) printf ( "     " ); if ( lo >= 0 ) for ( int i = lo; i < hi; i++ ) printf ( "....^" ); else printf ( "<<<<|" ); printf ( "\n" );
//        while (hi - lo < fib.get()) fib.prev(); //�Ժ���ǰ˳����ң���̯O(1)��
//        Rank mi = lo + fib.get() - 1; //ȷ������Fib(k) - 1�����
//        (e < S[mi]) ? hi = mi : lo = mi + 1; //�ȽϺ�ȷ������ǰ���[lo, mi)�����(mi, hi)
//    } //�����Ѿ��ҵ���Ҳ������ǰ��ֹ
//    /*DSA*/ //for( int i = 0; i < lo - 1; i++ ) printf ( "     " ); if ( lo > 0 ) printf ( "....|\n" ); else printf ( "<<<<|\n" );
//    return lo - 1; //���ˣ�[lo]Ϊ����e����С�ߣ���[lo-1]��Ϊ������e�������
//} //�ж������Ԫ��ʱ����������ߣ�����ʧ��ʱ������ʧ�ܵ�λ��
//
//
//template <typename T> void Vector<T>::sort(Rank lo, Rank hi) { //��������[lo, hi)����
//    /*DSA*/switch (5) {
//        //switch ( rand() % 6 ) {
//    case 1: bubbleSort(lo, hi); break; //��������
//    case 2: selectionSort(lo, hi); break; //ѡ������ϰ�⣩
//    case 3: mergeSort(lo, hi); break; //�鲢����
//    case 4: heapSort(lo, hi); break; //�����򣨵�12�£�
//    case 5: quickSort(lo, hi); break; //�������򣨵�14�£�
//    default: shellSort(lo, hi); break; //ϣ�����򣨵�14�£�
//    } //���ѡ���㷨�Գ�ֲ��ԡ�ʵ��ʱ���Ӿ���������ص����ȷ��������
//}
//
//
//template <typename T> //�������������򣨻����棩
//void Vector<T>::bubbleSort(Rank lo, Rank hi) { //assert: 0 <= lo < hi <= size
//    while (lo < --hi) //��������ɨ��
//        for (Rank i = lo; i < hi; i++) //����������Ԫ��
//            if (_elem[i] > _elem[i + 1]) //��������
//                swap(_elem[i], _elem[i + 1]); //������ʹ�ֲ�����
//}
//
//
//template <typename T> //�����鲢����
//void Vector<T>::mergeSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
//    /*DSA*/ // printf ( "\tMERGEsort [%3d, %3d)\n", lo , hi );
//    if (hi - lo < 2) return; //��Ԫ��������Ȼ���򣬷���...
//    Rank mi = (lo + hi) / 2; //���е�Ϊ��
//    mergeSort(lo, mi); mergeSort(mi, hi); //ǰ׺����׺�ֱ�����
//    merge(lo, mi, hi); //�鲢
//}
//
//
//template <typename T> //�Ը��������[lo, mi)��[mi, hi)���鲢
//void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { // lo < mi < hi
//    Rank i = 0; T* A = _elem + lo; //�ϲ������������A[0, hi - lo) = _elem[lo, hi)
//    Rank j = 0, lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) <-- _elem[lo, mi)
//    for (Rank i = 0; i < lb; i++) B[i] = A[i]; //���Ƴ�A��ǰ׺
//    Rank k = 0, lc = hi - mi; T* C = _elem + mi; //��׺C[0, lc) = _elem[mi, hi)�͵�
//    while ((j < lb) && (k < lc)) //�����رȽ�B��C����Ԫ��
//        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++]; //����С�߹���A��
//    while (j < lb) //��C�Ⱥľ�����
//        A[i++] = B[j++]; //��B����ĺ�׺����A�С�����B�Ⱥľ��أ�
//    delete[] B; //�ͷ���ʱ�ռ䣺mergeSort()�����У���α�����෴����new/delete��
//}
//
//
//template <typename T> //����ѡ������
//void Vector<T>::selectionSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
//    /*DSA*/ // printf( "Selectionsort [%3d, %3d)\n", lo, hi );
//    while (lo < --hi)
//        swap(_elem[maxItem(lo, hi)], _elem[hi]); //��[hi]��[lo, hi]�е�����߽���
//}
//
//template <typename T> Rank Vector<T>::maxItem(Rank lo, Rank hi) { //��[lo, hi]���ҳ������
//    Rank mx = hi;
//    while (lo < hi--) //����ɨ��
//        if (_elem[hi] > _elem[mx]) //���ϸ�Ƚ�
//            mx = hi; //������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ�
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
            if (_elem[lo - 1].operator>(_elem[lo])) { // ��Ա��������
                std::swap(_elem[lo - 1], _elem[lo]);
                sorted = false;
            }
        }
        return sorted;
    }
public:
    // ���캯��
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

    // ֻ���ӿ�
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    Rank find(T const& e) const { return find(e, 0, _size); }
    Rank find(T const& e, Rank lo, Rank hi) const {
        while ((lo < hi--) && (e.operator!=(_elem[hi]))); // ��Ա��������
        return hi;
    }

    // ��д�ӿ�
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

    // ������ʽ���ó�Ա�������������壩
    void bubbleSort(Rank lo, Rank hi) {
        while (lo < --hi) {
            for (Rank i = lo; i < hi; i++) {
                if (_elem[i].operator>(_elem[i + 1])) { // ��Ա��������
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
            A[i++] = (B[j].operator<=(C[k])) ? B[j++] : C[k++]; // ��Ա��������
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
    void sort() { mergeSort(0, _size); } // Ĭ�Ϲ鲢����
    void unsort(Rank lo, Rank hi) {
        T* V = _elem + lo;
        for (Rank i = hi - lo; 1 < i; --i)
            std::swap(V[i - 1], V[rand() % i]);
    }
    void unsort() { unsort(0, _size); }

    // ȥ��
    Rank uniquify() {
        Rank i = 0, j = 0;
        while (++j < _size) {
            if (_elem[i].operator!=(_elem[j])) { // ��Ա��������
                _elem[++i] = _elem[j];
            }
        }
        _size = ++i; shrink();
        return j - i;
    }
};

// ȫ�����Һ���
template <typename T> void permute(Vector<T>& V) {
    for (int i = V.size(); i > 0; i--)
        std::swap(V[i - 1], V[rand() % i]);
}