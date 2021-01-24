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

    // Ask user if they want to give cardinality manually
    unsigned int carda = 0;
    unsigned int cardb = 0;

    std::cout << "Do you want to specify cardinality for two sets? (Y/N): ";
    std::cin.ignore();
    std::cin.clear();
    bool manual = true;
    if (std::getchar() != 'Y') {
        manual = false;
        goto begin;
    }

    std::cout << "Input first unsigned cardinality: ";
    std::cin >> buffer;
    carda = strtoul(buffer.c_str(), nullptr, 10);
    std::cout << "Input second unsigned cardinality: ";
    std::cin >> buffer;
    cardb = strtoul(buffer.c_str(), nullptr, 10);

    // Show user some warning
    std::cout << "Note: if you are using card bigger than 2**power without "
              << "multiset support, the count of sets will be same as Universe."
              << std::endl << std::endl;

    begin:
    Set<Gray> universe = universal(power);
    Set<Gray> parta = random(power, carda, manual);
    Set<Gray> partb = random(power, cardb, manual);

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
