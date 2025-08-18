#include "arithmatic.h"


template<typename T1, typename T2>
Column<T1>* sum(ColumnBase* a, ColumnBase* b) {
  int numRows = a->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(a);
    Column<T2>* colB = static_cast<Column<T2>*>(b);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = T1(valueA.value + valueB.value);
    }

    return res;
}

template<typename T1, typename T2>
Column<T1>* substract(ColumnBase* a, ColumnBase* b) {
  int numRows = a->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(a);
    Column<T2>* colB = static_cast<Column<T2>*>(b);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = T1(valueA.value - valueB.value);
    }

    return res;
}

template<typename T1, typename T2>
Column<T1>* divide(ColumnBase* a, ColumnBase* b) {
  int numRows = a->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(a);
    Column<T2>* colB = static_cast<Column<T2>*>(b);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = T1(valueA.value / valueB.value);
    }

    return res;
}

template<typename T1, typename T2>
Column<T1>* multiply(ColumnBase* a, ColumnBase* b) {
  int numRows = a->numRows();

    Column<T1>* colA = static_cast<Column<T1>*>(a);
    Column<T2>* colB = static_cast<Column<T2>*>(b);

    Column<T1>* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = T1(valueA.value * valueB.value);
    }

    return res;
}

template Column<int8>* sum<int8, int8>(ColumnBase*, ColumnBase*);
template Column<int16>* sum<int16, int16>(ColumnBase*, ColumnBase*);
template Column<int32>* sum<int32, int32>(ColumnBase*, ColumnBase*);
template Column<int64>* sum<int64, int64>(ColumnBase*, ColumnBase*);

template Column<int8>* substract<int8, int8>(ColumnBase*, ColumnBase*);
template Column<int16>* substract<int16, int16>(ColumnBase*, ColumnBase*);
template Column<int32>* substract<int32, int32>(ColumnBase*, ColumnBase*);
template Column<int64>* substract<int64, int64>(ColumnBase*, ColumnBase*);

template Column<int8>* divide<int8, int8>(ColumnBase*, ColumnBase*);
template Column<int16>* divide<int16, int16>(ColumnBase*, ColumnBase*);
template Column<int32>* divide<int32, int32>(ColumnBase*, ColumnBase*);
template Column<int64>* divide<int64, int64>(ColumnBase*, ColumnBase*);

template Column<int8>* multiply<int8, int8>(ColumnBase*, ColumnBase*);
template Column<int16>* multiply<int16, int16>(ColumnBase*, ColumnBase*);
template Column<int32>* multiply<int32, int32>(ColumnBase*, ColumnBase*);
template Column<int64>* multiply<int64, int64>(ColumnBase*, ColumnBase*);
