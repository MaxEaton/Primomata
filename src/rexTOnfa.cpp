#include "help.hpp"


struct Node;
enum Type {starting, character, and_operator, or_operator, round_bracket};
enum Number {once, times, plus, question};
union Store {std::vector<std::pair<char, char>>* content; Number number; Node* child;};

struct Node {
    Type type;
    Node* parent;
    std::pair<Store, Store> store;

    Node(Type _type, Node* _parent) {
        type = _type;
        parent = _parent;
    }
};

Number number(std::string &input) {
    switch (input[0]) {
        case '*':
            input.erase(0, 1);
            return Number::times;
        case '+':
            input.erase(0, 1);
            return Number::plus;
        case '?':
            input.erase(0, 1);
            return Number::question;
        default:
            return Number::once;
    }
}

std::vector<std::pair<char, char>>* special(std::string &input) {
    std::vector<std::pair<char, char>>* content = new std::vector<std::pair<char, char>>;
    switch (input[0]) {
        case '\\':
            content->push_back({'\\', '\\'});
            break;
        case '|':
            content->push_back({'|', '|'});
            break;
        case '(':
            content->push_back({'(', '('});
            break;
        case ')':
            content->push_back({')', ')'});
            break;
        case '[':
            content->push_back({'[', '['});
            break;
        case ']':
            content->push_back({']', ']'});
            break;
        case '.':
            content->push_back({'.', '.'});
            break;
        case '^':
            content->push_back({'^', '^'});
            break;
        case '*':
            content->push_back({'*', '*'});
            break;
        case '+':
            content->push_back({'+', '+'});
            break;
        case '?':
            content->push_back({'?', '?'});
            break;
        case 'd':
            content->push_back({'0', '9'});
            break;
        case 'D':
            content->push_back({' ', '/'});
            content->push_back({':', '~'});
            break;
        case 'w':
            content->push_back({'0', '9'});
            content->push_back({'A', 'Z'});
            content->push_back({'_', '_'});
            content->push_back({'a', 'z'});
            break;
        case 'W':
            content->push_back({' ', '/'});
            content->push_back({':', '@'});
            content->push_back({'[', '^'});
            content->push_back({'^', '`'});
            content->push_back({'{', '~'});
            break;
        default:
            fail("invalid escape character");
    }
    return content;
}

Node* parse(std::string &input, Node* root, Node* parent) {
    if (input.empty()) return parent;
    Node* node;
    Node* last;
    bool exclude = false;
    char buffer = 0;
    std::vector<std::pair<char, char>>* ranges;
    std::vector<std::pair<char, char>>* temp;
    std::bitset<'~'-' '+1> compiled;
    switch (input[0]) {
        case '*':
        case '+':
        case '?':
            input.erase(0, 1);
            return parse(input, root, parent);
        case '|':
            node = new Node(or_operator, parent);
            node->store.first.child = parent->store.second.child;
            parent->store.second.child = node;
            input.erase(0, 1);
            return parse(input, node, parent);
        case '(':
            last = new Node(round_bracket, parent);
            input.erase(0, 1);
            return parse(input, last, last);
        case ')':
            if (parent->type != round_bracket) fail("too many close round brackets");
            last = new Node(and_operator, parent->parent);
            last->store.first.child = parent;
            node = parent->parent;
            while (node->store.second.child) node = node->store.second.child;
            node->store.second.child = last;
            input.erase(0, 1);
            parent->store.first.number = number(input);
            return parse(input, last, parent->parent);
        case '[':
            input.erase(0, 1);
            if (input[0] == '^') {
                exclude = true;
                input.erase(0, 1);
            }
            ranges = new std::vector<std::pair<char, char>>;
            while (!input.empty()) {
                if (input[0] == ']') goto skip;
                if (input[0] < ' ' || input[0] > '~') fail("unprintable character provided");
                if (input[0] == '\\') {
                    input.erase(0, 1);
                    temp = special(input);
                    for (std::pair<char, char> range : *temp) ranges->push_back(range);
                    delete temp;
                } else if (input[0] == '-') {
                    if (!buffer) fail("start of range not specified");
                    if (input.length() < 2) fail("end of range not specified");
                    if (buffer > input[1]) fail("range is not in increasing order");
                    ranges->push_back({buffer, input[1]});
                    buffer = 0;
                    input.erase(0, 1);
                } else {
                    if (buffer) ranges->push_back({buffer, buffer});
                    buffer = input[0];
                }
                input.erase(0, 1);
            }
            fail("too many open square brackets");
        skip:;
            if (buffer) ranges->push_back({buffer, buffer});
            input.erase(0, 1);
            compiled.reset();
            for (std::pair<char, char> range : *ranges) {
                for (char i=range.first; i<=range.second; i++) {
                    compiled.set(i-' ');
                }
            }
            delete ranges;
            if (exclude) compiled.flip();
            last = new Node(character, parent);
            last->store.second.content = new std::vector<std::pair<char, char>>;
            buffer = 0;
            for (char i=' '; i<='~'; i++) {
                if (compiled[i-' ']) {
                    if (!buffer) buffer = i;
                } else if (buffer) {
                    last->store.second.content->push_back({buffer, i-1});
                    buffer = 0;
                }
            }
            if (buffer) last->store.second.content->push_back({buffer, '~'});
            node = new Node(and_operator, parent);
            node->store.first.child = last;
            root->store.second.child = node;
            last->store.first.number = number(input);
            return parse(input, node, parent);
        case '.':
            last = new Node(character, parent);
            last->store.second.content = new std::vector<std::pair<char, char>>;
            last->store.second.content->push_back({' ', '~'});
            input.erase(0, 1);
            node = new Node(and_operator, parent);
            node->store.first.child = last;
            root->store.second.child = node;
            last->store.first.number = number(input);
            return parse(input, node, parent);
        case '\\':
            last = new Node(character, parent);
            input.erase(0, 1);
            last->store.second.content = special(input);
            input.erase(0, 1);
            node = new Node(and_operator, parent);
            node->store.first.child = last;
            root->store.second.child = node;
            last->store.first.number = number(input);
            return parse(input, node, parent);
        default:
            if (input[0] < ' ' || input[0] > '~') fail("unprintable character provided");
            last = new Node(character, parent);
            last->store.second.content = new std::vector<std::pair<char, char>>;
            last->store.second.content->push_back({input[0], input[0]});
            input.erase(0, 1);
            node = new Node(and_operator, parent);
            node->store.first.child = last;
            root->store.second.child = node;
            last->store.first.number = number(input);
            return parse(input, node, parent);
    }
}

