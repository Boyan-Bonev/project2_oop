#include <iostream>
#include <cstring>
#include <fstream>
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

void Universe::printJedi (const MyString& name) const {
    for (int i = 0; i < size; i++) {
        if (planets[i].alreadyExists(name)) {
            for (int j = 0; j < size; j++) {
                if (planets[i].jedis[j].name == name) {
                    planets[i].jedis[j].print();
                }
            }
        }
    }
}

bool Universe::planetExists(const MyString& name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].planetName == name) {
            return true;
        }
    }
    return false;
}

bool Universe::jediExists(const MyString& name) {
    for (int i = 0; i < size; i++) {
        if (planets[i].alreadyExists(name)) {
            return true;
        }
    }
    return false;
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

 Universe::getYoungestJedi (const MyString& planet_name, const Rank& jedi_rank) {
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

void Universe::sortedNames (const MyString& firstPlanet, const MyString& secondPlanet) {
    int firstPlanetIdx = -1, secondPlanetIdx = -1, i = 0;
    do {
        if (planets[i].planetName == firstPlanet) {
            firstPlanetIdx = i;
        }
        if (planets[i].planetName == secondPlanet) {
            secondPlanetIdx = i;
        }
        i++;
    }
    while (firstPlanetIdx == -1 || secondPlanetIdx == -1 || i < size);

    if (firstPlanetIdx != -1) {
        planets[firstPlanetIdx].sortJedis();
    }
    if (secondPlanetIdx != -1) {
        planets[secondPlanetIdx].sortJedis();
    }
    if (firstPlanetIdx == -1 && secondPlanetIdx == -1) {
        cout << "Neither of those names match the planets in this universe!\n";
    }
    else if (firstPlanetIdx == -1 && secondPlanetIdx != -1) {
        cout << "Only planet" << secondPlanet << "exists. Printing out its sorted habitants.\n";
        planets[secondPlanetIdx].println();
    }
    else if (firstPlanetIdx != -1 && secondPlanetIdx == -1) {
        cout << "Only planet" << firstPlanet << "exists. Printing out its sorted habitants.\n";
        planets[firstPlanetIdx].println();
    }
    else {
        int firstIdx = 0, secondIdx = 0, comparison = 0;
        do {
            // compare the jedis' names at both indexes
            if (firstIdx == planets[firstPlanetIdx].size) {
                comparison = 1;
            }
            if (secondIdx == planets[secondPlanetIdx].size) {
                comparison = -1;
            }
            if (firstIdx < planets[firstPlanetIdx].size && secondIdx < planets[secondPlanetIdx].size) {
                comparison = strcmp(planets[firstPlanetIdx].jedis[firstIdx].name.getString(),
                                    planets[secondPlanetIdx].jedis[secondIdx].name.getString());
            }
            if (comparison > 0) // first dismatch of chars: ch of 1 > ch of 2 --> 2 is before 1 --> print out 2 
            {
                planets[secondPlanetIdx].jedis[secondIdx++].println();
            }
            if (comparison == 0) // strings are equal --> print out both 
            {
                planets[firstPlanetIdx].jedis[firstIdx++].println();
                planets[secondPlanetIdx].jedis[secondIdx++].println();
            }
            if (comparison > 0) // first dismatch chars: ch of 1 < ch of 2 --> 1 is before 2 --> print out 1 
            {
                planets[firstPlanetIdx].jedis[firstIdx++].println();
            }
        }
        while (firstIdx < planets[firstPlanetIdx].size || secondIdx < planets[secondPlanetIdx].size);
    }
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
    os << universe.size << endl;
    for (int i = 0; i < universe.size; i++) {
        os << universe.planets[i];
    }
    return os;
}

std::istream& operator >> (std::istream& is, Universe& universe) {
    int count;
    is >> count; is.get();
    for (universe.size; universe.size < count; (universe.size)++) {
        is >> universe.planets[universe.size];
    }
    return is;
}

void Universe::readFromFile(const char* name) {
    std::ifstream in;
    in.open(name);
    if (in) {
        in >> *this;
    }
    in.close();
}

bool Universe::writeToFile(const char* name) {
    std::ofstream out;
    out.open(name);
    if (!out) {
        return false;
    }
    out << *this;
    out.close();
    return true;
}