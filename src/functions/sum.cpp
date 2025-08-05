#include <iostream>
#include <vector>
#include "../format/columnar.h"

Column* sum(Column* a, Column* b) {
    int n = a->data->size();
    Column* res = new Column(n);

    for(int i=0; i<n; i++) {
        (*res->data)[i] = (*a->data)[i] + (*b->data)[i];
    }

    return res;
}