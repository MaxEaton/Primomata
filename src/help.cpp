#include "help.hpp"


State::State(std::string _name, bool _final) {
    name = _name;
    final = _final;
}

State::~State() {
    transitions.clear();
}

void fail(std::string msg) {
    std::cout << msg << std::endl;
    exit(-1);
}

void read(State *&start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName) {
    std::ifstream file(fileName);
    if (!file) fail("file failed to open");
    std::string word;
    std::istringstream buff;

    // get letters
    std::getline(file, letters);
    if (letters.empty()) fail("file has no letters");

    // get states
    std::getline(file, word);
    buff.str(word);
    if (!buff) fail("file has no states");
    bool final;
    while (buff >> word) {
        final = false;
        if (word.back() == '>') {
            final = true;
            word = word.substr(0, word.length()-1);
        }
        if (word[0] == '>') {
            if (start) fail("file has multiple start states");
            word = word.substr(1, word.length()-1);
            start = new State(word, final);
            states[word] = start;
        } else states[word] = new State(word, final);
            states.insert({word, new State(word, final)});
    }
    if (!start) fail("file has no start states");

    // get transitions
    State *A;
    std::vector<State*> B;
    char x;
    while (std::getline(file, word)) {
        buff.clear();
        buff.str(word);
        B = {};
        buff >> word;
        A = states[word];
        buff >> word;
        if (word == "epsilon") x = 0;
        else if (word == "space") x = ' ';
        else if (word.length() != 1) fail("file has invalid symbol");
        else x = word[0];
        while (buff >> word) {
            B.push_back(states[word]);
        }
        if (!A || !B[0]) fail("file has undefined states");
        A->transitions[x] = B;
    }

    file.close();
}

void note(State *&start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName) {
    std::ofstream file(fileName);
    file << letters << "\n";
    for (std::pair<std::string, State*> state: states) {
        if (state.second == start) file << ">";
        file << state.first;
        if (state.second->final) file << ">";
        file << " ";
    }
    file << "\n";
    for (std::pair<std::string, State*> state: states) {
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            file << state.first << " ";
            if (transition.first == 0) file << "epsilon ";
            else if (transition.first == ' ') file << "space ";
            else file << transition.first << " ";
            for (State* dest : transition.second) {
                file << dest->name << " ";
            }
            file << "\n";
        }
    }
    file.close();
}
