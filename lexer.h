#ifndef LEXER_H
#define LEXER_H

#include"token.h"
#include<vector>
#include<string>
using namespace std;

//存识别好的字符串和非法字符(声明)
extern vector<Token> Tokens;
extern vector<string> errors;

void addToken(TokenType type,const string &value);
void addError(const string &str);

void lexer(const string &str);

#endif