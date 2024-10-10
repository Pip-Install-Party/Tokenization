#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "tokenizer.h"

// The Parser class is responsible for utilizing a vector of tokens created with the tokenizer
// and converting it into a concrete syntax tree using a recursive descent parsing technique.
// This class utilizes a LCRS binary tree to store the CST.
class Parser 
{
private:
    // Vector holding all of the tokens in order from the tokenizer.
    std::vector<Token> tokenList;

    // Variable to track the current position in the token list.
    int index;
    

public:
    // Parser construtor that is passed a vector of tokens from tokenizer.
    Parser(const std::vector<Token>& tokenList);

    // Begin the parsing process.
    void begin();
};

#endif // PARSER_H