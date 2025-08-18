#ifndef ARITHMATIC_H
#define ARITHMATIC_H

#include "../format/columnar.h"
#include <vector>

template<typename T1, typename T2>
Column<T1>* sum(ColumnBase* a, ColumnBase* b);

template<typename T1, typename T2>
Column<T1>* substract(ColumnBase* a, ColumnBase* b);

template<typename T1, typename T2>
Column<T1>* divide(ColumnBase* a, ColumnBase* b);

template<typename T1, typename T2>
Column<T1>* multiply(ColumnBase* a, ColumnBase* b);

#endif