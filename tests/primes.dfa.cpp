#include <iostream>

bool state_q_3_0_q_5_2(std::string input);
bool state_q_3_1_q_5_1(std::string input);
bool state_q_3_2_q_5_4(std::string input);
bool state_q_3_1_q_5_4(std::string input);
bool state_q_3_1_q_5_0(std::string input);
bool state_q_3_2_q_5_2(std::string input);
bool state_q_3_0_q_5_4(std::string input);
bool state_q_3_2_q_5_0(std::string input);
bool state_q_3_2_q_5_1(std::string input);
bool state_q_3_1_q_5_2(std::string input);
bool state_q_3_0_q_5_3(std::string input);
bool state_q_3_1_q_5_3(std::string input);
bool state_q_3_0_q_5_0_q_start_q_3_0_q_5_0(std::string input);
bool state_q_3_2_q_5_3(std::string input);
bool state_q_3_0_q_5_1(std::string input);

bool state_q_3_0_q_5_2(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_0_q_5_4(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_1_q_5_0(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_1_q_5_1(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_2_q_5_2(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_0_q_5_3(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_2_q_5_4(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_1_q_5_3(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_2_q_5_4(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_1_q_5_4(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_2_q_5_3(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_0_q_5_4(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_1_q_5_0(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_2_q_5_0(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_0_q_5_1(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_2_q_5_2(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_1_q_5_4(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_2_q_5_0(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_0_q_5_4(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_0_q_5_3(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_1_q_5_4(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_2_q_5_0(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_1_q_5_0(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_2_q_5_1(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_2_q_5_1(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_1_q_5_2(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_2_q_5_3(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_1_q_5_2(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_2_q_5_4(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_0_q_5_0_q_start_q_3_0_q_5_0(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_0_q_5_3(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_0_q_5_1(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_1_q_5_2(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_1_q_5_3(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_2_q_5_1(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_0_q_5_2(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_0_q_5_0_q_start_q_3_0_q_5_0(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_0_q_5_0_q_start_q_3_0_q_5_0(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_1_q_5_1(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_2_q_5_3(std::string input) {
	if (input.empty()) return 0;
	switch(input[0]) {
		case '0':
			return state_q_3_1_q_5_1(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_2_q_5_2(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

bool state_q_3_0_q_5_1(std::string input) {
	if (input.empty()) return 1;
	switch(input[0]) {
		case '0':
			return state_q_3_0_q_5_2(input.substr(1, input.length()-1));
		case '1':
			return state_q_3_1_q_5_3(input.substr(1, input.length()-1));
		default:
			return false;
	}
}

int main(int argc, char** argv) {
	if (argc != 2) return -1;
	if (state_q_3_0_q_5_0_q_start_q_3_0_q_5_0(argv[1])) std::cout << "valid string" << std::endl;
	return 0;
}
