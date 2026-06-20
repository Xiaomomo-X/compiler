#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "lexer.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Quadruple{
    string op;
    string arg1;
    string arg2;
    string result;
};

extern vector<string> opStack;
extern vector<string> semanticStack;
extern vector<Quadruple> intermediateCode;
extern map<string,Token> symbolTable;
extern string semanticInfo;

string newTemp();
void expression();
void multi_or_division();
void factor();
void print();
bool semantic();
#endif