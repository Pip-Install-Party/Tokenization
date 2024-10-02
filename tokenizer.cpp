//**************
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <set>
#include "tokenizer.h"

// Base state. Branch elsewhere from here.
// This state processes characters, numbers, and punctuation, directing control to specific states based on input.
void Tokenizer::state0(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character from the input stream.
    
    if (inputStream.eof()) {  // End of input, stop processing.
        return;
    } else if (ch == '\n') {  // Handle newlines by incrementing the line count.
        lineCount++;
        return state0(inputStream, lineCount, buffer);
    } else if (isspace(ch)) {  // Skip all whitespace characters (space, tab, etc.).
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '(') {  // Handle left parentheses.
        buffer << "\nToken type: L_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ')') {  // Handle right parentheses.
        buffer << "\nToken type: R_PAREN\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '{') {  // Handle left braces.
        buffer << "\nToken type: L_BRACE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '}') {  // Handle right braces.
        buffer << "\nToken type: R_BRACE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '[') {  // Handle left brackets.
        buffer << "\nToken type: L_BRACKET\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ']') {  // Handle right brackets.
        buffer << "\nToken type: R_BRACKET\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == ';') {  // Handle semicolons.
        buffer << "\nToken type: SEMICOLON\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '/') {  // Handle division operator.
        buffer << "\nToken type: DIVIDE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (isdigit(ch)) {  // Handle integer literals.
        inputStream.putback(ch);  // Put character back for further processing.
        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: ";
        state12(inputStream, lineCount, buffer);  // Transition to state12 to process the number.
        buffer << "\n";
        return state0(inputStream, lineCount, buffer);    
    } else if (ch == ',') {  // Handle commas.
        buffer << "\nToken type: COMMA\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '=') {  // Handle assignment or equality.
        state13(inputStream, lineCount, buffer);  // Transition to state13 for further processing.
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '+') {  // Handle plus operator.
        buffer << "\nToken type: PLUS\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '-') {  // Handle minus sign or negative integers.
        state2(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '>') {  // Handle greater than or greater than or equal to operator.
        state6(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '<') {  // Handle less than or less than or equal to operator.
        state7(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '*') {  // Handle asterisk operator.
        buffer << "\nToken type: ASTERISK\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '%') {  // Handle modulo operator.
        buffer << "\nToken type: MODULO\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\\') {  // Handle backslash character.
        buffer << "\nToken type: BACKSLASH\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '&') {  // Handle boolean AND or bitwise AND.
        state10(inputStream, lineCount, buffer);
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '"') {  // Handle double quotes (beginning of a string literal).
        buffer << "\nToken type: DOUBLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        buffer << "\nToken type: STRING\n";
        buffer << "Token: ";
        state1(inputStream, lineCount, buffer);  // Transition to state1 to handle the string.
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '\'') {  // Handle single quotes (character literals).
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        state5(inputStream, lineCount, buffer);  // Transition to state5 for single quotes.
        return state0(inputStream, lineCount, buffer);
    } else if (ch == '_') {  // Handle underscores.
        buffer << "\nToken type: UNDERSCORE\n";
        buffer << "Token: " << ch << "\n";
        return state0(inputStream, lineCount, buffer);
    } else if (isalpha(ch) || ch == '_') {  // Handle identifiers (letters or underscores).
        buffer << "\nToken type: IDENTIFIER\n";
        buffer << "Token: " << ch;
        state4(inputStream, lineCount, buffer);  // Transition to state4 to process the identifier.
        return state0(inputStream, lineCount, buffer);
     } else if (isdigit(ch)) {  // Handle digits (numbers).
        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: " << ch;
        state3(inputStream, lineCount, buffer);  // Transition to state3 for further processing.
        buffer << "\n";
        return state0(inputStream, lineCount, buffer);
     } 
    
    // If an unrecognized token is encountered, output an error message and terminate.
    std::cerr << "Unrecognized token: '" << ch << "' at line " << lineCount << " - Terminating...\n";
    exit(1);
}

// Handle string literals enclosed by double quotes
void Tokenizer::state1(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);
    
    if (inputStream.eof()) {  // Handle the end of the file.
        std::cerr << "Error: Unterminated string\n";
        exit(1);
    } else if (ch == '"') {  // End of the string literal.
        buffer << "\n";
        buffer << "\nToken type: DOUBLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";
        return;
    } else if (ch == '\\') {  // Handle escape characters inside the string.
        buffer << ch;  // Add the backslash to the buffer.
        state8(inputStream, lineCount, buffer);  // Transition to state9 to handle the escape sequence.
    } else if (ch == '\n') {  // Handle newlines within the string (error).
        lineCount++;
        std::cerr << "Error: Unterminated string on line " << lineCount << "\n";
        exit(1);
    } else {  // Add characters to the buffer as part of the string.
        buffer << ch;
    }
    state1(inputStream, lineCount, buffer);  // Continue processing the string.
}

// Check if - is part of a number or just a minus sign.
void Tokenizer::state2(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (inputStream.eof()) {  // End of file, return error for unterminated hyphen.
        std::cerr << "Error: Unterminated hyphen\n";
        exit(1);
    } else if (ch == '\n') {  // Handle newline, increment line count.
        lineCount++;
    } else if (isdigit(ch)) {  // Handle negative numbers.
        buffer << "\nToken type: INTEGER\n";
        buffer << "Token: -" << ch;
        return state3(inputStream, lineCount, buffer);  // Transition to state3 for further number processing.
    } else {
        inputStream.putback(ch);  // If it's not part of a number, put the character back.
    }
    buffer << "\nToken type: MINUS\n";
    buffer << "Token: -" << "\n";
    return;
}

// Process integer tokens.
void Tokenizer::state3(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.
    
    if (inputStream.eof()) {  // End of file, handle error for unterminated integer.
        std::cerr << "Error: Unterminated integer\n";
        exit(1);
    } else if (!isdigit(ch)) {  // If not a digit, stop processing the integer.
        buffer << "\n";
        inputStream.putback(ch);  // Put the non-integer character back.
        return state0(inputStream, lineCount, buffer);  // Return to state0.
    }
    buffer << ch;  // Add digit to the buffer.
    state3(inputStream, lineCount, buffer);  // Recursively continue processing digits.
}

// Process identifier tokens (letters and underscores).
void Tokenizer::state4(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (inputStream.eof()) {  // End of file, handle error for unterminated identifier.
        std::cerr << "Error: Unterminated identifier\n";
        exit(1);
    } else if (!isalnum(ch) && ch != '_') {  // If it's not a valid identifier character, stop.
        inputStream.putback(ch);  // Put the character back.
        buffer << "\n";
        return;
    }
    buffer << ch;  // Add character to the identifier token.
    return state4(inputStream, lineCount, buffer);  // Continue processing the identifier.
}

// Handle character literals enclosed by single quotes.
void Tokenizer::state5(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (inputStream.eof()) {  // End of file, error for unterminated character literal.
        std::cerr << "Error: Unterminated character literal\n";
        exit(1);
    } else if (ch == '\'') {  // Empty character literal, handle it.
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: ''\n";  // Empty literal.
        return;
    } else if (ch == '\\') {  // Escape character inside the literal.
        state8(inputStream, lineCount, buffer);  // Handle escape sequences.
    } else {  // Handle regular character literals.
        buffer << "\nToken type: STRING\n";
        buffer << "Token: " << ch << "\n";
    }
    state11(inputStream, lineCount, buffer);  // Check for the closing single quote.
}

// Process greater-than operator and greater-than-or-equal-to operator.
void Tokenizer::state6(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (ch == '=') {  // Handle '>=' (greater than or equal to).
        buffer << "\nToken type: GT_EQUAL\n";
        buffer << "Token: >=\n";
    } else {  // Handle '>' (greater than).
        inputStream.putback(ch);  // Put character back if not '='.
        buffer << "\nToken type: GT\n";
        buffer << "Token: >\n";
    }
    return;
}

// Process less-than operator and less-than-or-equal-to operator.
void Tokenizer::state7(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (ch == '=') {  // Handle '<=' (less than or equal to).
        buffer << "\nToken type: LT_EQUAL\n";
        buffer << "Token: <=\n";
    } else {  // Handle '<' (less than).
        inputStream.putback(ch);  // Put character back if not '='.
        buffer << "\nToken type: LT\n";
        buffer << "Token: <\n";
    }
    return;
}

// Handle escape sequences inside string literals (e.g., '\n', '\t').
void Tokenizer::state8(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    // Set of valid escape characters.
    const std::set<char> validEscapeChars = {'n', 't', '\\', '0'};
    
    char ch;
    inputStream.get(ch);  // Get the character after the backslash.

    if (validEscapeChars.find(ch) != validEscapeChars.end()) {
        buffer << "\nToken type: STRING\n";
        buffer << "Token: \\" << ch << "\n";  // Add valid escape sequence to the buffer.
    } else {
        std::cerr << "Error: Invalid escape sequence '\\" << ch << "' on line " << lineCount << "\n";
        exit(1);  // Terminate on invalid escape sequence.
    }
}

// Handle boolean AND (&&) and bitwise AND (&).
void Tokenizer::state10(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (ch == '&') {  // Handle boolean AND (&&).
        buffer << "\nToken type: BOOLEAN_AND\n";
        buffer << "Token: &&\n";
    } else {  // Handle bitwise AND (&).
        inputStream.putback(ch);  // Put character back if not another '&'.
        buffer << "\nToken type: AMPERSAND\n";
        buffer << "Token: &\n";
    }
}

// Check for the closing single quote for character literals.
void Tokenizer::state11(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (ch == '\'') {  // Handle closing single quote.
        buffer << "\nToken type: SINGLE_QUOTE\n";
        buffer << "Token: " << ch << "\n";  // Closing quote.
        return;
    } else {  // Handle invalid character literals.
        std::cerr << "Error: Invalid character literal\n";
        exit(1);
    }
}

// Process sequences of digits (integer values).
void Tokenizer::state12(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    // Keep reading digits until a non-digit character is found.
    if (!isdigit(ch)) {
        inputStream.putback(ch);  // Put back the non-digit character.
        state14(inputStream, lineCount, buffer);  // Transition to state14 to validate.
        return;
    }
    buffer << ch;  // Add digit to the buffer.
    state12(inputStream, lineCount, buffer);  // Continue processing digits.
    return;
}

// Process assignment '=' and equality '=='.
void Tokenizer::state13(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    if (ch == '=') {  // Handle equality '=='.
        buffer << "\nToken type: BOOLEAN_EQUAL\n";
        buffer << "Token: ==\n";
    } else {  // Handle assignment '='.
        inputStream.putback(ch);  // Put back the character if it's not another '='.
        buffer << "\nToken type: ASSIGNMENT_OPERATOR\n";
        buffer << "Token: =\n";
    }
    return;
}

// Check and validate the termination of integer tokens.
void Tokenizer::state14(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer) {
    char ch;
    inputStream.get(ch);  // Get the next character.

    // Ensure that the number is followed by a valid token terminator (space, semicolon, closing parenthesis, or bracket).
    if (ch != ' ' && ch != ';' && ch != ')' && ch != ']') {
        std::cerr << "Syntax error on line " <<  lineCount << ": invalid integer\n";
        exit(1);  // Terminate on invalid character after integer.
    }

    // If it's a valid token terminator, put the character back into the stream for further processing.
    inputStream.putback(ch);
    return;
}

