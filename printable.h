#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>

class Printable {
    public:
    virtual void print(std::ostream& os = std::cout) const = 0;
    virtual ~Printable() {}

    void println(std::ostream& os = std::cout) const {
        print(os);
        os << std::endl;
    }
};

#endif