#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

// The Tokenizer class is responsible for breaking down a stream of input into various tokens,
// using multiple states to process different types of input, such as numbers, operators, and identifiers.
class Tokenizer
{
private:
    // Variable to track the current line number in the input stream, starting from 1.
    int lineCount = 1;

    // Declare all the different states of the tokenizer. Each state processes a different
    // type of token or character in the input stream.
    
    // Main state that branches to other states based on input.
    void state0(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to handle string literals (enclosed by double quotes).
    void state1(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to handle the minus sign and potentially negative numbers.
    void state2(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to process a sequence of digits, forming integers.
    void state3(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to process identifiers (alphanumeric characters and underscores).
    void state4(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to handle character literals (enclosed by single quotes).
    void state5(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  
    
    // State to process the '>' (greater than) operator and '>=' (greater than or equal to).
    void state6(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  
    
    // State to process the '<' (less than) operator and '<=' (less than or equal to).
    void state7(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  
    
    // State to process escape sequences in string literals.
    void state8(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer); 

    // State to process escape characters (like '\n') after the backslash in strings.
    void state9(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to process boolean AND ('&&') or bitwise AND ('&').
    void state10(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to check for the closing single quote in character literals.
    void state11(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to process a continuous sequence of digits (integer values).
    void state12(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to process the assignment operator ('=') and equality operator ('==').
    void state13(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);

    // State to validate the termination of integer tokens.
    void state14(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  
    
public:
    // Constructor for the Tokenizer class. Initializes an empty object.
    Tokenizer() {}

    // Destructor for the Tokenizer class.
    // Cleans up resources used by the class (deletes this object).
    ~Tokenizer() { delete this; };

    // Begin the tokenization process from the initial state (state0).
    // This method takes the input stream and a buffer to store token output.
    void begin(std::istringstream &inputStream, std::ostringstream &buffer) { state0(inputStream, lineCount, buffer); }
};

#endif // TOKENIZER_H

