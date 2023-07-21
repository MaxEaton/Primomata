#include "help.hpp"


void unreachable(State* &start, std::unordered_map<std::string, State*> &states) {
    std::unordered_map<std::string, State*> dfaStates;
    dfaStates[start->name] = start;
    std::queue<State*> queue;

    queue.push(start);
    while (!queue.empty()) {
        for (std::pair<char, std::vector<State*>> transition : queue.front()->transitions) {
            if (dfaStates.find(transition.second[0]->name) == dfaStates.end()) {
                dfaStates[transition.second[0]->name] = transition.second[0];
                queue.push(transition.second[0]);
            }
        }
        queue.pop();
    }

    states = dfaStates;
}

void dead(State* &start, std::unordered_map<std::string, State*> &states) {
    std::unordered_map<std::string, State*> deadStates;
    for (std::pair<std::string, State*> state : states) {
        if (state.second->transitions.empty() && !state.second->final) {
            deadStates[state.second->name] = state.second;
        }
    }

    int n = 0;
    int count;
    while (n != deadStates.size()) {
        n = deadStates.size();
        for (std::pair<std::string, State*> state : states) {
            if (state.second->transitions.empty() || state.second->final || deadStates.find(state.first)!=deadStates.end()) continue;
            count = 0;
            for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
                if (deadStates.find(transition.second[0]->name) != deadStates.end()) count++;
            }
            if (count == state.second->transitions.size()) {
                if (start == state.second) fail("start state is dead");
                deadStates[state.first] = state.second;
            }
        }
    }

    for (std::pair<std::string, State*> deadState : deadStates) {
        states.erase(deadState.first);
        for (std::pair<std::string, State*> state : states) {
            for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
                if (transition.second[0]->name == deadState.first) {
                    state.second->transitions.erase(transition.first);
                    break;
                }
            }
        }
    }
}

bool partition(std::vector<std::unordered_map<std::string, State*>> &clusters) {
    std::vector<std::unordered_map<std::string, State*>> newClusters;
    std::unordered_map<std::string, State*> tempCluster;
    for (std::unordered_map<std::string, State*> cluster : clusters) {
        for (auto i=cluster.begin(); i!=cluster.end(); i++) {
            for (std::unordered_map<std::string, State*> newCluster : newClusters) if (newCluster.find(i->first) != newCluster.end()) goto done;
            tempCluster.clear();
            tempCluster[i->first] = i->second;
            for (auto j=i; j!=cluster.end(); j++) {
                if (i != j && i->second->transitions.size() == j->second->transitions.size()) {
                    for (std::pair<char, std::vector<State*>> transition : i->second->transitions) {
                        if (j->second->transitions.find(transition.first) == j->second->transitions.end()) goto skip;
                        std::unordered_map<std::string, State*> jCluster;
                        for (std::unordered_map<std::string, State*> iCluster : clusters) {
                            if (iCluster.find(transition.second[0]->name) != iCluster.end()) {
                                jCluster = iCluster;
                                break;
                            }
                        }
                        if (jCluster.find(j->second->transitions[transition.first][0]->name) == jCluster.end()) goto skip;
                    }
                    tempCluster[j->first] = j->second;
                    skip:;
                }
            }
            newClusters.push_back(tempCluster);
            done:;
        }
    }

    if (clusters == newClusters) return false;
    clusters = newClusters;
    return true;
}

void create(std::unordered_map<std::string, State*> &elems, std::string &nextStateName, bool &dfaFinal) {
    nextStateName = "";
    dfaFinal = false;
    for (std::pair<std::string, State*> elem : elems) {
        if (!nextStateName.empty()) nextStateName += "_";
        nextStateName += elem.first;
        if (elem.second->final) dfaFinal = true;
    }
}

void dfaTOmin(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters) {
    unreachable(start, states);
    dead(start, states);
    std::unordered_map<std::string, State*> endStates;
    for (std::pair<std::string, State*> state : states) if (state.second->final) endStates[state.first] = state.second;
    for (std::pair<std::string, State*> endState : endStates) states.erase(endState.first);
    std::vector<std::unordered_map<std::string, State*>> clusters = {states, endStates};
    while (partition(clusters));
    State* dfaStart;
    std::unordered_map<std::string, State*> dfaStates;
    std::string dfaStateName;
    bool dfaFinal;
    for (std::unordered_map<std::string, State*> cluster : clusters) {
        create(cluster, dfaStateName, dfaFinal);
        dfaStates[dfaStateName] = new State(dfaStateName, dfaFinal);
        for (std::pair<std::string, State*> state : cluster) {
            if (state.second == start) {
                dfaStart = dfaStates[dfaStateName];
                break;
            }
        }
    }
    clusters.push_back(dfaStates);
    std::string nextStateName;
    for (std::unordered_map<std::string, State*> cluster : clusters) {
        if (cluster == dfaStates) continue;
        create(cluster, dfaStateName, dfaFinal);
        for (std::pair<char, std::vector<State*>> transition : cluster.begin()->second->transitions) {
            for (std::unordered_map<std::string, State*> nextCluster : clusters) {
                if (nextCluster.find(transition.second[0]->name) != nextCluster.end()) {
                    create(nextCluster, nextStateName, dfaFinal);
                    break;
                }
            }
            dfaStates[dfaStateName]->transitions[transition.first].push_back(dfaStates[nextStateName]);
        }
    }

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
    std::unordered_map<std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    unreachable(start, states);
    dead(start, states);
    std::unordered_map<std::string, State*> endStates;
    for (std::pair<std::string, State*> state : states) if (state.second->final) endStates[state.first] = state.second;
    for (std::pair<std::string, State*> endState : endStates) states.erase(endState.first);
    std::vector<std::unordered_map<std::string, State*>> clusters = {states, endStates};
    while (partition(clusters));

    State* dfaStart;
    std::unordered_map<std::string, State*> dfaStates;
    std::string dfaStateName;
    bool dfaFinal;
    for (std::unordered_map<std::string, State*> cluster : clusters) {
        create(cluster, dfaStateName, dfaFinal);
        dfaStates[dfaStateName] = new State(dfaStateName, dfaFinal);
        for (std::pair<std::string, State*> state : cluster) {
            if (state.second == start) {
                dfaStart = dfaStates[dfaStateName];
                break;
            }
        }
    }
    clusters.push_back(dfaStates);
    std::string nextStateName;
    for (std::unordered_map<std::string, State*> cluster : clusters) {
        if (cluster == dfaStates) continue;
        create(cluster, dfaStateName, dfaFinal);
        for (std::pair<char, std::vector<State*>> transition : cluster.begin()->second->transitions) {
            for (std::unordered_map<std::string, State*> nextCluster : clusters) {
                if (nextCluster.find(transition.second[0]->name) != nextCluster.end()) {
                    create(nextCluster, nextStateName, dfaFinal);
                    break;
                }
            }
            dfaStates[dfaStateName]->transitions[transition.first].push_back(dfaStates[nextStateName]);
        }
    }

    note(dfaStart, dfaStates, letters, fileName + ".min");

    return 0;
}
#endif
