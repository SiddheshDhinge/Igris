#include "reader.h"


int stringtoint(std::string* str) {
    bool neg = false;
    int cur = 0;
    if((*str)[cur] == '-') {
        neg = true;
        cur++;
    }
    
    int ans = 0;
    while(cur < (int)str->size()) {
        ans = ans * 10 + (*str)[cur] - '0';
        cur++;
    }

    ans = (neg) ? -ans : ans;
    return ans;
}

std::vector<std::string>* parse_headers(std::string header_line) {
    int back = 0;
    int cur = 0;

    std::vector<std::string> *headers = new std::vector<std::string>();
    while(cur != (int)header_line.size()) {
        if(header_line[cur] == ',') {
            headers->push_back(header_line.substr(back, cur - back));
            back = cur + 1;
        }
        cur++;
    }

    // parse last field
    headers->push_back(header_line.substr(back, cur - back));
    return headers;
}

DataFrame* read_csv(std::string* path) {
    std::ifstream file(*path);

    if(!file)
        return nullptr;
    
    std::string str;

    //first line is field headers
    std::getline(file, str);
    std::vector<std::string>* headers = parse_headers(str);
    
    int numColumns = headers->size();
    std::vector<Column*>* data = new std::vector<Column*>(numColumns, nullptr);
    for(int i=0; i<numColumns; i++)
        (*data)[i] = new Column(0);

    int curColumn = 0;
    while(std::getline(file, str)) {
        // parse data row by row
        int last = 0;
        for(int i=0; i < (int)str.size(); i++) {
            if(str[i] == ',')
            {
                std::string value = str.substr(last, i - last);
                int intvalue = stringtoint(&value);
                (*data)[curColumn]->data->push_back(intvalue);
                last = i + 1;
                curColumn++;
            }
        }
        // parse from last to str size
        std::string value = str.substr(last, str.size() - last);
        int intvalue = stringtoint(&value);
        (*data)[curColumn]->data->push_back(intvalue);

        curColumn = 0;
    }

    DataFrame* df = new DataFrame(numColumns, data, headers);
    return df;
}