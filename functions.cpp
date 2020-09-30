#include "functions.h"


static std::default_random_engine engine(std::time(nullptr));
static std::uniform_real_distribution<double> uniform(0, 1);

// Hash Template Function Specialization for Different Types of Values
template <>
unsigned int hash<Binary>(size_t maxsize, const Binary& bin) {
    return bin.decimal() % maxsize;
}

template <>
unsigned int hash<Gray>(size_t maxsize, const Gray& bin) {
    return bin.decimal() % maxsize;
}

template <>
unsigned int hash<char>(size_t maxsize, const char& chr) {
    return chr % maxsize;
}

template <>
unsigned int hash<Couple<char, char>>(size_t maxsize, const Couple<char, char>& couple) {
    return hash(maxsize, (char)(couple.first() + couple.second()));
}

template <>
unsigned int hash<Couple<Gray, Gray>>(size_t maxsize, const Couple<Gray, Gray>& couple) {
    return (hash(maxsize, couple.first()) + hash(maxsize, couple.second())) % maxsize;
}

// Friend functions for class Binary
std::ostream& operator<<(std::ostream& out, const Binary& bin) {
    for (size_t _ = bin.size() - 1; _ != 0; _--)
        out << bin.get(_);
    out << bin.get(0);
    return out;
}

bool operator==(const Binary& bina, const Binary& binb) {
    if (bina.size() != binb.size())
        return false;

    for (size_t _ = 0; _ < bina._size; _++)
        if (bina.get(_) != binb.get(_))
            return false;
    return true;
}

Set<Gray> universal(unsigned int power) {
    Set<Gray> set(16);
    std::cout << "Value" << '\t' << "Gray" << std::endl;
    std::cout << "------------" << std::endl;

    for (unsigned int value = 0; value < (0x1u << power); value++) {
        Gray gray(power);
        gray.import<short>(value);
        std::cout << value << "\t" << gray << std::endl;
        set.add(gray);
    }

    std::cout << std::endl;
    return set;
}

Set<Gray> random(unsigned int power) {
    Set<Gray> set(16);
    for (unsigned int value = 0; value < (0x1u << power); value++) {
        Gray gray(power);
        gray.import<short>(value);
        if (uniform(engine) > 0.5)
            set.add(gray);
    }
    return set;
}
