#include "help.hpp"


void twoTOone(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, State* &start2, std::unordered_map<std::string, State*> &states2, std::string &letters2) {
    State* nfaStart = new State(start->name+"_start", false);
    nfaStart->transitions[0].push_back(start);
    nfaStart->transitions[0].push_back(start2);
    states[nfaStart->name] = nfaStart;
    for (std::pair<std::string, State*> state : states2) {
        state.second->name = state.first + "_2";
        states[state.second->name] = state.second;
    }
    states2.clear();
    std::bitset<'~'-' '+1> lettersSet;
    for (char letter : letters) lettersSet.set(letter-' ');
    for (char letter : letters2) lettersSet.set(letter-' ');
    std::string nfaLetters = "";
    for (char i=' '; i<='~'; i++) if (lettersSet[i-' ']) nfaLetters += i;

    start = nfaStart;
    letters = nfaLetters;
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 3) fail("no files provided");
    std::string fileName = argv[1];
    std::string fileName2 = argv[2];
    State *start = nullptr;
    State *start2 = nullptr;
    std::unordered_map <std::string, State*> states;
    std::unordered_map <std::string, State*> states2;
    std::string letters;
    std::string letters2;

    read(start, states, letters, fileName);
    read(start2, states2, letters2, fileName2);
    State* nfaStart = new State("q_start", false);
    nfaStart->transitions[0].push_back(start);
    nfaStart->transitions[0].push_back(start2);
    states[nfaStart->name] = nfaStart;
    for (std::pair<std::string, State*> state : states2) {
        state.second->name = state.first + "_1";
        states[state.second->name] = state.second;
    }
    std::bitset<'~'-' '+1> lettersSet;
    for (char letter : letters) lettersSet.set(letter-' ');
    for (char letter : letters2) lettersSet.set(letter-' ');
    std::string nfaLetters = "";
    for (char i=' '; i<='~'; i++) if (lettersSet[i-' ']) nfaLetters += i;

    note(nfaStart, states, nfaLetters, "tests/combined.dfa");

    return 0;
}
#endif
