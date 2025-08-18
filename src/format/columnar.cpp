#include "columnar.h"

template <typename T>
Column<T>::Column(std::vector<T> input)
{
    data = input;
}

template <typename T>
Column<T>::Column(int numRows)
{
    this->data = std::vector<T>(numRows);
}

template <typename T>
Column<T>::~Column() = default;


template <typename T>
int Column<T>::numRows()
{
    return static_cast<int>(data.size());
}


DataFrame::DataFrame(int numRows, int numColumns, std::vector<std::string> headers, std::vector<DataTypeEnum> schema) {
    this->data = std::vector<ColumnBase*>(numColumns, nullptr);
    this->headers = headers;
    this->schema = schema;
    for(int i=0; i<numColumns; i++)
    {
        switch (schema[i])
        {
            case DataTypeEnum::INT_8:
                this->data[i] = new Column<int8>(numRows);
                break;
            
            case DataTypeEnum::INT_16:
                this->data[i] = new Column<int16>(numRows);
                break;

            case DataTypeEnum::INT_32:
                this->data[i] = new Column<int32>(numRows);
                break;
                
            case DataTypeEnum::INT_64:
                this->data[i] = new Column<int64>(numRows);
                break;
                
            case DataTypeEnum::STRING:
                this->data[i] = new Column<string>(numRows);
                break;
        }
    }
}

DataFrame::DataFrame(std::vector<ColumnBase*> &input, std::vector<std::string> headers, std::vector<DataTypeEnum> schema) {
    this->headers = headers;
    this->data = input;
    this->schema = schema;
}

DataFrame::~DataFrame() {
    int numColumns = this->numColumns();
    for (int i = 0; i < numColumns; i++) {
        switch(schema[i]) {
            case DataTypeEnum::INT_8:
            case DataTypeEnum::INT_16:
            case DataTypeEnum::INT_32:
            case DataTypeEnum::INT_64:
                delete static_cast<Column<int_>*>(this->data[i]);
                break;
            case DataTypeEnum::STRING:
                delete static_cast<Column<string>*>(this->data[i]);
                break;
        }
    }
}

void DataFrame::show() {
    int numColumns = this->numColumns();
    int numRows = this->numRows();

    if (numColumns == 0 || numRows == 0)
        return;

    for(int j = 0; j < (int)this->headers.size(); j++) {
        std::cout << std::setw(show_width) << this->headers[j];
        if (j < numColumns - 1)
            std::cout << " | ";
    }
    std::cout<<std::endl;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            std::cout<<std::setw(show_width);
            switch(this->schema[j]) {
                case DataTypeEnum::INT_8:
                case DataTypeEnum::INT_16:
                case DataTypeEnum::INT_32:
                case DataTypeEnum::INT_64: {
                    Column<int_>* c1 = (Column<int_>*) data[j];
                    std::cout<<c1->data[i].value;
                    break;
                }
                case DataTypeEnum::STRING: {
                    Column<string>* c2 = (Column<string>*) data[j];
                    std::cout<<c2->data[i].value;
                    break;
                }
            }
            if (j < numColumns - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

int DataFrame::numColumns() {
    return this->data.size();
}

int DataFrame::numRows() {
    if(numColumns() == 0)
        return 0;
    return this->data[0]->numRows();
}

void DataFrame::addColumn(ColumnBase* newColumn, std::string header_name, DataTypeEnum column_schema) {
    this->data.push_back(newColumn);
    this->headers.push_back(header_name);
    this->schema.push_back(column_schema);
}
