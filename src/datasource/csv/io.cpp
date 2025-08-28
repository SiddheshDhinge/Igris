#include "io.h"


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

// intw* bytetoint(char* bytes, int size, intw* old = nullptr) {
//     if(size == 0)
//         return new intw(0, false);
        
//     bool neg = false;
//     int cur = 0;
//     int ans = 0;

//     if(old != nullptr) {
//         ans = old->value;
//         neg = old->sign;
//     }
//     else if(bytes[cur] == '-')
//     {
//         neg = true;
//         cur++;
//     }

//     while(cur < size) {
//         ans = ans * 10 + (bytes[cur] - '0');
//         cur++;
//     }

//     return new intw(ans, neg);
// }

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

DataFrame* read_csv(std::string &path, std::vector<DataTypeEnum> schema) {
    std::ifstream file(path);

    if(!file)
        return nullptr;
    
    std::string str;

    //first line is field headers
    std::getline(file, str);
    std::vector<std::string>* headers = parse_headers(str);
    
    int numColumns = headers->size();
    std::vector<Column<int32>*> data = std::vector<Column<int32>*>(numColumns, nullptr);
    for(int i=0; i<numColumns; i++)
        data[i] = new Column<int32>(0);

    int curColumn = 0;
    int curRow = 0;

    while(std::getline(file, str)) {
        // parse data row by row
        curRow++;
        int last = 0;
        for(int i=0; i < (int)str.size(); i++) {
            if(str[i] == ',')
            {
                std::string value = str.substr(last, i - last);
                int intvalue = stringtoint(&value);
                data[curColumn]->data.push_back(int32(intvalue));
                // data[curColumn]->data.push_back(int32(intvalue));
                last = i + 1;
                curColumn++;
            }
        }
        // parse from last to str size
        std::string value = str.substr(last, str.size() - last);
        int intvalue = stringtoint(&value);
        data[curColumn]->data.push_back(int32(intvalue));

        curColumn = 0;
    }

    std::vector<ColumnBase*> baseData;
    for (auto c : data) {
        baseData.push_back(c);
    }
    std::cout<<"parsed "<<curRow<< " rows"<<std::endl;

    DataFrame* df = new DataFrame(baseData, *headers, schema);
    return df;
}

bool write_csv(DataFrame* df, std::string &path) {
    std::ofstream file(path, std::ios::binary);
    if(!file)
        return false;

    char buffer[4*1024*1024];
    int buffer_cur = 0;
    for(int i=0; i < df->numColumns(); i++) {
        int j = 0;
        while(j < (int) df->headers[i].size())
            buffer[buffer_cur++] = df->headers[i][j++];

        buffer[buffer_cur++] = (i < (df->numColumns() - 1)) ? ',' : '\n';
    }

    file.write(buffer, buffer_cur);

    for(int i=0; i<df->numRows(); i++)
    {
        buffer_cur = 0;
        for(int j=0; j<df->numColumns(); j++) {
            Column<int32>* c = static_cast<Column<int32>*>(df->data[j]);
            std::string val = std::to_string(c->data[i].value);
            int k = 0;
            while(k < (int) val.size())
                buffer[buffer_cur++] = val[k++];

            buffer[buffer_cur++] = (j < (df->numColumns() - 1)) ? ',' : '\n';
        }

        file.write(buffer, buffer_cur);
    }
    std::cout<<"written "<<df->numRows()<<" rows to "<<path<<std::endl;
    
    return true;
}



// /* 
// Copies from src to dst
// assumes that dst has end - start allocated
// */
// void cp(char* src, char* dst, int start, int end) {
//     int i = start;
//     while(i < end) {
//         dst[i - start] = src[i];
//         i++;
//     }
// }

// DataFrame* read_csv_buffered(std::string* path) {
//     std::ifstream file(*path, std::ios::binary);

//     if(!file)
//         return nullptr;
    
//     std::string str;

//     //first line is field headers
//     std::getline(file, str);
//     std::vector<std::string>* headers = parse_headers(str);
    
//     int numColumns = headers->size();
//     std::vector<Column*>* data = new std::vector<Column*>(numColumns, nullptr);
//     for(int i=0; i<numColumns; i++)
//         (*data)[i] = new Column(0);

//     const static int BYTES_TO_READ = 512;
//     char buffer[BYTES_TO_READ] = {};
//     int curColumn = 0;
//     intw* lastval = new intw(0, false);

//     while(file.read(buffer, BYTES_TO_READ)) {
//         // parse data byte by byte
//         std::streamsize bytesRead = file.gcount();
//         int curByte = 0;
//         int lastSep = 0;
//         while(curByte < bytesRead) {
//             if(buffer[curByte] == ',' || buffer[curByte] == '\n') {
//                 char* value = new char[curByte - lastSep];
//                 cp(buffer, value, lastSep + 1, curByte);
//                 intw* completeVal = bytetoint(value, curByte - lastSep, lastval);
//                 (*data)[curColumn]->data->push_back(completeVal);
//                 lastval->value = 0, lastval->sign = false;
//                 lastSep = curByte;
//                 curColumn++;
//             }
//             curByte++;
//         }

//         char* value = new char[curByte - lastSep];
//         cp(buffer, value, lastSep + 1, curByte);
//         lastval = bytetoint(value, curByte - lastSep, lastval);
//         curColumn = 0;
//     }

//     DataFrame* df = new DataFrame(numColumns, data, headers);
//     return df;
// }