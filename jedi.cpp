#include <iostream>
#include "jedi.h"
#include "myString.h"
#include <fstream>

using std::cout; using std::cin; using std:: endl;
const double DEFAULT_POWER_CHANGE = 0.5;

void Jedi::setJedi (const MyString& _name, int _age, const Rank& _rank, const MyString& _saberColor, double _power) {
    name = _name;
    age = _age; 
    rank = _rank; 
    saberColor = _saberColor;
    power = _power;
}

void Jedi::readJedi (std::istream& is) {
    cout << "What's the name of the jedi? "; is >> name;
    cout << "What's their age? "; is >> age;
    cout << "What's their rank? "; is >> rank;
    cout << "What's the color of their saber? "; is >> saberColor;
    cout << "How much power do they hold ? "; is >> power;
}

void Jedi::promoteJedi (double multiplier) {
    rank.rankUp();
    if (multiplier > 0) {
        power *= (1 + multiplier);
    }
    else {
        cout << "Multiplier must be a positive double number!\nPower increased by 50% /default/.";
        power *= (1 + DEFAULT_POWER_CHANGE);
    }
}

void Jedi::demoteJedi (double multiplier) {
    rank.demote();
    if (multiplier > 0) {
        power *= (1 - multiplier);
    }
    else {
        cout << "Multiplier must be a positive double number!\nPower decreased by 50% /default/.";
        power *= (1 - DEFAULT_POWER_CHANGE);
    }
}

bool Jedi::operator != (const Jedi& other) {
    if (name != other.name || age != other.age || rank != other.rank || saberColor != other.saberColor || power != other.power) {
        return true;
    }
    return false;
}

std::ostream& operator << (std::ostream& os, const Jedi& jedi) {
    os << jedi.name << '|' << jedi.age << '|' << jedi.rank << '|' << jedi.saberColor << '|' << jedi.power << '\n';
    return os;
}
std::istream& operator >> (std::istream& is, Jedi& jedi) {
    is >> jedi.name;
    is >> jedi.age; is.get();
    is >> jedi.rank;
    is >> jedi.saberColor;
    is >> jedi.power; is.get();
    return is;
}

void Jedi::print (std::ostream& os) const {
    os << "The jedi " << name << " , " << age << ", ";
    rank.print(os);
    os << " ,wields a " << saberColor << " saber and beholds " << power << "power.";
}

void Jedi::readFromFile(const char* name) {
    std::ifstream in;
    in.open(name);
    if (in) {
        in >> *this;
    }
    in.close();
}

bool Jedi::writeToFile(const char* name) {
    std::ofstream out;
    out.open(name);
    if (!out) {
        return false;
    }
    out << *this;
    out.close();
    return true;
}