void count(State* &curr, State* &next, Number number) {
    switch (number) {
        case once:
            break;
        case times:
            curr->transitions[0].push_back(next);
            next->transitions[0].push_back(curr);
            break;
        case plus:
            next->transitions[0].push_back(curr);
            break;
        case question:
            curr->transitions[0].push_back(next);
            break;
    }
}

State* create(Node* root, State* last, std::unordered_map<std::string, State*> &states, std::bitset<'~'-' '+1> &lettersSet) {
    State* prev;
    State* curr;
    State* next;
    std::string name;
    switch (root->type) {
        case starting:
            name = "q" + std::to_string(states.size());
            curr = new State(name, true);
            states[curr->name] = curr;
            return create(root->store.second.child, curr, states, lettersSet);
        case character:
            name = "q" + std::to_string(states.size());
            curr = new State(name, false);
            for (std::pair<char, char> range : *(root->store.second.content)) {
                for (char i=range.first; i<=range.second; i++) {
                    lettersSet.set(i-' ');
                    curr->transitions[i].push_back(last);
                }
            }
            count(curr, last, root->store.first.number);
            states[curr->name] = curr;
            return curr;
        case and_operator:
            if (root->store.second.child) {
                name = "q" + std::to_string(states.size());
                prev = new State(name, false);
                name = "q" + std::to_string(states.size()+1);
                next = new State(name, false);
                states[prev->name] = prev;
                states[next->name] = next;
                next->transitions[0].push_back(last);
                prev->transitions[0].push_back(create(root->store.second.child, next, states, lettersSet));
                return create(root->store.first.child, prev, states, lettersSet);
            }
            name = "q" + std::to_string(states.size());
            curr = new State(name, false);
            states[curr->name] = curr;
            curr->transitions[0].push_back(last);
            return create(root->store.first.child, curr, states, lettersSet);
        case or_operator:
            name = "q" + std::to_string(states.size());
            curr = new State(name, false);
            name = "q" + std::to_string(states.size()+1);
            prev = new State(name, false);
            name = "q" + std::to_string(states.size()+2);
            next = new State(name, false);
            states[curr->name] = curr;
            states[prev->name] = prev;
            states[next->name] = next;
            curr->transitions[0].push_back(create(root->store.first.child, prev, states, lettersSet));
            curr->transitions[0].push_back(create(root->store.second.child, next, states, lettersSet));
            prev->transitions[0].push_back(last);
            next->transitions[0].push_back(last);
            return curr;
        case round_bracket:
            curr = create(root->store.second.child, last, states, lettersSet);
            count(curr, last, root->store.first.number);
            return curr;
    }
    return nullptr;
}

void rexTOnfa(State* &start, std::unordered_map<std::string, State*> &states, std::string &letters, std::string input) {
    Node* root = new Node(starting, nullptr);
    if (parse(input, root, root) != root) fail("too many open round brackets");
    std::unordered_map<std::string, State*> dfaStates;
    std::bitset<'~'-' '+1> lettersSet;

    for (std::pair<std::string, State*> state : states) delete state.second;
    states.clear();
    letters = "";

    start = create(root, nullptr, dfaStates, lettersSet);
    states = dfaStates;
    for (char i=' '; i<='~'; i++) letters += i;
}

#ifdef ALONE
int main(int argc, char** argv) {
    if (argc != 2) fail("no regex provided");
    std::string fileName = argv[1];
    std::ifstream inFile(fileName);
    std::string input;
    std::getline(inFile, input);
    inFile.close();
    Node* root = new Node(starting, nullptr);
    if (parse(input, root, root) != root) fail("too many open round brackets");

    std::unordered_map<std::string, State*> states;
    std::bitset<'~'-' '+1> lettersSet;
    State* start = create(root, nullptr, states, lettersSet);
    std::string letters;
    for (char i=' '; i<='~'; i++) if (lettersSet[i-' ']) letters += i;

    note(start, states, letters, fileName + ".nfa");

    return 0;
}
#endif
