#include "sum.h"

Column* sum(Column* a, Column* b) {
    int numRows = a->numRows();
    Column* res = new Column(numRows);

    for(int i=0; i<numRows; i++) {
        int valueA = ((intw*)(*a->data)[i])->get();
        int valueB = ((intw*)(*b->data)[i])->get();
        
        int valueRes = valueA + valueB;
        bool sign = (valueRes < 0) ? true : false;
        (*res->data)[i] = new intw(valueRes, sign);
    }

    return res;
}