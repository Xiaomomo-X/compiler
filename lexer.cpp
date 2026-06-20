#include "lexer.h"
#include <cctype>
using namespace std;


vector<Token> Tokens;
vector<string> errors;


void addToken(TokenType type,const string &value)
{
    Tokens.push_back({type,value});
}

void addError(const string &str)
{
    errors.push_back(str);
}

// 词法分析
void lexer(const string &str)
{
    Tokens.clear();
    errors.clear();
    int i=0;
    int n=str.size();
    while(i<n){
        // 跳过空白字符
        if(isspace(str[i])){
            i++;
            continue;
        }
        // 单行注释 //
        if(str[i]=='/' && i+1<n && str[i+1]=='/'){
            i+=2;
            while(i<n && str[i]!='\n'){
                i++;
            }
            continue;
        }
        // 多行注释 /* */
        if(str[i]=='/' && i+1<n && str[i+1]=='*'){
            i+=2;
            bool flag=false;
            while(i+1<n){
                if(str[i]=='*' && str[i+1]=='/'){
                    flag=true;
                    i+=2;
                    break;
                }
                i++;
            }
            if(!flag){
                addError("注释未闭合");
            }
            continue;
        }
        // 标识符或关键字
        if(isalpha(str[i]) || str[i]=='_'){
            string word;
            while(i<n &&(isalnum(str[i]) || str[i]=='_')){
                word.push_back(str[i]);
                i++;
            }
            if(keywordMap.count(word)){
                addToken(keyword,word);
            }
            else{
                addToken(id,word);
            }
            continue;
        }
        // 数字
        if(isdigit(str[i])){
            string number;
            while(i<n && isdigit(str[i])){
                number.push_back(str[i]);
                i++;
            }
            // 非法数字
            if(i<n&&(isalpha(str[i]) || str[i]=='_')){
                while(i<n&&(isalnum(str[i]) ||str[i]=='_')){
                    number.push_back(str[i]);
                    i++;
                }
                addError("非法标识符: "+number);
            }
            else{
                addToken(num,number);
            }
            continue;
        }
        // 双字符运算符
        if(i+1<n){
            string temp;
            temp.push_back(str[i]);
            temp.push_back(str[i+1]);
            if(opMap.count(temp)){
                addToken(op,temp);
                i+=2;
                continue;
            }
        }
        // 单字符
        string temp;
        temp.push_back(str[i]);
        // 运算符
        if(opMap.count(temp)){
            addToken(op,temp);
            i++;
            continue;
        }
        // 分隔符
        if(delimiterMap.count(temp)){
            addToken(delimiter,temp);
            i++;
            continue;
        }
        // 非法字符
        addError("非法字符: "+temp);
        i++;
    }
}