#ifndef AST_H
#define AST_H

#include <string>
using namespace std;

enum Operation {
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    MOD,
    ERROR,
    VALUE
};

static string enumToOperator[] = {"+","-","*","/","%","ERROR","VALUE"};



class AST{
    public:
        AST();
        AST(double val);
        AST(AST* l, Operation op, AST* r);
        void print();
        double eval();

    private:
        double value;
        Operation op;
        AST* left;
        AST* right;
};

#endif