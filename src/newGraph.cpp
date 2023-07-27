#include "help.hpp"


//    note(start, states, letters, fileName);
void newGraph(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName) {
    std::ofstream file(fileName + ".dot");
    file << "digraph fsa {\n";
    file << "ratio=\"1\"\n";
    file << "    \"\" [shape=none]\n";
    for (std::pair<std::string, State*> state : states) {
        file << "    \"" << state.first << "\"" << " [shape=";
        if (state.second->final) file << "double";
        file << "circle]\n";
    }
    file << "\n    \"\" -> \"" << start->name << "\"\n";
    for (std::pair<std::string, State*> state : states) {
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            for (State* nextState : transition.second) {
                file << "    \"" << state.first << "\" -> \"" << nextState->name<< "\" [label=\"";
                if (transition.first == 0) file << "ε\"]\n";
                else if (transition.first == ' ') file << "space\"]\n";
                else file << transition.first << "\"]\n";
            }
        }
    }
    file << "}\n";
    file.close();
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    std::string fileName = argv[1];
    State *start = nullptr;
    std::unordered_map <std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    std::ofstream file(fileName + ".dot");
    file << "digraph fsa {\n";
    file << "    \"\" [shape=none]\n";
    for (std::pair<std::string, State*> state : states) {
        file << "    \"" << state.first << "\"" << " [shape=";
        if (state.second->final) file << "double";
        file << "circle]\n";
    }
    file << "\n    \"\" -> \"" << start->name << "\"\n";
    for (std::pair<std::string, State*> state : states) {
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            for (State* nextState : transition.second) {
                file << "    \"" << state.first << "\" -> \"" << nextState->name<< "\" [label=\"";
                if (transition.first == 0) file << "ε\"]\n";
                else if (transition.first == ' ') file << "space\"]\n";
                else file << transition.first << "\"]\n";
            }
        }
    }
    file << "}\n";
    file.close();

    return 0;
}
#endif
