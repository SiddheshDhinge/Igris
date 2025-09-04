#ifndef ARITHMATIC_H
#define ARITHMATIC_H

#include "../format/columnar.h"
#include <vector>


template<typename T1, typename T2>
struct SumOp {
    T1 operator()(T1 left, T2 right);
};

template<typename T1, typename T2>
struct SubOp {
    T1 operator()(T1 left, T2 right);
};

template<typename T1, typename T2>
struct MulOp {
    T1 operator()(T1 left, T2 right);
};

template<typename T1, typename T2>
struct DivOp {
    T1 operator()(T1 left, T2 right);
};


template<typename T1, typename T2, typename Op>
class Arithmatic {
public:
    Column<T1>* operator()(ColumnBase* left, ColumnBase* right);
    Column<T1>* operator()(ColumnBase* left, T2 right);
    Column<T1>* operator()(T1 left, ColumnBase* right);
    T1 operator()(T1 left, T2 right);
};


template<typename T1, typename T2>
using Sum = Arithmatic<T1, T2, SumOp<T1, T2>>;

template<typename T1, typename T2>
using Substract = Arithmatic<T1, T2, SubOp<T1, T2>>;

template<typename T1, typename T2>
using Multiply = Arithmatic<T1, T2, MulOp<T1, T2>>;

template<typename T1, typename T2>
using Divide = Arithmatic<T1, T2, DivOp<T1, T2>>;

#endif