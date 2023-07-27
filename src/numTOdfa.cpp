#include "help.hpp"


void numTOdfa(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, int n, bool accept) {
    for (std::pair<std::string, State*> state : states) delete state.second;
    states.clear();

    std::string prefix = "q_"+std::to_string(n)+"_";
    start = new State(prefix+std::to_string(0), accept);
    letters = "01";
    states[start->name] = start;
    for (int i=1; i<n; i++) states[prefix+std::to_string(i)] = new State(prefix+std::to_string(i), !accept);
    for (int i=0; i<n/2+1; i++) {
        states[prefix+std::to_string(i)]->transitions['0'].push_back(states[prefix+std::to_string(i*2)]);
        states[prefix+std::to_string(i+n/2)]->transitions['1'].push_back(states[prefix+std::to_string(i*2)]);
    }
    for (int i=0; i<n/2; i++) {
        states[prefix+std::to_string(i)]->transitions['1'].push_back(states[prefix+std::to_string(i*2+1)]);
        states[prefix+std::to_string(i+n/2+1)]->transitions['0'].push_back(states[prefix+std::to_string(i*2+1)]);
    }
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    int n = std::stoi(argv[1]);
    std::string prefix = "q_"+std::to_string(n)+"_";

    State *start = new State(prefix+std::to_string(0), true);
    std::unordered_map<std::string, State*> states;
    std::string letters = "01";

    states[start->name] = start;
    for (int i=1; i<n; i++) states[prefix+std::to_string(i)] = new State(prefix+std::to_string(i), false);

    for (int i=0; i<n/2+1; i++) {
        states[prefix+std::to_string(i)]->transitions['0'].push_back(states[prefix+std::to_string(i*2)]);
        states[prefix+std::to_string(i+n/2)]->transitions['1'].push_back(states[prefix+std::to_string(i*2)]);
    }

    for (int i=0; i<n/2; i++) {
        states[prefix+std::to_string(i)]->transitions['1'].push_back(states[prefix+std::to_string(i*2+1)]);
        states[prefix+std::to_string(i+n/2+1)]->transitions['0'].push_back(states[prefix+std::to_string(i*2+1)]);
    }

    note(start, states, letters, "tests/prime.dfa");

    return 0;
}
#endif
