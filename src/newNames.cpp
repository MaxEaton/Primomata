#include "help.hpp"


void newNames(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters) {
    State *dfaStart = start;
    std::unordered_map<std::string, State*> dfaStates;
    int i = 0;
    for (std::pair<std::string, State*> state : states) {
        dfaStates["q"+std::to_string(i)] = state.second;
        state.second->name = "q"+std::to_string(i);
        i++;
    }

    start = dfaStart;
    states = dfaStates;
    letters = letters;
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    std::string fileName = argv[1];
    State *start = nullptr;
    std::unordered_map<std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    State *dfaStart = start;
    std::unordered_map<std::string, State*> dfaStates;
    int i = 0;
    for (std::pair<std::string, State*> state : states) {
        dfaStates["q"+std::to_string(i)] = state.second;
        state.second->name = "q"+std::to_string(i);
        i++;
    }

    note(dfaStart, dfaStates, letters, fileName);

    return 0;
}
#endif
