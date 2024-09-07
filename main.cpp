#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void state0(std::ifstream& file);
void state1(std::ifstream& file);
void state2(std::ifstream& file);
void state3(std::ifstream& file);
void state4(std::ifstream& file);

const std::vector<std::string> tests = {
   "tests/programming_assignment_1-test_file_1.c",
   "tests/programming_assignment_1-test_file_2.c",
   "tests/programming_assignment_1-test_file_3.c",
   "tests/programming_assignment_1-test_file_4.c",
   "tests/programming_assignment_1-test_file_5.c",
   "tests/programming_assignment_1-test_file_6.c"
};

void state0(std::ifstream& file) {
    char ch; 
    file.get(ch); 
    if (file.eof()) {
        return; 
    } else if (ch == '/') {
        return state1(file);
    } else {
        std::cout << ch;
        state0(file);
    }
}
void state1(std::ifstream& file) {
    char ch; 
    file.get(ch); 
    if (file.eof()) {
        return; 
    } else if (ch == '/') {
        return state2(file);
    } else if (ch == '*') {
        return state3(file);
    } else {
        std::cout << ch;
        return state0(file);
    }
}
void state2(std::ifstream& file) {
    char ch; 
    file.get(ch); 
    if (ch == '\n') {
        return state0(file);
    }
    return state2(file);
}
void state3(std::ifstream& file) {
    char ch; 
    file.get(ch); 
    if (ch == '*') {
        return state4(file);
    }
    return state3(file);
}
void state4(std::ifstream& file) {
    char ch; 
    file.get(ch); 
    if (ch == '/') {
        return state0(file);
    }
    return state3(file);
}

int main() {
    char ch; 
    std::ifstream file(tests[0]);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << tests[0] << std::endl;
        return 1;
    }
    state0(file);
    file.close();

    return 0;
}