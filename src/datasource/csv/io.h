#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include "../../format/columnar.h"


DataFrame* read_csv(std::string* path, std::vector<DataTypeEnum> schema);
// DataFrame* read_csv_buffered(std::string* path);

bool write_csv(DataFrame* df, std::string* path);

#endif