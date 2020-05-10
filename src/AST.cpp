#include "AST.h"
#include <iostream>

using namespace std;


AST::AST(){
    left = nullptr;
    right = nullptr;
    op = ERROR;
    value = 0.0;
}

AST::AST(double val){
    cout << "Building new node with value " << val << endl;
    left = nullptr;
    right = nullptr;
    op = VALUE;
    value = val;
}

AST::AST(AST* l, Operation oper, AST* r){
    left = l;
    op = oper;
    right = r;
    value = 0.0;
}

void AST::print(){
    if(left != nullptr){
        cout << "(";
        left->print();
    }
    if(op == VALUE){
        cout << " " << value << " ";
    } else {
        cout << " " << enumToOperator[op] << " ";
    }
    if(right != nullptr) {
        right->print();
        cout << ")";
    }
}

double AST::eval(){
    if(op == VALUE){
        return value;
    } else {
        double lhs = left->eval();
        double rhs = right->eval();
        double ret = 0.0;
        switch(op){
            case(PLUS): ret = lhs + rhs; break;
            case(MINUS): ret = lhs - rhs; break;
            case(TIMES): ret = lhs * rhs; break;
            case(DIVIDE): ret = lhs / rhs; break;
            case(MOD): ret = (int)lhs % (int)rhs; break;
            default: cout << "ERROR - OPERATION ERROR - CANNOT EVALUATE" << endl; break;
        }
        return ret;
    }
}