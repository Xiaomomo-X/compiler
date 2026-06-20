#ifndef PARSE_H
#define PARSE_H

#include "lexer.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

struct production{
    string left;
    vector<string> right;
};

extern vector<production> grammar;
extern vector<string> parseStack;
extern map<string,int> ActionIndex;
extern map<string,int> GotoIndex;
extern vector<vector<string>> Action;
extern vector<vector<string>> Goto;

// 保存整个分析过程
extern string parseInfo;
// 保存错误信
extern string parseError;

void saveAction();
void saveGoto();
bool parse();
string Type();
void printStack();
void printStr();
void printAction(int m,int n);
void printGoto(int m,int x);

#endif