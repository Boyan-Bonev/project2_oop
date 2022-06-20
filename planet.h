#ifndef PLANET_H
#define PLANET_H
#include "jedi.h"
#include "myString.h"
#include "printable.h"

class Planet : public Printable {
    MyString planetName;
    Jedi* jedis;
    int size; int capacity;
    void copy (const Planet& other);
    void doubleCap ();
    int idxOfJedi (const MyString& jedi_name);
    public:
    Planet();
    Planet(const Planet& other);
    Planet& operator = (const Planet& other);
    ~Planet();

    void sortJedis();
    int idxOfJedi (const MyString& jedi_name) const;
    bool alreadyExists(const MyString& jedi_name) const;
    Planet(const MyString& _planetName, const Jedi* _jedis, int jedisCount);
    void readPlanet(std::istream& is = std::cin);
    void createJedi(const MyString& jedi_name, const Rank& jedi_rank,
                    int jedi_age, const MyString&saber_color, double jedi_strength);
    void removeJedi (const MyString& jedi_name);
    void promoteJedi (const MyString& jedi_name, double multiplier);
    void demoteJedi (const MyString& jedi_name, double multiplier);
    void getStrongestJedi () const;
    void getYoungestJedi (const Rank& jedi_rank) const;
    char* getMostUsedSaberColor() const ;   
    char* getMostUsedSaberColor (const Rank& jedi_rank) const;
    bool operator != (const Planet& other);
    void print(std::ostream& os = std::cout) const override;
    void readFromFile(const char* name);
    bool writeToFile(const char* name);
    friend std::ostream& operator << (std::ostream& os, const Planet& planet);
    friend std::istream& operator >> (std::istream& is, Planet& planet);

    friend class Universe;
};

#endif 