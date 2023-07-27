#include "help.hpp"


int main(int argc, char** argv) {
    std::string fileName;
    State* start = nullptr;
    std::unordered_map <std::string, State*> states;
    std::string letters;
    State* start2;
    std::unordered_map <std::string, State*> states2;
    std::string letters2;

    fileName = "tests/primes.dfa";
    numTOdfa(start, states, letters, 3, true);
    numTOdfa(start2, states2, letters2, 5, true);
    twoTOone(start, states, letters, start2, states2, letters2);
    nfaTOdfa(start, states, letters);
    dfaTOmin(start, states, letters);
    dfaTOcpp(start, states, letters, fileName);
    newGraph(start, states, letters, fileName);
    note(start, states, letters, fileName);

    fileName = "tests/composites.dfa";
    numTOdfa(start, states, letters, 15, true);
    dfaTOcpp(start, states, letters, fileName);
    newGraph(start, states, letters, fileName);
    note(start, states, letters, fileName);

    return 0;
}
