#include "help.hpp"


void addStart(State* &start, std::unordered_map<std::string, State*> &states) {
    State* newStart = new State("q_start", start->final);
    newStart->transitions[0].push_back(start);
    states[newStart->name] = newStart;
    start = newStart;
}

void addEnd(State* &start, std::unordered_map<std::string, State*> &states) {
    State* newEnd = new State("q_end", true);
    for (std::pair<std::string, State*> state : states) {
        if (state.second->final) {
            state.second->final = false;
            state.second->transitions[0].push_back(newEnd);
        }
    }
    states[newEnd->name] = newEnd;
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    std::string fileName = argv[1];
    State *start = nullptr;
    std::unordered_map<std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    bool needStart = false;
    bool needEnd = false;
    for (std::pair<std::string, State*> state : states) {
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            if (transition.second[0] == start) needStart = true;
            if (state.second->final) needEnd = true;
        }
        if (needStart && needEnd) break;
    }
    if (needStart) addStart(start, states);
    if (needEnd) addEnd(start, states);

    return 0;
}
#endif
