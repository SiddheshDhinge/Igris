#ifndef CONF_H
#define CONF_H


struct Conf {
    int igrisRowGroupBatchSize = 256;

    Conf() {
        this->igrisRowGroupBatchSize = 256;
    }
};

extern Conf conf;


#endif