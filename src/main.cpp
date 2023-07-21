#include "help.hpp"


int main(int argc, char** argv) {
//    if (argc != 2) fail("no file provided");
    std::string input = "((1|0)*0|0)*|(1(01*0)*1|0)*|(0|1(10)*(0|11)(01*01|01*00(10)*(0|11))*1)*";
    State* start;
    std::unordered_map <std::string, State*> states;
    std::string letters;
    std::string fileName = "mainTest";
//    std::string fileName = argv[1];

    rexTOnfa(start, states, letters, input);
    nfaTOdfa(start, states, letters);
    dfaTOmin(start, states, letters);
    newNames(start, states, letters);
    dfaTOcpp(start, states, letters, fileName);
    newGraph(start, states, letters, fileName);

    return 0;
}