#include "token.h"
//关键字 if int while do else return continue 
const map<string,TokenType> keywordMap{
    {"if",keyword},{"int",keyword},{"while",keyword},{"do",keyword},
    {"else",keyword},{"return",keyword},{"continue",keyword}
};
//操作数 + - * / > < <= >= != 
const map<string,TokenType> opMap{
    {"+",op},{"-",op},{"*",op},{"/",op},
    {">",op},{"<",op},{">=",op},{"<=",op},
    {"!=",op}
};

//分隔符 , ; () {}
const map<string,TokenType> delimiterMap{
    {",",delimiter},{";",delimiter},{"(",delimiter},
    {")",delimiter},{"{",delimiter},{"}",delimiter}
};