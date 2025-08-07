#include "datatype.h"


intw::intw(int value, bool sign){
    this->value = value;
    this->sign = sign;
}

int intw::get() {
    return value * (sign ? -1 : 1);
}