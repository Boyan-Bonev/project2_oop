#include <iostream>
#include <fstream>
#include <cstring>
#include "planet.h"
#include "myString.h"
#include "jedi.h"

const size_t DEFAULT_CAP = 4;
const double COMPARISON = 0.0001;
const int MAX_INTEGER = 2147483647;
using std::cout; using std::cin; using std:: endl;

void Planet::doubleCap () {
    capacity *= 2;
    Jedi* tempJedis = new Jedi [capacity];
    for (int i = 0; i < size; i++) {
        tempJedis[i] = jedis[i];
    }
    delete[] jedis;
    jedis = tempJedis;
}

bool Planet::operator != (const Planet& other) {
    if (planetName != other.planetName || size != other.size || capacity != other.capacity) {
        return true;
    }
    for (int i = 0; i < size; i++) {
        if (jedis[i] != other.jedis[i]) {
            return true;
        }
    }
    return false;
}

Planet::Planet() {
    planetName = "None";
    size = 0; capacity = DEFAULT_CAP;
    jedis = new Jedi [capacity];
}

void Planet::copy (const Planet& other) {
    planetName = other.planetName;
    capacity = other.capacity;
    size = other.size;
    jedis = new Jedi [capacity];
    for (int i = 0; i < size; i++) {
        jedis[i] = other.jedis[i];
    }
}

Planet::Planet(const Planet& other) {
    copy(other);
}
Planet& Planet::operator = (const Planet& other) {
    if (*this != other) {
        copy (other);
    }
    return *this;
}
Planet::~Planet() {
    delete[] jedis;
}

Planet::Planet(const MyString& _planetName, const Jedi* _jedis, int jedisCount) {
    planetName = _planetName; 
    for (int i = 0; i < jedisCount; i++) {
        if (size == capacity) {
            doubleCap();
        }
        jedis[i] = _jedis[i];
        size++;
    }
}
void Planet::readPlanet(std::istream& is) {
    int count;
    cout << "What's the name of the planet? "; is >> planetName;
    cout << "How many jedis inhabit it? "; is >> count;
    for (size; size < count; size++) {
        cout << "Please enter jedi " << size + 1 << ':' << endl;
        if (size == capacity) {
            doubleCap();
        }
        jedis[size].readJedi(is);
    }
}

void Planet::sortJedis() {
    int minIdx = 0;
    Jedi tempJedi;
    for (int i = 0; i < size; i++) {
        minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (strcmp(jedis[i].name.getString(),jedis[j].name.getString()) > 0) 
            // j before i 
            {
                minIdx = j;
            }
        }
        // temp = a, a = b, b = temp
        tempJedi = jedis[i];
        jedis[i] = jedis[minIdx];
        jedis[minIdx] = tempJedi;
    }
}

int Planet::idxOfJedi (const MyString& jedi_name) const {
    for (int i = 0; i < size; i++) {
        if (jedis[i].name == jedi_name) {
            return i;
        }
    }
}

bool Planet::alreadyExists(const MyString& jedi_name) const {
    for (int i = 0; i < size; i++) {
        if (jedis[i].name == jedi_name) {
            return true;
        }
    }
    return false;
}

void Planet::createJedi(const MyString& jedi_name, const Rank& jedi_rank,int jedi_age, const MyString&saber_color, double jedi_strength) {
    if (!alreadyExists(jedi_name)) {
        if (size == capacity) {
            doubleCap();
        }
        jedis[size++].setJedi(jedi_name,jedi_age, jedi_rank, saber_color, jedi_strength);
    }
    else {
        cout << "Jedi already exists on planet " << planetName << "!\n";
    }
}
void Planet::removeJedi (const MyString& jedi_name) {
    if (alreadyExists(jedi_name)) {
        int idx = idxOfJedi(jedi_name);
        for (int i = idx; i < size; i++) {
            jedis[i] = jedis[i + 1];
        }
        size--;
        cout << "Jedi" << jedi_name << "has been removed from planet" << planetName << ".\n";
    }
    else {
        cout << "No jedi by the name of " << jedi_name << "inhabits planet" << planetName << "!\n";
    }
}
void Planet::promoteJedi (const MyString& jedi_name, double multiplier) {
    if (alreadyExists(jedi_name)) {
        int idx = idxOfJedi(jedi_name);
        jedis[idx].promoteJedi(multiplier);
    }
    else {
        cout << "No jedi by the name of " << jedi_name << "inhabits planet" << planetName << "!\n";
    }
}
void Planet::demoteJedi (const MyString& jedi_name, double multiplier) {
    if (alreadyExists(jedi_name)) {
        int idx = idxOfJedi(jedi_name);
        jedis[idx].demoteJedi(multiplier);
    }
    else {
        cout << "No jedi by the name of " << jedi_name << "inhabits planet" << planetName << "!\n";
    }
}
void Planet::getStrongestJedi () const {
    int idx = 0;
    for (int i = 1; i < size; i++) {
        if (jedis[i].power - jedis[idx].power > COMPARISON) {
            idx = i;
        }
    }
    jedis[idx].println();
}
void Planet::getYoungestJedi (const Rank& jedi_rank) const {
    int idx = -1, youngest = MAX_INTEGER;
    for (int i = 0; i < size; i++) {
        if (jedis[i].rank == jedi_rank) {
            if (jedis[i].age < youngest) {
                idx = i;
            }
        }
    }
    if (idx == -1) {
        cout << "No jedi with the rank " << jedi_rank << "inhabits planet" << planetName << "!\n";
    }
    else {
        jedis[idx].println();
    }
}

