#ifndef RANK_H
#define RANK_H

#include "myString.h"
#include "Printable.h"

class Rank : public Printable {
    MyString rank;
    unsigned rankLevel;
    void checkRank();
    void setLevel();
    public: 

    Rank();
    Rank(const MyString& name);
    Rank(char* name);

    MyString& getRank () {return rank;}

    void readRank ();
    void setRank (const MyString& newRank);
    void rankUp ();
    void demote ();
    bool operator != (const Rank& other);
    bool operator == (const Rank& other);
    friend std::ostream& operator << (std::ostream& os, const Rank& _rank);
    friend std::istream& operator >> (std::istream& is, Rank& _rank);
    friend class Jedi;
    void print(std::ostream& os = std::cout) const override;
};

#endif