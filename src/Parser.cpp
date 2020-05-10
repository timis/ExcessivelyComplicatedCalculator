#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(){
    str = "";
    index = 0;
}

Operation Parser::parse_operation(){
    cout << "parse_operation called" << endl;
    char c = str[index];
    index++;
    while(c == ' '){
        c = str[index];
        index++;
    }
    Operation returnVal = ERROR;
    switch(c){
        case('+'): returnVal = PLUS; break;
        case('-'): returnVal = MINUS; break;
        case('*'): returnVal = TIMES; break;
        case('/'): returnVal = DIVIDE; break;
        case('%'): returnVal = MOD; break;
        default: returnVal = ERROR; break;
    }
    while(c == ' '){
        c = str[index];
        index++;
    }
    return returnVal;
}

bool Parser::isNumeric(char c){
    cout << "isNumeric called on " << c << endl;
    return (c >= '0' && c <= '9');
}

AST* Parser::parse_expression(){
    cout << "parse_expression called; index=" << index << endl;
    if(index >= str.size()){
        cout << "ERROR - index greater than str size" << endl;
        return NULL;
    }
    char c = str[index];
    index++;
    while(c == ' '){
        if(index >= str.size()){
            cout << "ERROR - index greater than str size" << endl;
            return NULL;
        }
        c = str[index];
        index++;
    }

    if(isNumeric(c)){
        cout << c << " is in fact numeric"<< endl;
        string doubleString = "";
        doubleString.push_back(c);
        cout << "doubleString: " << doubleString << endl;
        if(index >= str.size()){
            cout << "ERROR - index greater than str size" << endl;
            return NULL;
        }
        c = str[index];
        bool periodFound = false;
        while(isNumeric(c) || c == '.'){
            cout << "Building doubleString: "<< doubleString << endl;
            if(c == '.'){
                if(periodFound){
                    //ERROR - represent somehow
                } else {
                    periodFound = true;
                }
            }
            index++;
            doubleString += c;
            if(index >= str.size()){
                cout << "ERROR - index greater than str size" << endl;
                return NULL;
            }
            c = str[index];
        }
        cout << "returning new AST node" << endl;
        string::size_type sz;
        return new AST(stod(doubleString,&sz));
    } else if (c == '('){
        AST* lhs = parse_expression();
        if(lhs == NULL){
            cout << "Could not find left hand side"<<endl;
            return NULL;
        }
        Operation oper = parse_operation();
        if(oper == ERROR){
            cout << "Could not find operation " << str.substr(0,index) << endl;
            return NULL;
        }
        AST* rhs = parse_expression();
        if(rhs == NULL){
            cout << "Could not find right hand side"<<endl;
            return NULL;
        }
        if(str[index] != ')'){
            cout << "Compound expression must end with ')'" << endl;
            return NULL;
        }
        index++;
        return new AST(lhs,oper,rhs);
    } else {
        cout << "Not supported yet" << endl;
        return NULL;
    }   
}

AST* Parser::parse(string inputStr){
    cout << "parse called" << endl;
    str = inputStr;
    index = 0;
    return parse_expression();
}