#ifndef GRAYSET_GRAY_H
#define GRAYSET_GRAY_H

#include "binary.h"

class Gray: public Binary {
public:
    using Binary::Binary;

public:
    template <typename VT>
    void import(VT value) {
        this->decimal<VT>(value ^ (value >> 1));
    }
};

#endif //GRAYSET_GRAY_H
