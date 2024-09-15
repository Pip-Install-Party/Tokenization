#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream> 

#include "commentDFA.h"

// Vector holding the file paths for test files
const std::filesystem::path tests[] = {
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_1.c",
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_2.c",
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_3.c",
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_4.c",
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_5.c",
   "Tests/programming_assignment_1_tests/programming_assignment_1-test_file_6.c",

   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_1.c",
   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_2.c",
   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_3.c",
   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_4.c",
   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_5.c",
   "Tests/programming_assignment_2_tests/programming_assignment_2-test_file_6.c",
};

// Main program function that handles user prompt, file opening/closing, and initial state
int main() {
    char ch;
    int assignment_num;
    int filenum;
    std::ostringstream buffer;

    // Prompt user for what programming assignment they want to test
    std::cout << "Which programming assignment would you like to test?\n\n"
         "Type 1 for Programming Assignment 1: Ignore Comments\n"
         "Type 2 for Programming Assignment 2: Tokenization\n"
         "Selection: ";
    std::cin >> assignment_num;

    // Logic to execute a specific assignment and their respective files
    if (assignment_num == 1) {
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
    }
    else if(assignment_num == 2) {
        std::cout << "Assignment 2";
    }
    else {
        std::cout << "No matching assignments exist for " << assignment_num << ".\n";
        return 1;
    }
    

    return 0;  // Exit successfully
}
