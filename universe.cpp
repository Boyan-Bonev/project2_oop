#include <iostream>
#include "universe.h"
#include "planet.h"

const size_t DEFAULT_CAP = 4;
using std::cout; using std::cin; using std::endl;

void Universe::copy (const Universe& other) {
    capacity = other.capacity;
    size = other.size;
    planets = new Planet [capacity];
    for (int i = 0; i < size; i++) {
        planets[i] = other.planets[i];
    }
}

void Universe::doubleCap () {
    capacity *= 2;
    Planet* tempPlanets = new Planet [capacity];
    for (int i = 0; i < size; i++) {
        tempPlanets[i] = planets[i];
    }
    delete[] planets;
    planets = tempPlanets;
}

Universe::Universe() {
    size = 0; capacity = DEFAULT_CAP;
    planets = new Planet [capacity];
}

Universe::Universe(const Universe& other) {
    copy(other);
}

Universe& Universe::operator = (const Universe& other) {
    if (*this != other) {
        copy(other);
    }
    return *this;
}

Universe::~Universe() {
    delete[] planets;
}

void Universe::readUniverse(std::istream& is) {
    int count;
    cout << "How many planets does this universe have? "; is >> count;
    for (size; size < count; size++) {
        cout << "Enter planet" << size + 1 << ':' << endl;
        if (size == capacity) {
            doubleCap();
        }
        planets[size].readPlanet(is);
    }
}

void Universe::addPlanet(const MyString& planet_name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            cout << "Planet by the name of " << planet_name << "already exists!\n";
            return;
        }
    }
    if (size == capacity) {
        doubleCap();
    }
    planets[size++].readPlanet();
}

void Universe::createJedi(const MyString& planet_name, const MyString& jedi_name, 
                const Rank& jedi_rank,int jedi_age, const MyString&saber_color, double jedi_strength) 
{
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].createJedi(jedi_name, jedi_rank, jedi_age, saber_color, jedi_strength);
            return;
        }
    }
    cout << "No planet named" << planet_name << "exists in this universe!\n"; 
}

void Universe::removeJedi(const MyString& jedi_name, const MyString& planet_name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].removeJedi(jedi_name);
            return;
        }
    }
    cout << "No planet by the name of " << planet_name << "exists in this universe!\n";
}

void Universe::promoteJedi (const MyString& jedi_name, double multiplier) {
    for (int i = 0; i < size; i++) {
        if (planets[i].alreadyExists(jedi_name)) {
            planets[i].promoteJedi(jedi_name,multiplier);
            return;
        }
    }
    cout << "No jedi named" << jedi_name << "exists in this universe!\n";
}

void Universe::demoteJedi (const MyString& jedi_name, double multiplier) {
    for (int i = 0; i < size; i++) {
        if (planets[i].alreadyExists(jedi_name)) {
            planets[i].demoteJedi(jedi_name,multiplier);
            return;
        }
    }
    cout << "No jedi named" << jedi_name << "exists in this universe!\n";
}

void Universe::getStrongestJedi(const MyString& planet_name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].getStrongestJedi();
            return;
        }
    }
    cout << "No planet named" << planet_name << "exists in this universe!\n";
}

void Universe::getYoungestJedi (const MyString& planet_name, const Rank& jedi_rank) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].getYoungestJedi(jedi_rank);
            return;
        }
    }
    cout << "No planet named" << planet_name << "exists in this universe!\n";
}

void Universe::getMostUsedSaberColor (const MyString& planet_name, const Rank& jedi_rank) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].getMostUsedSaberColor(jedi_rank);
            return;
        }
    }
    cout << "No planet named" << planet_name << "exists in this universe!\n";
}

void Universe::getMostUsedSaberColor (const MyString& planet_name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == planet_name) {
            planets[i].getMostUsedSaberColor();
            return;
        }
    }
    cout << "No planet named" << planet_name << "exists in this universe!\n";
}

bool Universe::operator != (const Universe& other) {
    if (size != other.size || capacity != other.capacity) {
        return true;
    }
    for (int i = 0; i < size; i++) {
        if (planets[i] != other.planets[i]) {
            return true;
        }
    }
    return false;
}

void Universe::print(std::ostream& os) const {
    os << "This universe is formed from " << size << " planets";
    for (int i = 0; i < size; i++) {
        planets[i].println(os);
    }
}

std::ostream& operator << (std::ostream& os, const Universe& universe) {
    universe.print(os);
}

std::istream& operator >> (std::istream& is, Universe& universe) {
    universe.readUniverse(is);
}