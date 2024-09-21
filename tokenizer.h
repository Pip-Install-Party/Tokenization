/
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <sstream>

class Tokenizer
{
private:
    int lineCount = 0;

    // Declare states
    void state0(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state1(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state2(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state3(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state4(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);
    void state5(std::istringstream &inputStream, int &lineCount, std::ostringstream &buffer);  // Handles character literals
    void error(const std::string &message, int lineCount);

public:
    Tokenizer() {}
    ~Tokenizer() {}
    void begin(std::istringstream &inputStream, std::ostringstream &buffer) { state0(inputStream, lineCount, buffer); }
};

#endif // TOKENIZER_H/ tokenizer.h
#ifndef TOKENIZER_H // include guard
#define TOKENIZER_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream> 

class Tokenizer
{
private:
    int lineCount = 0;
    void state0(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer);
    void state1(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer);
    void state2(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer);
    void state3(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer);
    void state4(std::istringstream &inputStream, int &lineCount, std::ostringstream& buffer);

public:
    Tokenizer() {}
    ~Tokenizer() { delete this; };
    void begin(std::istringstream &inputStream, std::ostringstream& buffer) { state0(inputStream, lineCount, buffer); }
};

#endif /* TOKENIZER */
