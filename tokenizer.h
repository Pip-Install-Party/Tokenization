// tokenizer.h
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
    void Tokenizer::state0(std::istringstream &inputStream);

public:
    Tokenizer() {}
    ~Tokenizer() { delete this; };
    void begin(std::istringstream &inputStream) { state0(inputStream); }
};

#endif /* TOKENIZER */
