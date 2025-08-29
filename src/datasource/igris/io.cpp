#include "io.h"

template<typename T>
void writeColumnBlock(std::ofstream& file, Column<T>* col, int cur, int K, int numRows) {
    int start = cur * K;
    int end = std::min(numRows, (cur + 1) * K);

    for (int j = start; j < end; j++) {
        file.write(reinterpret_cast<const char*>(&col->data[j].value), sizeof(T));
    }
}


void writeStringColumnBlock(std::ofstream &file, Column<string>* col, int cur, int K, int numRows) {
    int start = cur * K;
    int end = std::min(numRows, (cur + 1) * K);

    // LEN => first 4 bytes = string length
    // next LEN bytes = string value
    
    for(int j = start; j < end; j++) {
        std::string &value = col->data[j].value;
        int len = static_cast<int>(value.size());
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(value.c_str(), len);
    }
}


bool write_igris(DataFrame* df, std::string& path) {
    std::ofstream file(path, std::ios::binary);
    
    if(!file.is_open()) {
        return false;
    }

    int K = conf.igrisRowGroupBatchSize;

    // write total rows and total columns
    int numRows = df->numRows();
    int numColumns = df->numColumns();

    file.write((const char*) &numRows, sizeof(int));
    file.write((const char*) &numColumns, sizeof(int));
    
    // write headers
    for(int i=0; i<df->numColumns(); i++) {
        std::string columnName = df->headers[i];
        int len = columnName.size();
        
        file.write((const char*) &len, sizeof(int));
        file.write(columnName.c_str(), len);

        DataTypeEnum headerType = DataTypeEnum::INT_8;
        if(DataTypeEnum::INT_8 == df->schema[i]) {
            headerType = DataTypeEnum::INT_8;
        }
        else if(DataTypeEnum::INT_16 == df->schema[i]) {
            headerType = DataTypeEnum::INT_16;
        }
        else if(DataTypeEnum::INT_32 == df->schema[i]) {
            headerType = DataTypeEnum::INT_32;
        }
        else if(DataTypeEnum::INT_64 == df->schema[i]) {
            headerType = DataTypeEnum::INT_64;
        }
        else if(DataTypeEnum::STRING == df->schema[i]) {
            headerType = DataTypeEnum::STRING;
        }
        file.write((const char*) &headerType, sizeof(headerType));
    }

    // write data

    int totalBlocks = (df->numRows() / K) + (df->numRows() % K != 0);
    
    for(int j= 0; j< totalBlocks; j++) {        
        for(int i=0; i<df->numColumns(); i++)
        {
            switch (df->schema[i]) {
                case DataTypeEnum::INT_8:
                    writeColumnBlock(file, static_cast<Column<int8>*>(df->data[i]), j, K, df->numRows());
                    break;
                case DataTypeEnum::INT_16:
                    writeColumnBlock(file, static_cast<Column<int16>*>(df->data[i]), j, K, df->numRows());
                    break;
                case DataTypeEnum::INT_32:
                    writeColumnBlock(file, static_cast<Column<int32>*>(df->data[i]), j, K, df->numRows());
                    break;
                case DataTypeEnum::INT_64:
                    writeColumnBlock(file, static_cast<Column<int64>*>(df->data[i]), j, K, df->numRows());
                    break;
                case DataTypeEnum::STRING:
                    writeStringColumnBlock(file, static_cast<Column<string>*>(df->data[i]), j, K, df->numRows());
                    break;
            }
        }
    }

    return true;
}

template<typename T>
void readColumnBlock(std::ifstream& file, Column<T>* column, int cur, int K, int numRows) {
    int start = cur * K;
    int end = std::min(numRows, (cur + 1) * K);

    T val;
    for (int j = start; j < end; j++) {
        file.read((char*) &val.value, sizeof(val.value));
        column->data[j] = val;
    }
}

DataFrame* read_igris(std::string& path) {
    std::ifstream file(path, std::ios::binary);
    
    int K = conf.igrisRowGroupBatchSize;

    // read total rows and columns
    int numRows = 0;
    int numColumns = 0;

    file.read((char*) &numRows, sizeof(int));
    file.read((char*) &numColumns, sizeof(int));

    // read headers

    std::vector<std::string> headers;
    std::vector<DataTypeEnum> schema;
    char buffer[4094 * 1024];
    for(int i=0; i<numColumns; i++) {
        int len = 0;
        DataTypeEnum dteType = DataTypeEnum::INT_8;
        file.read((char*) &len, sizeof(int));
        file.read(buffer, len);

        std::string columnName(buffer, len);
        headers.push_back(columnName);

        file.read((char*) &dteType, sizeof(DataTypeEnum));
        schema.push_back(dteType);
    }

    int totalBlocks = (numRows / K) + (numRows % K != 0);
    std::vector<ColumnBase*> data(numColumns, nullptr);

    for(int i=0; i<numColumns; i++)
    {
        switch (schema[i])
        {
            case DataTypeEnum::INT_8:
                data[i] = new Column<int8>(numRows);
                break;
            case DataTypeEnum::INT_16:
                data[i] = new Column<int16>(numRows);
                break;
            case DataTypeEnum::INT_32:
                data[i] = new Column<int32>(numRows);
                break;
            case DataTypeEnum::INT_64:
                data[i] = new Column<int64>(numRows);
                break;
            case DataTypeEnum::STRING:
                data[i] = new Column<string>(numRows);
                break;
        }
    }

    for(int i=0; i<totalBlocks; i++)
    {
        for(int j=0; j<numColumns; j++) {
            switch(schema[j]) {
                case DataTypeEnum::INT_8:
                    readColumnBlock(file, static_cast<Column<int8>*>(data[j]), i, K, numRows);
                    break;
                case DataTypeEnum::INT_16:
                    readColumnBlock(file, static_cast<Column<int16>*>(data[j]), i, K, numRows);
                    break;
                case DataTypeEnum::INT_32:
                    readColumnBlock(file, static_cast<Column<int32>*>(data[j]), i, K, numRows);
                    break;
                case DataTypeEnum::INT_64:
                    readColumnBlock(file, static_cast<Column<int64>*>(data[j]), i, K, numRows);
                    break;
                case DataTypeEnum::STRING:
                    readColumnBlock(file, static_cast<Column<string>*>(data[j]), i, K, numRows);
                    break;
            }
        }
    }
    
    DataFrame* df = new DataFrame(data, headers, schema);
    return df;
}
