#ifndef GRAYSET_COUPLE_H
#define GRAYSET_COUPLE_H

#include "header.h"

template <typename Ta, typename Tb>
class Couple {
private:
    Ta* _value_a;
    Tb* _value_b;

public:
    Couple() = delete;
    explicit Couple(const Ta& valuea, const Tb& valueb) {
        this->_value_a = new Ta(valuea);
        this->_value_b = new Tb(valueb);
    }

    Couple(const Couple<Ta, Tb>& couple) {
        this->_value_a = new Ta(*couple._value_a);
        this->_value_b = new Tb(*couple._value_b);
    }

    Ta& first() const { return *this->_value_a; }
    Tb& second() const { return *this-> _value_b; }

    ~Couple() {
        delete this->_value_a;
        delete this->_value_b;
    }

    friend std::ostream& operator<<(std::ostream& out, const Couple<Ta, Tb>& couple) {
        std::cout << '(' << couple.first() << ", " << couple.second() << ')';
        return out;
    }

    friend bool operator==(const Couple<Ta, Tb>& couplea, const Couple<Ta, Tb>& coupleb) {
        return (couplea.first() == coupleb.first() && couplea.second() == coupleb.second());
    }
};

#endif //GRAYSET_COUPLE_H
