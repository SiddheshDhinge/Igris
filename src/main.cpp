#include <iostream>
#include <vector>
#include <map>
#include "functions/arithmatic.h"
#include "functions/aggregate.h"
#include "format/columnar.h"
#include "datasource/csv/io.h"
#include "datasource/igris/io.h"
#include "functions/filter/filter.h"


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

    std::string input_path = config["input"]; // ".//data//data.csv";
    std::string output_path = config["output"]; // ".//op.csv";
    
    std::vector<DataTypeEnum> schema = {DataTypeEnum::INT_32, DataTypeEnum::INT_32, DataTypeEnum::INT_32, DataTypeEnum::INT_32, DataTypeEnum::INT_32};

    DataFrame* df = read_csv(input_path, schema);
    // df->show();
    
    df->addColumn(Sum<int32, int32>()(df->data[0], df->data[1]), "col_sum", DataTypeEnum::INT_32);
    df->addColumn(Substract<int32, int32>()(df->data[0], df->data[1]), "col_sub", DataTypeEnum::INT_32);
    df->addColumn(Multiply<int32, int32>()(df->data[0], df->data[1]), "col_mul", DataTypeEnum::INT_32);
    df->addColumn(Divide<int32, int32>()(df->data[0], df->data[1]), "col_div", DataTypeEnum::INT_32);
    
    int32 res1 = count(df->data[0]);
    int32 res2 = min<int32>(df->data[1]);
    int32 res3 = max<int32>(df->data[2]);
    int32 res4 = avg<int32>(df->data[3]);
    int32 res5 = sum<int32>(df->data[4]);
    std::cout<<"Cnt: "<<res1.value<<std::endl;
    std::cout<<"Min: "<<res2.value<<std::endl;
    std::cout<<"Max: "<<res3.value<<std::endl;
    std::cout<<"Avg: "<<res4.value<<std::endl;
    std::cout<<"Sum: "<<res5.value<<std::endl;

    // df->show();

    // std::cout<<df->numRows()<<std::endl;
    // std::string op = "op.csv";
    // write_csv(df, op);

    write_igris(df, output_path);
    DataFrame* df2 = read_igris(output_path);
    
    int32 res_1 = count(df2->data[0]);
    int32 res_2 = min<int32>(df2->data[1]);
    int32 res_3 = max<int32>(df2->data[2]);
    int32 res_4 = avg<int32>(df2->data[3]);
    int32 res_5 = sum<int32>(df2->data[4]);
    std::cout<<"Cnt: "<<res_1.value<<std::endl;
    std::cout<<"Min: "<<res_2.value<<std::endl;
    std::cout<<"Max: "<<res_3.value<<std::endl;
    std::cout<<"Avg: "<<res_4.value<<std::endl;
    std::cout<<"Sum: "<<res_5.value<<std::endl;

    std::string filterString = "(a + b) > c AND (c IN ('10',20,30)) AND d = 'fit' OR e = 10";
    filter(df, filterString);
    

    return 0;
}