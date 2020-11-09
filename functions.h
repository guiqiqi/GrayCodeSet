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

    // Detect empty set
    if (set.count() == 0) {
        std::cout << '}' << std::endl;
        return;
    }

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

    // Show multiset analysis
    if (set.multiple()) {
        std::cout << "Multiple set analysing: " << std::endl;
        Vector<Couple<T, unsigned int>> result = set.analysis();

        Couple<T, unsigned int> first = result.index(0);

        unsigned int total = result.count();
        for (int index = 0; index < total; index++) {
            Couple<T, unsigned int> value = result.pop(0);
            const T& element = value.first();
            unsigned int count = value.second();
            std::cout << element << " - " << count << " times" << std::endl;
        }

        std::cout << std::endl;
    }
}

// Generate Gray Set with specific power
Set<Gray> universal(unsigned int);
Set<Gray> random(unsigned int, unsigned int = 0);

#endif //GRAYSET_FUNCTIONS_H
