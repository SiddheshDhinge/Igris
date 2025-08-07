#ifndef DATATYPE_H
#define DATATYPE_H

class datatype {

};

class intw: public datatype {
public:
    int value;
    bool sign;

    intw(int value, bool sign);

    int get();
};

#endif