#include "sum.h"

template<typename T1, typename T2>
Column<T1>* sum(ColumnBase* a, ColumnBase* b) {
  int numRows = a->numRows();

    auto colA = static_cast<Column<T1>*>(a);
    auto colB = static_cast<Column<T2>*>(b);

    auto* res = new Column<T1>(numRows);

    for (int i = 0; i < numRows; i++) {
        T1 valueA = colA->data[i];
        T2 valueB = colB->data[i];

        res->data[i] = T1(valueA.value + valueB.value);
    }

    return res;
}

template Column<int32>* sum<int32, int32>(ColumnBase*, ColumnBase*);
