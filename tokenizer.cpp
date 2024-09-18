// tokenize.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream> 
#include "tokenizer.h"

// Base state. Branch elsewhere from here. 
void Tokenizer::state0(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer){
    char ch; 
    inputStream.get(ch);

    if (inputStream.eof()) {  // Check if the end of file is reached
        return;  // End of input, stop the function
    } else if (ch == '\n'){
       lineCount++;
       return state0(inputStream, lineCount, buffer);
    } else if (ch == '('){
        buffer << "\nToken type: L_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ')'){
        buffer << "\nToken type: R_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer); 
    } else if (ch == '{'){
        buffer << "\nToken type: L_BRACE \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);    
    } else if (ch == '}'){
        buffer << "\nToken type: R_BRACE \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ';'){
        buffer << "\nToken type: SEMICOLON \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '='){
        buffer << "\nToken type: ASSIGNMENT_OPERATOR \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '"'){
        buffer << "\nToken type: DOUBLE_QUOTE \n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: STRING \n";
        buffer << "Token: ";
        return state1(inputStream, lineCount, buffer);

    } else if (ch == '\''){
        buffer << "\nToken type: SINGLE_QUOTE \n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: STRING \n";
        buffer << "Token: ";
        state1(inputStream, lineCount, buffer);
        buffer << "\n";
        return;
    } else if (ch == ','){
        buffer << "\nToken type: COMMA \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '-'){
        return state2(inputStream, lineCount, buffer);
    } else if (isalpha(ch)){
        buffer << "\nToken type: IDENTIFIER \n";
        buffer << "Token: " << ch;
        state4(inputStream, lineCount, buffer);
        buffer << "\n";
        return;
    } else if (isdigit(ch)){
        buffer << "\nToken type: INTEGER \n";
        buffer << "Token: " << ch;
        state3(inputStream, lineCount, buffer);
        buffer << "\n";
        return;
    } else if (ch == ' '){
        return state0(inputStream, lineCount, buffer);
    } 
    std::cerr << "Unrecognized token: " << ch << " Terminating...";
    exit(1);
}

void Tokenizer::state1(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer){
    char ch; 
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Check if the end of file is reached
        std::cerr << "Nah bro, that ain't right"; // Found end of file unexectedly
        exit(1);
    } else if (ch == '\n'){
       lineCount++;
    } else if (ch == '"') {
        buffer << "\n\nToken type: DOUBLE_QUOTE \n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    }
    buffer << ch; 
    state1(inputStream, lineCount, buffer);
}

//Check if - is part of int or just - 
void Tokenizer::state2(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer){
    char ch; 
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Check if the end of file is reached
        std::cerr << "Nah bro, that ain't right"; // Found end of file unexectedly
        exit(1);
    } else if (ch == '\n'){
       lineCount++;
    } else if (isdigit(ch)) {
       buffer << "\nToken type: INTEGER \n";
       buffer << "Token: -" << ch;
       return state3(inputStream, lineCount, buffer);
    }
    inputStream.putback(ch);
     buffer << "\nToken type: HEIFEN \n";
     buffer << "Token: -" << "\n";
     state0(inputStream, lineCount, buffer);
  
}
// Process integer 
void Tokenizer::state3(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer){
    char ch; 
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Check if the end of file is reached
        std::cerr << "Nah bro, that ain't right"; // Found end of file unexectedly
        exit(1);
    } else if (ch == '\n'){
       lineCount++;
    } else if (!isdigit(ch)) {
        buffer << "\n";
       inputStream.putback(ch);
       return state0(inputStream, lineCount, buffer);
    }
    buffer << ch;
    return state3(inputStream, lineCount, buffer);
}

// Process identifier 
void Tokenizer::state4(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer){
    char ch; 
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Check if the end of file is reached
        std::cerr << "Nah bro, that ain't right"; // Found end of file unexectedly
        exit(1);
    } else if (ch == '\n'){
        lineCount++;
    } else if (!isalpha(ch)) {
        inputStream.putback(ch);
        buffer << "\n";
        return state0(inputStream, lineCount, buffer);
    }
    buffer << ch;
    return state4(inputStream, lineCount, buffer);
}