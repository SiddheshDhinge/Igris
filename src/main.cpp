#include <iostream>
#include <vector>
#include "functions/sum.h"
#include "format/columnar.h"
#include "reader/csv/reader.h"

int main(int argc, char** args) {
    std::string path = ".\\data\\data.csv";
    DataFrame* df = read_csv(&path);
    df->show();
    
    Column* res = sum(df->data[0], df->data[1]);
    // std::cout<<res->numRows<<std::endl;
    // std::cout<<res->data->size()<<std::endl;
    for(int i=0; i<(int)res->data->size(); i++) {
        std::cout<<(*res->data)[i]<<std::endl;
    }
    return 0;
}