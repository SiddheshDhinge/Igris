#include "columnar.h"


Column::Column(std::vector<int>* input) {
    data = input;
}

Column::Column(int numRows) {
    this->data = new std::vector<int>(numRows);
}

Column::~Column() {
    delete data;
}

int Column::numRows() {
    return this->data->size();
}


DataFrame::DataFrame(int numRows, int numColumns, std::vector<std::string>* headers) {
    this->data = new std::vector<Column*>(numColumns, nullptr);
    this->headers = headers;
    for(int i=0; i<numColumns; i++)
    {
        (*this->data)[i] = new Column(numRows);
    }
}

DataFrame::DataFrame(int n, std::vector<Column*>* input, std::vector<std::string>* headers) {
    this->headers = headers;
    this->data = input;
}

DataFrame::~DataFrame() {
    int numColumns = this->numColumns();
    for (int i = 0; i < numColumns; i++) {
        delete (*this->data)[i];
    }
    delete data;
}

void DataFrame::show() {
    int numColumns = this->numColumns();
    if (numColumns == 0 || data == nullptr || (*data)[0] == nullptr)
        return;

    for(int j = 0; j < (int)this->headers->size(); j++) {
        std::cout << std::setw(show_width) << (*this->headers)[j];
        if (j < numColumns - 1)
            std::cout << " | ";
    }
    std::cout<<std::endl;

    int numRows = (*data)[0]->numRows();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            Column* c = (*data)[j];
            int val = (*c->data)[i];
            std::cout << std::setw(show_width) << val;
            if (j < numColumns - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

int DataFrame::numColumns() {
    return this->data->size();
}

void DataFrame::addColumn(Column* newColumn, std::string header_name) {
    this->data->push_back(newColumn);
    this->headers->push_back(header_name);
}
