#include "columnar.h"

Column::Column(int n) {
    numRows = n;
    data = new std::vector<int>(n);
}

Column::Column(int n, std::vector<int>* input) {
    numRows = n;
    data = input;
}

Column::~Column() {
    delete data;
}


DataFrame::DataFrame(int n) {
    numColumns = n;
    data = new Column*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new Column(n);
    }
}

DataFrame::DataFrame(int n, Column** input) {
    numColumns = n;
    data = input;
}

void DataFrame::show() {
    if (numColumns == 0 || data == nullptr || data[0] == nullptr || data[0]->data == nullptr)
        return;

    int numRows = data[0]->data->size();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            Column* c = data[j];
            int val = (*c->data)[i];
            std::cout << val;
            if (j < numColumns - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

DataFrame::~DataFrame() {
    for (int i = 0; i < numColumns; i++) {
        delete data[i];
    }
    delete[] data;
}