// Saber Colors in Star Wars:
// Black (darksaber), Blue, Light blue, Green, Yellow-green, Purple, Red (darksiders only), White, Yellow
// Creating an array with the following colors coresponding to the indexes of the array in that order
// Black - 0, Blue - 1, Light blue - 2, Green - 3, Yellow-green - 4, Purple - 5, Red - 6, White - 7, Yellow - 8
const size_t COLORS_COUNT = 9;
char* Planet::getMostUsedSaberColor (const Rank& jedi_rank) const {
    int colors[COLORS_COUNT] = {0}, idx = 0;
    bool jediOfThisRankExists = false;
    for (int i = 0; i < size; i++) {
        if (jedis[i].rank == jedi_rank) {
            jediOfThisRankExists = true;
            MyString& tempColor = jedis[i].saberColor;
            if (tempColor == "Black" || tempColor == "black") {
                colors[0] += 1;
            }
            else if (tempColor == "Blue" || tempColor == "blue") {
                colors[1] += 1;

            }
            else if (tempColor == "Light blue" || tempColor == "light blue") {
                colors[2] += 1;
            }
            else if (tempColor == "Green" || tempColor == "green") {
                colors[3] += 1;
            }
            else if (tempColor == "Yellow-green" || tempColor == "yellow-green" || 
                tempColor == "yellow green" || tempColor == "Yellow green") {
                colors[4] += 1;
            }
            else if (tempColor == "Purple" || tempColor == "purple") {
                colors[5] += 1;
            }
            else if (tempColor == "Red" || tempColor == "red") {
                colors[6] += 1;
            }
            else if (tempColor == "White" || tempColor == "white") {
                colors[7] += 1;
            }
            else if (tempColor == "Yellow" || tempColor == "yellow") {
                colors[8] += 1;
            }
        }
    }
    if (jediOfThisRankExists) {
        for (int i = 1; i < COLORS_COUNT; i++) {
            if (colors[i] > colors[idx]) {
                idx = i;
            }
        }
        switch (idx) {
            case 0: return "Black";
            case 1: return "Blue";
            case 2: return "Light blue";
            case 3: return "Green";
            case 4: return "Yellow-green";
            case 5: return "Purple";
            case 6: return "Red";
            case 7: return "White";
            case 8: return "Yellow";
        }
    }
    else return "No jedis of such rank!";
}

char* Planet::getMostUsedSaberColor() const {
    return getMostUsedSaberColor(MyString("GRAND_MASTER"));
}  

void Planet::print(std::ostream& os) const {
    os << "The planet " << planetName << " is a home for " << size << "jedis.\n";
    for (int i = 0; i < size; i++) {
        jedis[i].println(os);
    }
}

void Planet::readFromFile(const char* name) {
    std::ifstream in;
    in.open(name);
    if (in) {
        in >> *this;
    }
    in.close();
}

bool Planet::writeToFile(const char* name) {
    std::ofstream out;
    out.open(name);
    if (!out) {
        return false;
    }
    out << *this;
    out.close();
    return true;
}

std::ostream& operator << (std::ostream& os, const Planet& planet) {
    os << planet.planetName << '|' << planet.size << endl;
    for (int i = 0; i < planet.size; i++) {
        os << planet.jedis[i];
    }
    return os;
}

std::istream& operator >> (std::istream& is, Planet& planet) {
    is >> planet.planetName;
    int count = 0;
    is >> count; is.get();
    for (planet.size; planet.size < count; (planet.size)++) {
        is >> planet.jedis[planet.size];
    }
    return is;
}
