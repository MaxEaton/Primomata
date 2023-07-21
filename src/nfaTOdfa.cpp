#include "help.hpp"


void epsilon(State *dfaState, std::map<std::string, State*> &elems) {
    for (State *state : dfaState->transitions[0]) {
        if (!elems[state->name]) {
            elems[state->name] = state;
            epsilon(state, elems);
        }
    }
}

void create(std::map<std::string, State*> &elems, std::string &nextStateName, bool &nextFinal) {
    nextStateName = "";
    nextFinal = false;
    for (std::pair<std::string, State*> elem : elems) {
        if (!nextStateName.empty()) nextStateName += "_";
        nextStateName += elem.first;
        if (elem.second->final) nextFinal = true;
    }
}

void add(State *dfaState, std::map<std::string, State*> elems, std::unordered_map<std::string, State*> &dfaStates, std::string &letters) {
    dfaStates.insert({dfaState->name, dfaState});
    std::string nextStateName;
    bool nextFinal;
    for (char letter : letters) {
        if (letter == 0) continue;
        std::map<std::string, State*> list;
        for (std::pair<std::string, State*> elem : elems) {
            for (State *state : elem.second->transitions[letter]) {
                if (!list[state->name]) {
                    list[state->name] = state;
                    epsilon(state, list);
                }
            }
        }
        create(list, nextStateName, nextFinal);
        if (nextStateName.empty()) continue;
        if (!dfaStates[nextStateName]) {
            State* nextState = new State(nextStateName, nextFinal);
            dfaState->transitions.insert({letter, {nextState}});
            dfaStates[nextStateName] = nextState;
            add(nextState, list, dfaStates, letters);
        } else {
            dfaState->transitions.insert({letter, {dfaStates[nextStateName]}});
        }
    }
}

void nfaTOdfa(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters) {
    std::unordered_map <std::string, State*> dfaStates;
    std::map<std::string, State*> list;
    list[start->name] = start;
    epsilon(start, list);
    std::string nextStateName;
    bool nextFinal;
    create(list, nextStateName, nextFinal);
    State *dfaStart = new State(nextStateName, nextFinal);
    add(dfaStart, list, dfaStates, letters);

    for (std::pair<std::string, State*> state : states) delete state.second;
    states.clear();

    start = dfaStart;
    states = dfaStates;
    letters = letters;
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    std::string fileName = argv[1];
    State *start = nullptr;
    std::unordered_map <std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    std::unordered_map <std::string, State*> dfaStates;
    std::map<std::string, State*> list;
    list[start->name] = start;
    epsilon(start, list);
    std::string nextStateName;
    bool nextFinal;
    create(list, nextStateName, nextFinal);
    State *dfaStart = new State(nextStateName, nextFinal);
    add(dfaStart, list, dfaStates, letters);

    note(dfaStart, dfaStates, letters, fileName + ".dfa");

    return 0;
}
#endif
