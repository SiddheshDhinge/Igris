#include "operators.h"


bool OperatorAND::process(bool left, bool right) {
    return left & right;
}


bool OperatorOR::process(bool left, bool right) {
    return left | right;
}


template<typename T1, typename T2>
std::vector<bool> OperatorLT<T1,T2>::process(Column<T1>* left, Column<T2>* right) {
    static_assert(left->numRows() == right->numRows());

    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value < right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorLT<T1,T2>::process(Column<T1>* left, T2 right) {
    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value < right.value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorLT<T1,T2>::process(T1 left, Column<T2>* right) {
    int n = right->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left.value < right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
bool OperatorLT<T1,T2>::process(T1 left, T2 right) {
    return left.value < right.value;
}


template<typename T1, typename T2>
std::vector<bool> OperatorLTE<T1,T2>::process(Column<T1>* left, Column<T2>* right) {
    static_assert(left->numRows() == right->numRows());

    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value <= right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorLTE<T1,T2>::process(Column<T1>* left, T2 right) {
    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value <= right.value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorLTE<T1,T2>::process(T1 left, Column<T2>* right) {
    int n = right->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left.value <= right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
bool OperatorLTE<T1,T2>::process(T1 left, T2 right) {
    return left.value <= right.value;
}


template<typename T1, typename T2>
std::vector<bool> OperatorGT<T1,T2>::process(Column<T1>* left, Column<T2>* right) {
    static_assert(left->numRows() == right->numRows());

    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value > right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorGT<T1,T2>::process(Column<T1>* left, T2 right) {
    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value > right.value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorGT<T1,T2>::process(T1 left, Column<T2>* right) {
    int n = right->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left.value > right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
bool OperatorGT<T1,T2>::process(T1 left, T2 right) {
    return left.value > right.value;
}


template<typename T1, typename T2>
std::vector<bool> OperatorGTE<T1,T2>::process(Column<T1>* left, Column<T2>* right) {
    static_assert(left->numRows() == right->numRows());

    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value >= right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorGTE<T1,T2>::process(Column<T1>* left, T2 right) {
    int n = left->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left->data[i].value >= right.value;
    }

    return res;
}

template<typename T1, typename T2>
std::vector<bool> OperatorGTE<T1,T2>::process(T1 left, Column<T2>* right) {
    int n = right->numRows();
    std::vector<bool> res(n);
    
    for(int i=0; i<n; i++) {
        res[i] = left.value >= right->data[i].value;
    }

    return res;
}

template<typename T1, typename T2>
bool OperatorGTE<T1,T2>::process(T1 left, T2 right) {
    return left.value >= right.value;
}