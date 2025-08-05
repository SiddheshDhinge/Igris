#ifndef COLUMNAR_H
#define COLUMNAR_H

#include <vector>
#include <iostream>


struct Column
{
    std::vector<int>* data;
    int numRows;

    Column(int);
    Column(int, std::vector<int>*);
    ~Column();
};

struct DataFrame
{
    Column** data;
    int numColumns;
    
    DataFrame(int);
    DataFrame(int, Column**);

    void show();
    ~DataFrame();
};

#endif