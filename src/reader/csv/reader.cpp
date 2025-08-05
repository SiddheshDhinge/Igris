#include <iostream>
#include <fstream>
#include "../../format/columnar.h"


int stringtoint(std::string* str) {
    int ans = 0;
    for(int i=0; i<(int)str->size(); i++) {
        ans = ans * 10 + (*str)[i] - '0';
    }
    return ans;
}

DataFrame* read_csv(std::string* path) {
    std::ifstream file(*path);

    if(!file)
        return nullptr;
    
    std::string str;
    
    Column** data;
    int columns = 0;

    bool columnFlag = false;

    int curColumn = 0;
    while(std::getline(file, str)) {
        // figure out number of columns
        if(!columnFlag) {
            for(int i=0; i<(int)str.size(); i++) {
                if(str[i] == ',')
                    columns++;
            }
            columns++;
            data = new Column*[columns];
            for(int i=0; i<columns; i++) {
                data[i] = new Column(0);
            }
            columnFlag = true;
        }
        
        // parse row by row
        int last = 0;
        for(int i=0; i < (int)str.size(); i++) {
            if(str[i] == ',')
            {
                std::string value = str.substr(last, i - last);
                int intvalue = stringtoint(&value);
                data[curColumn]->data->push_back(intvalue);
                last = i + 1;
                curColumn++;
            }
        }
        // parse from last to str size
        std::string value = str.substr(last, str.size() - last);
        int intvalue = stringtoint(&value);
        data[curColumn]->data->push_back(intvalue);

        curColumn = 0;
    }

    DataFrame* df = new DataFrame(columns, data);
    return df;
}