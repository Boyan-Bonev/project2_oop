#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "planet.h"
#include "Printable.h"

class Universe : public Printable {
    Planet* planets;
    int size; int capacity;
    void copy (const Universe& other);
    void doubleCap ();
    public: 
    Universe();
    Universe(const Universe& other);
    Universe& operator = (const Universe& other);
    ~Universe();

    int getSize () const { return size; }
    MyString& getPlanetName (int idx) const { return planets[idx].planetName; }
    void printPlanet (int idx) const { planets[idx].print(); }
    void printJedi (int idx, const MyString& name ) const { planets[idx]}

    bool planetExists(const MyString& name);
    bool jediExists(const MyString& name);
    void readUniverse(std::istream& is = std::cin);
    void addPlanet(const MyString& planet_name);
    void createJedi(const MyString& planet_name, const MyString& jedi_name, 
                    const Rank& jedi_rank,int jedi_age, const MyString&saber_color, double jedi_strength);
    void removeJedi(const MyString& jedi_name, const MyString& planet_name);
    void promoteJedi (const MyString& jedi_name, double multiplier);
    void demoteJedi (const MyString& jedi_name, double multiplier);
    void getStrongestJedi(const MyString& planet_name);
    void getYoungestJedi (const MyString& planet_name, const Rank& jedi_rank);
    void getMostUsedSaberColor (const MyString& planet_name, const Rank& jedi_rank);
    void getMostUsedSaberColor (const MyString& planet_name);
    void sortedNames (const MyString& firstPlanet, const MyString& secondPlanet);

    bool operator != (const Universe& other);
    void print(std::ostream& os = std::cout) const override;
    void readFromFile(const char* name);
    bool writeToFile(const char* name);

    friend std::ostream& operator << (std::ostream& os, const Universe& universe);
    friend std::istream& operator >> (std::istream& is, Universe& universe);


};

#endif