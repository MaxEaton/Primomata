#include <iostream>

bool state_q_15_14(std::string input);
bool state_q_15_13(std::string input);
bool state_q_15_11(std::string input);
bool state_q_15_10(std::string input);
bool state_q_15_8(std::string input);
bool state_q_15_7(std::string input);
bool state_q_15_9(std::string input);
bool state_q_15_6(std::string input);
bool state_q_15_5(std::string input);
bool state_q_15_4(std::string input);
bool state_q_15_12(std::string input);
bool state_q_15_3(std::string input);
bool state_q_15_2(std::string input);
bool state_q_15_1(std::string input);
bool state_q_15_0(std::string input);

bool state_q_15_14(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_13(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_14(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_13(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_11(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_12(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_11(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_7(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_8(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_10(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_5(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_6(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_8(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_1(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_2(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_7(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_14(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_0(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_9(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_3(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_4(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_6(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_13(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_12(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_5(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_11(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_10(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_4(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_9(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_8(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_12(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_15_9(input.substr(1, input.length()-1));
		case '1':
			return state_q_15_10(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_3(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_7(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_6(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_2(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_5(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_4(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_1(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '1':
			return state_q_15_3(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_2(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_15_0(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '1':
			return state_q_15_1(input.substr(1, input.length()-1));
		case '0':
			return state_q_15_0(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

int main(int argc, char** argv) {
	if (argc != 2) return -1;
	if (state_q_15_0(argv[1])) std::cout << "valid string" << std::endl;
	return 0;
}
