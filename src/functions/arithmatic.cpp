#include "arithmatic.h"


template<typename T1, typename T2>
T1 SumOp<T1,T2>::operator()(T1 left, T2 right) {
    return T1(left.value + right.value);
}

template<typename T1, typename T2>
T1 SubOp<T1,T2>::operator()(T1 left, T2 right) {
    return T1(left.value - right.value);
}

template<typename T1, typename T2>
T1 MulOp<T1,T2>::operator()(T1 left, T2 right) {
    return T1(left.value * right.value);
}

template<typename T1, typename T2>
T1 DivOp<T1,T2>::operator()(T1 left, T2 right) {
    return T1(left.value / right.value);
}


template<typename T1, typename T2, typename Op>
Column<T1>* Arithmatic<T1,T2, Op>::operator()(ColumnBase* left, ColumnBase* right) {
    int numRows = left->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(left);
    Column<T2>* colB = static_cast<Column<T2>*>(right);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = Op()(valueA, valueB);
    }

    return res;
}

template<typename T1, typename T2, typename Op>
Column<T1>* Arithmatic<T1,T2, Op>::operator()(ColumnBase* left, T2 right) {
    int numRows = left->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(left);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        res->data[i] = Op()(colA->data[i], right);
    }

    return res;
}

template<typename T1, typename T2, typename Op>
Column<T1>* Arithmatic<T1,T2, Op>::operator()(T1 left, ColumnBase* right) {
    int numRows = right->numRows();

    Column<T2>* colB = static_cast<Column<T2>*>(right);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        res->data[i] = Op()(left, colB->data[i]);
    }

    return res;
}

template<typename T1, typename T2, typename Op>
T1 Arithmatic<T1,T2, Op>::operator()(T1 left, T2 right) {
    return Op()(left, right);
}


template class Arithmatic<int8, int8, SumOp<int8, int8>>;
template class Arithmatic<int16, int16, SumOp<int16, int16>>;
template class Arithmatic<int32, int32, SumOp<int32, int32>>;
template class Arithmatic<int64, int64, SumOp<int64, int64>>;

template class Arithmatic<int8, int8, SubOp<int8, int8>>;
template class Arithmatic<int16, int16, SubOp<int16, int16>>;
template class Arithmatic<int32, int32, SubOp<int32, int32>>;
template class Arithmatic<int64, int64, SubOp<int64, int64>>;

template class Arithmatic<int8, int8, MulOp<int8, int8>>;
template class Arithmatic<int16, int16, MulOp<int16, int16>>;
template class Arithmatic<int32, int32, MulOp<int32, int32>>;
template class Arithmatic<int64, int64, MulOp<int64, int64>>;

template class Arithmatic<int8, int8, DivOp<int8, int8>>;
template class Arithmatic<int16, int16, DivOp<int16, int16>>;
template class Arithmatic<int32, int32, DivOp<int32, int32>>;
template class Arithmatic<int64, int64, DivOp<int64, int64>>;

