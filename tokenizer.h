// tokenizer.h
#ifndef TOKENIZER_H // include guard
#define TOKENIZER_H

#include <iostream>

class Tokenizer
{
private:
    void Tokenizer::state0(std::ifstream& file, int& lineCount, std::ostringstream& buffer);

public:
    Tokenizer() {}
    ~Tokenizer() { delete this; };
    void begin(std::ifstream& file, int lineCount, std::ostringstream& buffer) { state0(file, lineCount, buffer); }
};

#endif /* TOKENIZER */
