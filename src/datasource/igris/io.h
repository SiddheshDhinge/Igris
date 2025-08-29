#ifndef IGRIS_IO_H
#define IGRIS_IO_H

#include <string>
#include <fstream>
#include "../../format/columnar.h"
#include "../../utils/conf.h"


bool write_igris(DataFrame* df, std::string& path);

DataFrame* read_igris(std::string& path);


#endif