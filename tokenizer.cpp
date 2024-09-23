
//**************
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include "tokenizer.h"

// Base state. Branch elsewhere from here.
void Tokenizer::state0(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    if (inputStream.eof()) {
        return;  // End of input, stop the function
    } else if (ch == '\n') {
        lineCount++;
        return state0(inputStream, lineCount, buffer);  // Handle newlines (increment line count)
    } else if (isspace(ch)) {  // Handle all whitespace characters (space, tab, etc.)
        return state0(inputStream, lineCount, buffer);  // Ignore whitespace and continue
    } else if (ch == '(') {
        buffer << "\nToken type: L_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ')') {
        buffer << "\nToken type: R_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '{') {
        buffer << "\nToken type: L_BRACE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '}') {
        buffer << "\nToken type: R_BRACE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '[') {
        buffer << "\nToken type: L_BRACKET\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ']') {
        buffer << "\nToken type: R_BRACKET\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ';') {
        buffer << "\nToken type: SEMICOLON\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (isdigit(ch)) {
        std::string number;
        number += ch;
    
        // Keep reading until a non-digit character is found.
        while (inputStream.get(ch) && isdigit(ch)) {
            number += ch;
        }
        
        inputStream.putback(ch);  // Put back the last non-digit character.
    
        // Check if the number is valid.
        if (!isValidInteger(number)) {
            std::cerr << "Syntax error on line " << lineCount << ": invalid integer\n";
            return;
        }
    
        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: " << number << "\n";
        return state0(inputStream, lineCount, buffer);    
    } else if (ch == ',') {
        buffer << "\nToken type: COMMA\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '=') {
        inputStream.get(ch);
        if (ch == '=') {
            buffer << "\nToken type: BOOLEAN_EQUAL\n";
            buffer << "Token:      ==\n";
        } else {
            inputStream.putback(ch);
            buffer << "\nToken type: ASSIGNMENT_OPERATOR\n";
            buffer << "Token:      =\n";
        }
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '+') {
        buffer << "\nToken type: PLUS\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '-') {
        return state2(inputStream, lineCount, buffer);  // Handle minus sign or negative integers
    } else if (ch == '>') {
        buffer << "\nToken type: GREATER_THAN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '<') {
        state6(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '*') {
        buffer << "\nToken type: ASTERISK\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '%') {
        buffer << "\nToken type: MODULO\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\\') {
        buffer << "\nToken type: BACKSLASH\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '&') {
        inputStream.get(ch);
        if (ch == '&') {
            buffer << "\nToken type: BOOLEAN_AND\n";
            buffer << "Token:      &&\n";
        } else {
            inputStream.putback(ch);
            buffer << "\nToken type: AMPERSAND\n";
            buffer << "Token:      &\n";
        }
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '"') {
        buffer << "\nToken type: DOUBLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: STRING\n";
        buffer << "Token:      ";
        state1(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\'') {
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: CHAR_LITERAL\n";
        buffer << "Token:      ";
        return state5(inputStream, lineCount, buffer);  // New state for handling character literals
    } else if (ch == '_') {
        buffer << "\nToken type: UNDERSCORE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (isalpha(ch) || ch == '_') {
        buffer << "\nToken type: IDENTIFIER\n";
        buffer << "Token: " << ch;
        state4(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
     } else if (isdigit(ch)) {
        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: " << ch;
        state3(inputStream, lineCount, buffer);
        buffer << "\n";
        return state0(inputStream, lineCount, buffer);
     } 
    
    std::cerr << "Unrecognized token: '" << ch << "' at line " << lineCount << " - Terminating...\n";
    exit(1);
}

// Handle string literals enclosed by double quotes
void Tokenizer::state1(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // End of file
        std::cerr << "Error: Unterminated string\n";
        exit(1);
    } else if (ch == '"') {
        buffer << "\n";
        buffer << "\nToken type: DOUBLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        return;
    } else if (ch == '\\') {  // Handle escape characters in strings
        buffer << ch;  // Add the backslash
        inputStream.get(ch);
        if (ch == 'n') { // Case to add specifically 'n' to buffer
            buffer << "n";
        } else {
            buffer << ch;  // Add other escape character other than /n
        }
    } else if (ch == '\n') { // Real newline in input
        lineCount++;
        std::cerr << "Error: Unterminated string on line " << lineCount << "\n";
        exit(1);
    } else {
        buffer << ch;
    }
    state1(inputStream, lineCount, buffer);
}

// Check if - is part of int or just -
void Tokenizer::state2(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // End of file
        std::cerr << "Error: Unterminated hyphen\n";
        exit(1);
    } else if (ch == '\n') {
        lineCount++;
    } else if (isdigit(ch)) {
       buffer << "\nToken type: INTEGER\n";
       buffer << "Token:      -" << ch;
       return state3(inputStream, lineCount, buffer);
    }
    
    inputStream.putback(ch);  // Handle hyphen if not part of integer
    buffer << "\nToken type: HYPHEN\n";
    buffer << "Token:      -" << "\n";
    return;
}

// Process integer
void Tokenizer::state3(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // End of file
        std::cerr << "Error: Unterminated integer\n";
        exit(1);
    } else if (!isdigit(ch)) {
        buffer << "\n";
        inputStream.putback(ch);  // Return non-integer character to the stream
        return state0(inputStream, lineCount, buffer);
    }
    buffer << ch;
    state3(inputStream, lineCount, buffer);
}

// Process identifier
void Tokenizer::state4(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // End of file
        std::cerr << "Error: Unterminated identifier\n";
        exit(1);
    } else if (!isalnum(ch) && ch != '_') {  // Allow underscores in identifiers
        inputStream.putback(ch);
        buffer << "\n";
        return;
    }
    buffer << ch;
    return state4(inputStream, lineCount, buffer);
}

// Handle character literals enclosed by single quotes
void Tokenizer::state5(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);

    if (inputStream.eof()) {
        std::cerr << "Error: Unterminated character literal\n";
        exit(1);
    } else if (ch == '\'') {
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        return;
    } else if (ch == '\\') {
        buffer << ch;  // Escaped characters in character literals
        inputStream.get(ch);
        buffer << ch;
        inputStream.get(ch);
    } else {
        buffer << ch;
        inputStream.get(ch);  // Close the character literal
        if (ch == '\'') {
            buffer << "\nToken type: SINGLE_QUOTE\n";
            buffer << "Token: " << ch << "\n";
            return;
        } else {
            std::cerr << "Error: Invalid character literal\n";
            exit(1);
        }
    }
}

void Tokenizer::state6(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);

    if (ch == '=') {
        buffer << "\nToken type: LT_EQUAL\n";
        buffer << "Token: <=\n";
    } else {
        inputStream.putback(ch);
        buffer << "\nToken type: LESS_THAN\n";
        buffer << "Token: <\n";
    }
    return;
}

bool Tokenizer::isValidInteger(const std::string& token) {
    try {
        // Attempt to parse the token as an integer.
        int value = std::stoi(token);
        return true;  // If parsing succeeds, the integer is valid.
    } catch (const std::out_of_range& e) {
        return false;  // Number is too large or small.
    } catch (const std::invalid_argument& e) {
        return false;  // The token contains invalid characters.
    }
}

