#include <iostream>
#include <cstring>
#include "myString.h"
#include "rank.h"

const size_t MAX_RANK_NAME = 16;
const size_t YOUNGLING = 1;
const size_t INITIATE = 2;
const size_t PADAWAN = 3;
const size_t KNIGHT_ASPIRANT = 4;
const size_t KNIGHT = 5;
const size_t MASTER = 6;
const size_t BATTLE_MASTER = 7;
const size_t GRAND_MASTER = 8;


bool isRank (const MyString& rank) {
    char name [16];
    strcpy_s(name,16,rank.getString());
    if (name == "None" || name == "YOUNGLING"  || name == "INITIATE" ||name == "PADAWAN" || name == "KNIGHT-ASPIRANT"|| 
        name == "KNIGHT", name == "MASTER" || name == "BATTLE_MASTER" ||name == "GRAND_MASTER") {
            return true;
        }
    return false;
}

void Rank::checkRank() {
    if (!isRank(rank)) {
        do {
            std::cout <<    "Invalid rank! Your options are:\nYOUNGLING, INITIATE, PADAWAN, KNIGHT-ASPIRANT, KNIGHT, MASTER, BATTLE_MASTER or GRAND_MASTER\nEnter your rank: ";
            rank.readString();
        }
        while (!isRank(rank));
    }
}

Rank::Rank() {
    rank = "None";
    setLevel();
}
Rank::Rank(const MyString& name) {
    rank = name;
    checkRank();
    setLevel();
}
Rank::Rank(char* name) {
    rank = name;
    checkRank();
    setLevel();
}

void Rank::readRank () {
    rank.readString();
    checkRank();
    setLevel();
}
void Rank::setRank (const MyString& newRank) {
    rank = newRank;
    checkRank();
    setLevel();
}

void Rank::rankUp () {
    switch (rankLevel) {
        case 0                  : rank = "YOUNGLING"; break;
        case YOUNGLING          : rank = "INITIATE"; break;
        case INITIATE           : rank = "PADAWAN"; break;
        case PADAWAN            : rank = "KNIGHT-ASPIRANT"; break;
        case KNIGHT_ASPIRANT    : rank = "KNIGHT"; break;
        case KNIGHT             : rank = "MASTER"; break;
        case MASTER             : rank = "BATTLE_MASTER"; break;
        case BATTLE_MASTER      : rank = "GRAND_MASTER"; break;
        case GRAND_MASTER       : std::cout << "Max rank reached!"; break;
        default                 : std::cout << "Invalid rank!"; break;
    }
}

void Rank::demote () {
    switch (rankLevel) {
        case 0                  : std::cout << "No jedi created yet!"; break;
        case YOUNGLING          : rank = "None"; std::cout << "Jedi powers have been taken away."; break;
        case INITIATE           : rank = "YOUNGLING"; break;
        case PADAWAN            : rank = "INITIATE"; break;
        case KNIGHT_ASPIRANT    : rank = "PADAWAN"; break;
        case KNIGHT             : rank = "KNIGHT-ASPIRANT"; break;
        case MASTER             : rank = "KNIGHT"; break;
        case BATTLE_MASTER      : rank = "MASTER"; break;
        case GRAND_MASTER       : rank = "BATTLE_MASTER"; break;
        default                 : std::cout << "Invalid rank!"; break;
    }
}

void Rank::setLevel() {
    char name [16];
    strcpy_s(name,16,rank.getString());
    if (name == "YOUNGLING") {
        rankLevel = YOUNGLING;
    }
    else if (name == "INITIATE") {
        rankLevel = INITIATE;
    }
    else if (name == "PADAWAN") {
        rankLevel = PADAWAN;
    }
    else if (name == "KNIGHT-ASPIRANT") {
        rankLevel = KNIGHT_ASPIRANT;
    }
    else if (name == "KNIGHT") {
        rankLevel = KNIGHT;
    }
    else if (name == "MASTER") {
        rankLevel = MASTER;
    }
    else if (name == "BATTLE_MASTER") {
        rankLevel = BATTLE_MASTER;
    }
    else if (name == "GRAND_MASTER") {
        rankLevel = GRAND_MASTER;
    }
}

bool Rank::operator != (const Rank& other) {
    if (rank != other.rank) {
        return true;
    }
    return false;
}

bool Rank::operator == (const Rank& other) {
    if (rank != other.rank) {
        return false;
    }
    return true;
}

std::istream& operator >> (std::istream& is, Rank& _rank) {
    is >> _rank.rank;
    return is;
}

std::ostream& operator << (std::ostream& os, const Rank& _rank) {
    os << _rank.rank;
    return os;
}

void Rank::print(std::ostream& os) const {
    os << "is ";
    if (rankLevel == YOUNGLING || rankLevel == INITIATE) {
        os << "an";
    }
    else os << "a";
    os << rank;
}