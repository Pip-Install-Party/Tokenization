// tokenize.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream> 
#include "tokenizer.h"

// Base state. Branch elsewhere from here. 
void Tokenizer::state0(std::istringstream &inputStream){
    char ch; 
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Check if the end of file is reached
        return;  // End of input, stop the function
    } 
}