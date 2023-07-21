#include "help.hpp"


void dfaTOcpp(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string fileName) {
    std::ofstream file(fileName + ".cpp");
    file << "#include <iostream>\n\n";
    for (std::pair<std::string, State*> state : states) file << "bool state_" << state.first << "(std::string input);\n";
    file << "\n";
    for (std::pair<std::string, State*> state : states) {
        file << "bool state_" << state.first << "(std::string input) {\n";
        file << "\tif (input.empty()) return " << state.second->final << ";\n";
        file << "\tswitch(input[0]) {\n";
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            file << "\t\tcase '" << transition.first << "':\n";
            file << "\t\t\treturn state_" << transition.second[0]->name << "(input.substr(1, input.length()-1));\n";
        }
        file << "\t\tdefault:\n";
        file << "\t\t\treturn false;\n";
        file << "\t}\n";
        file << "}\n\n";
    }
    file << "int main(int argc, char** argv) {\n";
    file << "\tif (argc != 2) return -1;\n";
    file << "\tif (state_" << start->name << "(argv[1])) std::cout << \"valid string\" << std::endl;\n";
    file << "\treturn 0;\n";
    file << "}\n";
    file.close();
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no file provided");
    std::string fileName = argv[1];
    State *start = nullptr;
    std::unordered_map<std::string, State*> states;
    std::string letters;
    read(start, states, letters, fileName);

    std::ofstream file(fileName + ".cpp");
    file << "#include <iostream>\n\n";
    for (std::pair<std::string, State*> state : states) file << "bool state_" << state.first << "(std::string input);\n";
    file << "\n";
    for (std::pair<std::string, State*> state : states) {
        file << "bool state_" << state.first << "(std::string input) {\n";
        file << "\tif (input.empty()) return " << state.second->final << ";\n";
        file << "\tswitch(input[0]) {\n";
        for (std::pair<char, std::vector<State*>> transition : state.second->transitions) {
            file << "\t\tcase '" << transition.first << "':\n";
            file << "\t\t\treturn state_" << transition.second[0]->name << "(input.substr(1, input.length()-1));\n";
        }
        file << "\t\tdefault:\n";
        file << "\t\t\treturn false;\n";
        file << "\t}\n";
        file << "}\n\n";
    }
    file << "int main(int argc, char** argv) {\n";
    file << "\tif (argc != 2) return -1;\n";
    file << "\tif (state_" << start->name << "(argv[1])) std::cout << \"valid string\" << std::endl;\n";
    file << "\treturn 0;\n";
    file << "}\n";
    file.close();
    return 0;
}
#endif
