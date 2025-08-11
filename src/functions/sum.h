#ifndef SUM_H
#define SUM_H

#include "../format/columnar.h"
#include <vector>

template<typename T1, typename T2>
Column<T1>* sum(ColumnBase* a, ColumnBase* b);

#endif