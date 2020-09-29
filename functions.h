#ifndef GRAYSET_FUNCTIONS_H
#define GRAYSET_FUNCTIONS_H

#include "header.h"
#include "set.h"
#include "binary.h"
#include "gray.h"
#include "couple.h"

// Show all contents in HashSet
template <typename T>
void show(const char* label, const Set<T>& set, unsigned int line = 4) {
    std::cout << label << ": {" << std::endl;
    unsigned int lc = line;
    auto size = set.count() - 1;

    for (auto value: set) {
        if (lc-- == line)
            std::cout << '\t';

        std::cout << value;
        if (size > 0)
            std::cout << ", ";

        if (lc == 0) {
            lc = line;
            std::cout << std::endl;
        }
        size--;
    }
    if (lc != line)
        std::cout << std::endl;
    std::cout << '}' << std::endl;
}

// Generate Gray Set with wpecific power
Set<Gray> universal(unsigned int);
Set<Gray> random(unsigned int);

#endif //GRAYSET_FUNCTIONS_H
