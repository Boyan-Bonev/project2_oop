#include <iostream>
#include <cstring>

#include "universe.h"
#include "myString.h"

using std::cout; using std::cin; using std::endl;

void printHelp () {
    cout    << "Possible commands:\n" 
            << "add_planet <planet_name>\n"
            << "create_jedi <planet_name> <jedi_name> <jedi_rank> <jedi_age> <saber_color> <jedi_strength>\n"
            << "removeJedi <jedi_name> <planet_name>\n"
            << "promote_jedi <jedi_name> <multiplier>\n"
            << "demote_jedi <jedi_name> <multiplier>\n"
            << "get_strongest_jedi <planet_name>\n"
            << "get_youngest_jedi <planet_name> <jedi_rank>\n"
            << "get_most_used_saber_color <planet_name> <jedi_rank>\n"
            << "get_most_used_saber_color <planet_name>\n"
            << "print <planet_name>\n"
            << "print <jedi_name>\n"
            << "<planet_name> + <planet_name>\n"
            << "end\n";
}

const size_t ADD = 1;
const size_t CREATE = 2;
const size_t REMOVE = 3;
const size_t PROMOTE = 4;
const size_t DEMOTE = 5;
const size_t STRONGEST = 6;
const size_t YOUNGEST = 7;
const size_t MOST_USED = 8;
const size_t PRINT = 9;
const size_t SORT_PRINT = 10;
const size_t END = 11;
const size_t INCORRECT = 0;


int validCommand (const MyString& input) {
    int len = strlen(input.getString());
    char* command = new char [len+1];
    strcpy_s(command,len + 1,input.getString());
    if (strstr(command,"add_planet")) {
        return ADD;
    }
    if (strstr(command,"create_jedi")) {
        return CREATE;
    }
    if (strstr(command,"removeJedi")) {
        return REMOVE;
    }
    if (strstr(command,"promote_jedi")) {
        return PROMOTE;
    }
    if (strstr(command,"demote_jedi")) {
        return DEMOTE;
    }
    if (strstr(command,"get_strongest_jedi")) {
        return STRONGEST;
    }
    if (strstr(command,"get_youngest_jedi")) {
        return YOUNGEST;
    }
    if (strstr(command,"get_most_used_saber_color")) {
        return MOST_USED;
    }
    if (strstr(command,"print")) {
        return PRINT;
    }
    if (strstr(command," + ")) {
        return SORT_PRINT;
    }
    if (strstr(command,"end")) {
        return END;
    }
    return INCORRECT;
}

double toDouble(const MyString& input, int start, int stop) {
    unsigned long long int m = 1;
    double ret = 0;
    int len = strlen(input.getString());
    char* string = new char [len+1];
    strcpy_s(string,len + 1,input.getString());
    for (int i = stop; i >= start; i--) {
        ret += (string[i] - '0') * m;
        m *= 10;
    }
    return ret;
}

