#ifndef COLUMNAR_H
#define COLUMNAR_H

#include <vector>
#include <iostream>
#include <iomanip>

class Column
{
    public:
    std::vector<int>* data;

    Column(std::vector<int>* input);
    Column(int numRows);
    ~Column();

    int numRows();
};

class DataFrame
{
    public:
    const static int show_width = 10;

    std::vector<Column*>* data;
    std::vector<std::string>* headers;
    
    DataFrame(int numColumns, int numRows, std::vector<std::string>* headers);
    DataFrame(int numColumns, std::vector<Column*>* data, std::vector<std::string>* headers);
    ~DataFrame();

    void show();
    int numColumns();
    void addColumn(Column* newColumn, std::string header_name);
};

#endif