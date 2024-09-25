
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
    } else if (ch == '/') {
        buffer << "\nToken type: DIVIDE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (isdigit(ch)) {
        std::string number;
        number += ch;
// **********************************************************************************************
//         This needs to be its own state. There should not be any nested if statements.

        // Keep reading until a non-digit character is found.
        while (inputStream.get(ch) && ch != ' '  && ch != ';' && ch != ')' && ch != ']') {
            number += ch;
        }
        
        inputStream.putback(ch);  // Put back the last non-digit character.
    
        // Check if the number is valid.
        if (!isValidInteger(number)) {
            std::cerr << "Syntax error on line " << lineCount << ": invalid integer\n";
            exit(1);
        }

        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: " << number << "\n";
// **********************************************************************************************
        return state0(inputStream, lineCount, buffer);    
    } else if (ch == ',') {
        buffer << "\nToken type: COMMA\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '=') {
// **********************************************************************************************
//         This needs to be its own state. There should not be any nested if statements.
        inputStream.get(ch);
        if (ch == '=') {
            buffer << "\nToken type: BOOLEAN_EQUAL\n";
            buffer << "Token: ==\n";
        } else {
            inputStream.putback(ch);
            buffer << "\nToken type: ASSIGNMENT_OPERATOR\n";
            buffer << "Token: =\n";
        }
        return state0(inputStream, lineCount, buffer);
// **********************************************************************************************
    } else if (ch == '+') {
        buffer << "\nToken type: PLUS\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '-') {
        state2(inputStream, lineCount, buffer);  // Handle minus sign or negative integers
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '>') {
        state6(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '<') {
        state7(inputStream, lineCount, buffer);
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
// **********************************************************************************************
//         This needs to be its own state. There should not be any nested if statements.

        inputStream.get(ch);
        if (ch == '&') {
            buffer << "\nToken type: BOOLEAN_AND\n";
            buffer << "Token: &&\n";
        } else {
            inputStream.putback(ch);
            buffer << "\nToken type: AMPERSAND\n";
            buffer << "Token: &\n";
        }
// **********************************************************************************************
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '"') {
        buffer << "\nToken type: DOUBLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: STRING\n";
        buffer << "Token: ";
        state1(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\'') { // Found a single quote
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n"; // Add single quote to buffer 
        return state5(inputStream, lineCount, buffer);  // Check what the single quote is 
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
// **********************************************************************************************
//         This needs to be its own state. There should not be any nested if statements.

        buffer << ch;  // Add the backslash
        inputStream.get(ch);
        if (ch == 'n') { // Case to add specifically 'n' to buffer
            buffer << "n";
        } else {
            buffer << ch;  // Add other escape character other than /n
        }
// **********************************************************************************************     
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
       buffer << "Token: -" << ch;
       return state3(inputStream, lineCount, buffer);
    } else {
        inputStream.putback(ch);  // Handle hyphen if not part of integer
    }
    buffer << "\nToken type: HYPHEN\n";
    buffer << "Token: -" << "\n";
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

    // End of file reached too early
    if (inputStream.eof()) {
        std::cerr << "Error: Unterminated character literal\n";
        exit(1);
    } else if (ch == '\'') {  // Check for the closing single quote (for empty single quotes) ** not sure if this should be accepted but I am for now **
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: ''\n";  // Handle empty character literal
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\\') {     // Check for escaped characters
        state8(inputStream, lineCount, buffer); // Handle the esc character
    } 
    else { // Found a regular char, not an escape character
        buffer << "\nToken type: CHAR_LITERAL\n";
        buffer << "Token: " << ch << "\n"; // Handle the literal inside the single quotes
    }

    // Check for the closing single quote (to the non empty single quotes)
    inputStream.get(ch); // Why are we getting another character on the same iteration and checking for '\' again? Shouldn't we be calling state5() again instead? Repeated code? 
    if (ch == '\'') {
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n"; // Handle the final character
        return state0(inputStream, lineCount, buffer);
    } else {
        std::cerr << "Error: Invalid character literal\n";
        exit(1);
    }

}

void Tokenizer::state6(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);

    if (ch == '=') {
        buffer << "\nToken type: GT_EQUAL\n";
        buffer << "Token: >=\n";
    } else {
        inputStream.putback(ch);
        buffer << "\nToken type: GREATER_THAN\n";
        buffer << "Token: >\n";
    }
    return;
}

void Tokenizer::state7(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
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

void Tokenizer::state8(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char nextCh;
    inputStream.get(nextCh); // Get the next character after backslash
    
    // Verify that the next character is a valid escape character
    if (nextCh == 'n' || nextCh == 't' || nextCh == '\\'  || nextCh == '0') { // Can add more if needed... 
        buffer << "\nToken type: STRING\n";
        buffer << "Token: \\" << nextCh << "\n";   // Add the escaped character to the buffer
    } else { // Else, not a valid esc char
        std::cerr << "Error: Invalid escape sequence '\\" << nextCh << "\n";
        exit(1);
    }
}


bool Tokenizer::isValidInteger(const std::string& token) {
    try {
        int value = std::stoi(token);
        return std::to_string(value) == token;  
    } catch (const std::out_of_range& e) {
        return false;  
    } catch (const std::invalid_argument& e) {
        return false; 
    }
}