void activateCommand (const MyString& input, Universe& universe) {
    int command = validCommand(input);
    MyString planetName, jediName, multiplierString, jediRank, secondPlanetName, jediAge, jediStrength,saberColor;
    int len = strlen(input.getString());
    char* string = new char [len+1];
    strcpy_s(string,len + 1,input.getString());
    switch (command) {
        case INCORRECT: printHelp(); break;
        
        case ADD : 
        {   
            int beginning = strlen("add_planet <");
            for (int i = beginning; i < len; i++) { // the symbol after "add_planet <"
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            universe.addPlanet(planetName);
            break;
        }

        case CREATE : 
        {
            //"create_jedi <planet_name> <jedi_name> <jedi_rank> <jedi_age> <saber_color> <jedi_strength>\n"
            int beginning = strlen("create_jedi <"), i = 0;
            for (i = beginning; i < len; i++) { // the symbol after "add_planet <"
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            i+= 2;
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    jediName.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            i+= 2;
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    jediRank.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    jediAge.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            int age = (int)toDouble(jediAge,0,jediAge.getSize());
            i+= 2;
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    saberColor.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            i+= 2;
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    jediStrength.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            double strength = toDouble(jediStrength, 0, jediStrength.getSize());
            universe.createJedi(planetName,jediName,jediRank,age,saberColor,strength);
            break;
        }

        case REMOVE : 
        {
            int beginning = strlen("removeJedi <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    jediName.push_back(string[i]);
                }
                else break;
            }
            i += 2; // skips " <"
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            universe.removeJedi(jediName,planetName);
            break;
        }

        case PROMOTE :
        {
            int beginning = strlen("promote_jedi <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    jediName.push_back(string[i]);
                }
                else break;
            }
            i += 2; // skips " <"
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    multiplierString.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            double multiplier = toDouble(multiplierString.getString(),0,multiplierString.getSize());
            universe.promoteJedi(jediName,multiplier);
            break;
        }

        case DEMOTE :
        {
            int beginning = strlen("demote_jedi <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    jediName.push_back(string[i]);
                }
                else break;
            }
            i += 2; // skips " <"
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    multiplierString.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            double multiplier = toDouble(multiplierString.getString(),0,multiplierString.getSize());
            universe.demoteJedi(jediName,multiplier);
            break;
        }

        case STRONGEST :
        {
            int beginning = strlen("get_strongest_jedi <");
            for (int i = beginning; i < len; i++) { // the symbol after "add_planet <"
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            universe.getStrongestJedi(planetName);
            break;
        }

        case YOUNGEST : 
        {
            int beginning = strlen("get_youngest_jedi <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break;
            }
            i += 2; // skips " <"
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    jediRank.push_back(string[i]);
                }
                else break; // breaks when it reaches >
            }
            universe.getYoungestJedi(planetName,Rank(jediRank));
            break;
        }

        case MOST_USED :
        {
            int beginning = strlen("get_most_used_saber_color <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break;
            }
            if (i == len) /* if there is no jedi rank */ {
                universe.getMostUsedSaberColor(planetName);
            }
            else {
                i += 2; // skips " <"
                for (i; i < len; i++) {
                    if (string[i] != '>') {
                        jediRank.push_back(string[i]);
                    }
                    else break; // breaks when it reaches >
                }
                universe.getMostUsedSaberColor(planetName,Rank(jediName));
            }
            break;
        }

        case PRINT :
        {
            int beginning = strlen("print <"), i = 0;
            for (i = beginning; i < len; i++) {
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break;
            }
            if (universe.planetExists(planetName)) {
                int size = universe.getSize();
                for (int i = 0; i < size; i++) {
                    if (universe.getPlanetName(i) == planetName) {
                        universe.printPlanet(i);
                    }
                }
            }
            if (universe.jediExists(planetName)) {
                universe.printJedi(planetName);
            }
            break;
        }

        case SORT_PRINT : 
        {
            // skip < 
            int i = 0;
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    planetName.push_back(string[i]);
                }
                else break;
            }
            i+= 4; // skips " + <"
            for (i; i < len; i++) {
                if (string[i] != '>') {
                    secondPlanetName.push_back(string[i]);
                }
                else break;
            }
            universe.sortedNames(planetName,secondPlanetName);
            break;
        }

        case END : 
        {
            cout << "Ending this dialogue!\n";
        }
    }
}

int main () {
    Universe universe;
    MyString input;
    char c;
    do {
        cout << "Do you want to read your universe from a file (F) or enter it in the console (C)? Type the respondent letter: ";
        cin >> c;
    }
    while (c == 'F' || c == 'C');
    if (c == 'F') {
        cout << "Enter the name of your file in the following format - example.txt";
        input.readString();
        universe.readFromFile(input.getString());
    }
    else {
        universe.readUniverse();
    }
    do {
        cout << "Enter your command(type help to see the commands): "; input.readString();
        if (validCommand(input)) { // includes help option for command names 
            activateCommand(input, universe);
        }
    }
    while (input != "end");
    
}