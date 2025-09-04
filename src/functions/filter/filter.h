#ifndef FILTER_H
#define FILTER_H

#include "../../format/columnar.h"
#include <string>
#include <vector>


DataFrame* filter(DataFrame* df, std::string &filterString);


#endif