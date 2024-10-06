#include "parser.h"

Parser::Parser(const std::vector<Token>& tokenList)
{
    this->tokenList = tokenList;

    this->index = 0;
}

