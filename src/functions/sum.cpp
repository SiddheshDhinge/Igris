#include "sum.h"

Column* sum(Column* a, Column* b) {
    int numRows = a->numRows();
    Column* res = new Column(numRows);

    for(int i=0; i<numRows; i++) {
        (*res->data)[i] = (*a->data)[i] + (*b->data)[i];
    }

    return res;
}