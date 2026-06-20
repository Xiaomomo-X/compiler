#ifndef TOKEN_H
#define TOKEN_H

#include<string>
#include<map>
#include<vector>
using namespace std;
enum TokenType{
    keyword=1,  //关键字 if int while do else return continue 
    id=2,       //标识符
    num=3,      //数字
    op=4,       //操作数 + - * / > < <= >= != 
    delimiter=5 //分隔符 , ; () {}
};
struct Token{
    TokenType type;
    string value;
};
extern const map<string,TokenType> keywordMap;
extern const map<string,TokenType> opMap;
extern const map<string,TokenType> delimiterMap;
#endif