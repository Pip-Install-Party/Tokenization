#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::vector<std::string> tests = {
    "tests/programming_assignment_1-test_file_1.c",
    "tests/programming_assignment_1-test_file_2.c",
    "tests/programming_assignment_1-test_file_3.c",
    "tests/programming_assignment_1-test_file_4.c",
    "tests/programming_assignment_1-test_file_5.c",
    "tests/programming_assignment_1-test_file_6.c"
};

int main() {
    for (int i = 0; i < tests.size(); i++){
        
        std::ifstream file(tests[i]);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file " << tests[i] << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }

    return 0;
}