#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function prototypes for the different DFA states
void state0(std::ifstream& file);  // Normal state, reading code
void state1(std::ifstream& file);  // Detected '/', checking if it's a comment
void state2(std::ifstream& file);  // Inside a C++-style comment, ignore until newline
void state3(std::ifstream& file);  // Inside a C-style block comment
void state4(std::ifstream& file);  // Checking for end of C-style block comment

// Vector holding the file paths for test files
const std::vector<std::string> tests = {
   "tests/programming_assignment_1-test_file_1.c",
   "tests/programming_assignment_1-test_file_2.c",
   "tests/programming_assignment_1-test_file_3.c",
   "tests/programming_assignment_1-test_file_4.c",
   "tests/programming_assignment_1-test_file_5.c",
   "tests/programming_assignment_1-test_file_6.c"
};

// State 0: Normal state, reading and printing code character by character
void state0(std::ifstream& file) {
    char ch; 
    file.get(ch);  // Read a character from the file
    if (file.eof()) {  // Check if the end of file is reached
        return;  // End of input, stop the function
    } else if (ch == '/') {  // If the character is '/', move to state1
        return state1(file);
    } else {  // Otherwise, print the character and stay in state0
        std::cout << ch;
        state0(file);
    }
}

// State 1: After hitting a '/', figure out if it's a comment or a division operator
void state1(std::ifstream& file) {
    char ch; 
    file.get(ch);  // Read the next character
    if (file.eof()) {  // Check for end of file
        return; 
    } else if (ch == '/') {  // If it's another '/', we have a C++-style comment, move to state2
        return state2(file);
    } else if (ch == '*') {  // If it's a '*', we have a C-style block comment, move to state3
        return state3(file);
    } else {  // Otherwise, it's just a '/', print it and return to state0
        std::cout << '/';  // Don't forget to print the first '/' since it's not part of a comment
        std::cout << ch;   // Also print the current character
        return state0(file);
    }
}

// State 2: Inside a C++-style line comment, skip characters until newline is reached
void state2(std::ifstream& file) {
    char ch; 
    file.get(ch);  // Read the next character
    if (ch == '\n') {  // If it's a newline, return to state0 to process the next line
        return state0(file);
    }
    return state2(file);  // Otherwise, stay in state2, ignoring characters
}

// State 3: Inside a C-style block comment, look for the closing '*/'
void state3(std::ifstream& file) {
    char ch; 
    file.get(ch);  // Read the next character
    if (ch == '*') {  // If it's a '*', check if it's the start of '*/' (end of comment)
        return state4(file);
    }
    return state3(file);  // Otherwise, stay in state3, ignoring characters
}

// State 4: Looking for '/' to close the C-style block comment
void state4(std::ifstream& file) {
    char ch; 
    file.get(ch);  // Read the next character
    if (ch == '/') {  // If it's '/', the block comment is closed, return to state0
        return state0(file);
    }
    return state3(file);  // Otherwise, continue checking inside the block comment
}

int main() {
    char ch; 
    // Open the first test file from the vector
    std::ifstream file(tests[0]);
    
    if (!file.is_open()) {  // Check if the file was opened successfully
        std::cerr << "Error: Could not open the file " << tests[0] << std::endl;
        return 1;  // Exit with an error code
    }
    // Start in state0 to process the file
    state0(file);
    file.close();  // Close the file after processing

    return 0;  // Exit successfully
}
