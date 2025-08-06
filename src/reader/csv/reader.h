#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include "../../format/columnar.h"


DataFrame* read_csv(std::string* path);

#endif