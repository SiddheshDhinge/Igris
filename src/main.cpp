#include <iostream>
#include <vector>
#include <map>
#include "functions/sum.h"
#include "format/columnar.h"
#include "reader/csv/reader.h"


int main(int argc, char** args) {
    std::map<std::string, std::string> config;

    for(int i=1; i<argc; i++) {
        std::string kv = std::string(args[i]);
        int split = 0;
        while(kv[split] != '=')
            split++;
        
        std::string key = kv.substr(0, split);
        std::string value = kv.substr(split + 1, kv.size() - split);
        config[key] = value;
        std::cout<<key<<" -> "<<value<<std::endl;
    }

    std::string path = config["path"]; // ".//data//data.csv";

    DataFrame* df = read_csv(&path);
    // df->show();
    
    Column* res = sum((*df->data)[0], (*df->data)[1]);

    df->addColumn(res, "col_sum");
    df->show();

    return 0;
}