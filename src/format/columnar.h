#ifndef COLUMNAR_H
#define COLUMNAR_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <map>
#include <variant>
#include "datatype.h"


class ColumnBase {
public:
    virtual int numRows() = 0;
};

template<typename T> class Column: public ColumnBase
{
    public:
    std::vector<T> data;

    Column(std::vector<T> input);
    Column(int numRows);
    ~Column();

    virtual int numRows() override;
};

class DataFrame
{
    public:
    const static int show_width = 10;

    std::vector<ColumnBase*> data;
    std::vector<std::string> headers;
    std::vector<DataTypeEnum> schema;
    
    DataFrame(int numRows, int numColumns, std::vector<std::string> headers, std::vector<DataTypeEnum> schema);
    DataFrame(std::vector<ColumnBase*> &input, std::vector<std::string> headers, std::vector<DataTypeEnum> schema);
    ~DataFrame();

    void show();
    int numColumns();
    int numRows();
    void addColumn(ColumnBase* newColumn, std::string header_name, DataTypeEnum column_schema);
};

#endif