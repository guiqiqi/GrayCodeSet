#define DEBUG
#undef DEBUG
#define MAX_GRAY_POWER_INPUT 10
#define MIN_GRAY_POWER_INPUT 1

#include "functions.h"

int main(int argc, const char* argv[]) {

    input:
    unsigned int power;
    std::string buffer;
    std::cout << "Input power of Gray code ("
              << MIN_GRAY_POWER_INPUT << " - "
              << MAX_GRAY_POWER_INPUT << "): ";
    std::cin >> buffer;
    power = strtoul(buffer.c_str(), nullptr, 10);
    if (power < MIN_GRAY_POWER_INPUT || power > MAX_GRAY_POWER_INPUT) {
        std::cout << "Invalid power range." << std::endl;
        goto input;
    }

    Set<Gray> universe = universal(power);
    Set<Gray> parta = random(power);
    Set<Gray> partb = random(power);

    show("SU", universe);
    std::cout << "--------------------------" << std::endl;
    show("S1", parta);
    std::cout << "--------------------------" << std::endl;
    show("S2", partb);
    std::cout << "--------------------------" << std::endl;

    show("S1 & S2", parta.intersection(partb));
    show("S1 | S2", parta.union_(partb));
    show("S1 - S2", parta.difference(partb));
    show("S2 - S1", partb.difference(parta));
    show("S1 ^ S2", parta.symdiff(partb));
    show("SU \\ S1", parta.complement(universe));
    show("SU \\ S2", partb.complement(universe));
    show("S1 + S2", parta.sum(partb));
    show("S1 x S2", parta.product(partb));

    return 0;
}
