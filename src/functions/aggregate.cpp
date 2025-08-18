#include "aggregate.h"


template<typename T>
T sum(ColumnBase* col) {
    Column<T>* colA = static_cast<Column<T>*>(col);
    int numRows = colA->numRows();
    T res(0);

    for (int i = 0; i < numRows; i++) {
        res.value += colA->data[i].value;
    }

    return res;
}

template<typename T>
T min(ColumnBase* col) {
    Column<T>* colA = static_cast<Column<T>*>(col);
    int numRows = colA->numRows();
    if(numRows == 0) {
        //cant call min on empty column
        return T(0);
    }

    T res(colA->data[0]);
    for (int i = 1; i < numRows; i++) {
        res.value = std::min(res.value, colA->data[i].value);
    }

    return res;
}

template<typename T>
T max(ColumnBase* col) {
    Column<T>* colA = static_cast<Column<T>*>(col);
    int numRows = colA->numRows();
    if(numRows == 0) {
        //cant call max on empty column
        return T(0);
    }

    T res(colA->data[0]);
    for (int i = 1; i < numRows; i++) {
        res.value = std::max(res.value, colA->data[i].value);
    }

    return res;
}

template<typename T>
T avg(ColumnBase* col) {
    Column<T>* colA = static_cast<Column<T>*>(col);
    int numRows = colA->numRows();
    if(numRows == 0) {
        //cant call avg on empty column
        return T(0);
    }

    T res(colA->data[0]);
    for (int i = 1; i < numRows; i++) {
        res.value += colA->data[i].value;
    }
    res.value = res.value / numRows;

    return res;
}

int32 count(ColumnBase* col) {
    return int32(col->numRows());
}


template int8 sum<int8>(ColumnBase*);
template int16 sum<int16>(ColumnBase*);
template int32 sum<int32>(ColumnBase*);
template int64 sum<int64>(ColumnBase*);

template int8 min<int8>(ColumnBase*);
template int16 min<int16>(ColumnBase*);
template int32 min<int32>(ColumnBase*);
template int64 min<int64>(ColumnBase*);

template int8 max<int8>(ColumnBase*);
template int16 max<int16>(ColumnBase*);
template int32 max<int32>(ColumnBase*);
template int64 max<int64>(ColumnBase*);

template int8 avg<int8>(ColumnBase*);
template int16 avg<int16>(ColumnBase*);
template int32 avg<int32>(ColumnBase*);
template int64 avg<int64>(ColumnBase*);
