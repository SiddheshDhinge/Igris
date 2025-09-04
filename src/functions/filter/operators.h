#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include "../../format/columnar.h"

class OperatorBase {};


class OperatorAND: public OperatorBase {
public:
    bool process(bool left, bool right);
};

class OperatorOR: public OperatorBase {
public:
    bool process(bool left, bool right);
};


template<typename T1, typename T2>
class OperatorLT: public OperatorBase {
    std::vector<bool> process(Column<T1>* left, Column<T2>* right);
    std::vector<bool> process(Column<T1>* left, T2 right);
    std::vector<bool> process(T1 left, Column<T2>* right);
    bool process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorLTE: public OperatorBase {
    std::vector<bool> process(Column<T1>* left, Column<T2>* right);
    std::vector<bool> process(Column<T1>* left, T2 right);
    std::vector<bool> process(T1 left, Column<T2>* right);
    bool process(T1 left, T2 right);
};



template<typename T1, typename T2>
class OperatorGT: public OperatorBase {
    std::vector<bool> process(Column<T1>* left, Column<T2>* right);
    std::vector<bool> process(Column<T1>* left, T2 right);
    std::vector<bool> process(T1 left, Column<T2>* right);
    bool process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorGTE: public OperatorBase {
    std::vector<bool> process(Column<T1>* left, Column<T2>* right);
    std::vector<bool> process(Column<T1>* left, T2 right);
    std::vector<bool> process(T1 left, Column<T2>* right);
    bool process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorSum: public OperatorBase {
    std::vector<T1> process(Column<T1>* left, Column<T2>* right);
    std::vector<T1> process(Column<T1>* left, T2 right);
    std::vector<T1> process(T1 left, Column<T2>* right);
    T1 process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorSub: public OperatorBase {
    std::vector<T1> process(Column<T1>* left, Column<T2>* right);
    std::vector<T1> process(Column<T1>* left, T2 right);
    std::vector<T1> process(T1 left, Column<T2>* right);
    T1 process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorDiv: public OperatorBase {
    std::vector<T1> process(Column<T1>* left, Column<T2>* right);
    std::vector<T1> process(Column<T1>* left, T2 right);
    std::vector<T1> process(T1 left, Column<T2>* right);
    T1 process(T1 left, T2 right);
};


template<typename T1, typename T2>
class OperatorMul: public OperatorBase {
    std::vector<T1> process(Column<T1>* left, Column<T2>* right);
    std::vector<T1> process(Column<T1>* left, T2 right);
    std::vector<T1> process(T1 left, Column<T2>* right);
    T1 process(T1 left, T2 right);
};

#endif