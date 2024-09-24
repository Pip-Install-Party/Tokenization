#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

class Tokenizer
{
private:
    int lineCount = 1;

    // Declare states
    void state0(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state1(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state2(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state3(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state4(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state5(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  // Handles character literals
    void state6(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  
    void state7(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  

    void error(const std::string &message, int lineCount);
    bool isValidInteger(const std::string &token);
    
public:
    Tokenizer() {}
    ~Tokenizer() { delete this; };
    void begin(std::istringstream &inputStream, std::ostringstream &buffer) { state0(inputStream, lineCount, buffer); }
};

#endif // TOKENIZER_H/ tokenizer.h
