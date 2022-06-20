#ifndef JEDI_H
#define JEDI_H

#include <iostream>
#include "myString.h"
#include "rank.h"
#include "printable.h"

class Jedi : public Printable {
    MyString name;
    int age;
    Rank rank;
    MyString saberColor;
    double power;
    public:
    Jedi ();
    Jedi(   const MyString& _name, int _age, const Rank& _rank, const MyString& _saberColor, double _power) : 
            name(_name), rank(_rank), age(_age), saberColor(_saberColor), power(_power) {};
    void setJedi (  const MyString& _name, int _age, const Rank& _rank, 
                    const MyString& _saberColor, double _power);
    void readJedi (std::istream& is = std::cin);
    void promoteJedi (double multiplier);
    void demoteJedi (double multiplier);
    bool operator != (const Jedi& other);
    friend class Planet;
    friend std::ostream& operator << (std::ostream& os, const Jedi& jedi);
    friend std::istream& operator >> (std::istream& is, Jedi& jedi);
    void print(std::ostream& os = std::cout) const override;
    void readFromFile(const char* name, Jedi& jedi);
    bool writeToFile(const char* name, Jedi& jedi);
    
};

#endif