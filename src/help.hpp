#ifndef AUTOMATA_HELP_HPP
#define AUTOMATA_HELP_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <queue>
#include <map>
#include <unordered_map>


struct State {
    std::string name;
    bool final;
    std::unordered_map<char, std::vector<State*>> transitions;

    State(std::string _name, bool _final);
    ~State();
};

void fail(std::string msg);
void read(State *&start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName);
void note(State *&start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName);

void newGraph(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName);
void newNames(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters);
void rexTOnfa(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string input);
void nfaTOdfa(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters);
void dfaTOmin(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters);
void dfaTOcpp(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName);

#endif //AUTOMATA_HELP_HPP
