#include "functions.h"

static std::default_random_engine engine(std::time(nullptr));

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
    Set<Gray> set(16, true);
    std::cout << "Value" << '\t' << "Gray" << std::endl;
    std::cout << "------------" << std::endl;

    // Test for power of Zero
    if (power == 0) {
        std::cout << std::endl;
        return set;
    }

    for (unsigned int value = 0; value < (0x1u << power); value++) {
        Gray gray(power);
        gray.import<short>(value);
        std::cout << value << "\t" << gray << std::endl;
        set.add(gray);
    }

    std::cout << std::endl;
    return set;
}

Set<Gray> random(unsigned int power, unsigned int cardinality) {
    std::uniform_int_distribution<unsigned> uniform(0, 0x1u << power);

#ifdef MULTISET
    Set<Gray> set(16, false);
#else
    Set<Gray> set(16);
#endif

    // When user has specified cardinality
    bool manual = false;
    if (cardinality <= 0)
        cardinality = uniform(engine);
    else
        manual = true;

    if (manual and set.multiple())
        for (unsigned int index = 0; index < cardinality; index++) {
            Gray gray(power);
            gray.import<short>(uniform(engine));
            set.add(gray);
        }

    if (manual and not set.multiple())
        for (unsigned int value = 0; value < 0x1u << power && value < cardinality; value++) {
            Gray gray(power);
            gray.import<short>(value);
            set.add(gray);
        }

    if (not manual)
        for (unsigned int index = 0; index < cardinality; index++) {
            Gray gray(power);
            gray.import<short>(uniform(engine));
            set.add(gray);
        }

    return set;
}
