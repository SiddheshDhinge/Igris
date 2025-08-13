#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>
enum class DataTypeEnum {
    INT_8,
    INT_16,
    INT_32,
    INT_64,
    STRING
};

struct DataTypeBase {};

struct int_: public DataTypeBase {
public:
    int value;
    int_(int value);
};

struct int8: public int_ {
public:
    int8(int value):int_(value) {};
    int8():int_(0) {};
};
struct int16: public int_ {
public:
    int16(int value):int_(value) {};
    int16():int_(0) {};
};
struct int32: public int_ {
public:
    int32(int value):int_(value) {};
    int32():int_(0) {};
};
struct int64: public int_ {
public:
    int64(int value):int_(value) {};
    int64():int_(0) {};
};

struct string: public DataTypeBase {
public:
    std::string value;
    string(std::string value);
    string();
};

#endif