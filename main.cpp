#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream> 

#include "commentDFA.h"

// Vector holding the file paths for test files
const std::filesystem::path tests[] = {
   "Tests/programming_assignment_1-test_file_1.c",
   "Tests/programming_assignment_1-test_file_2.c",
   "Tests/programming_assignment_1-test_file_3.c",
   "Tests/programming_assignment_1-test_file_4.c",
   "Tests/programming_assignment_1-test_file_5.c",
   "Tests/programming_assignment_1-test_file_6.c"
};

// Main program function that handles user prompt, file opening/closing, and initial state
int main() {
    char ch;
    int filenum;
    std::ostringstream buffer;

    // Prompt user for what file they want to remove comments
    std::cout << "Which file would you like to remove comments from?\n\n"
		"Type 1 for programming_assignment_1-test_file_1.c\n"
   		"Type 2 for programming_assignment_1-test_file_2.c\n"
   		"Type 3 for programming_assignment_1-test_file_3.c\n"
   		"Type 4 for programming_assignment_1-test_file_4.c\n"
   		"Type 5 for programming_assignment_1-test_file_5.c\n"
   		"Type 6 for programming_assignment_1-test_file_6.c\n"
        "Selection: ";
    std::cin >> filenum;
	filenum -= 1;

    // Open the first test file from the vector
    std::ifstream file(tests[filenum]);
    
    if (!file.is_open()) {  // Check if the file was opened successfully
        std::cerr << "Error: Could not open the file " << tests[filenum] << std::endl;
        return 1;  // Exit with an error code
    }
    commentDFA *removeComments = new commentDFA();
    // Start in state0 to process the file
    removeComments->begin(file, buffer);
    file.close();  // Close the file after processing

    std::cout  << "\nResulting File:" << std::endl;
    std::cout << buffer.str();

    return 0;  // Exit successfully
}
