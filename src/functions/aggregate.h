#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "../format/columnar.h"
#include <vector>

template<typename T>
T sum(ColumnBase* col);

template<typename T>
T min(ColumnBase* col);

template<typename T>
T max(ColumnBase* col);

template<typename T>
T avg(ColumnBase* col);

int32 count(ColumnBase* col);

#endif