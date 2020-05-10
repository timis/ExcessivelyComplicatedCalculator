#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "AST.h"

using namespace std;

class Parser {
    public:
        Parser();
        Operation parse_operation();
        AST* parse_expression();
        AST* parse(string inputStr);

    private:
        string str;
        int index;
        bool isNumeric(char c);
};


#endif