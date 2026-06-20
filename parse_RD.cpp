#include "parse_RD.h"
#include <stdexcept>
using namespace std;

int rdIndex=0;
void E(){
    T();
    G();
}

void G(){
    if(rdIndex<Tokens.size()&&Tokens[rdIndex].value=="+"){
        rdIndex++;
        T();
        G();
    }
}

void T(){
    F();
    S();
}
void S(){
    if(rdIndex<Tokens.size()&&Tokens[rdIndex].value=="*"){
        rdIndex++;
        F();
        S();
    }
}

void F(){
    if(rdIndex>=Tokens.size()){
        throw runtime_error("表达式不完整");
    }

    // 关键字不能出现
    if(Tokens[rdIndex].type==keyword){
        throw runtime_error("表达式中不能出现关键字 "+Tokens[rdIndex].value);
    }

    if(Tokens[rdIndex].type==id||Tokens[rdIndex].type==num){
        rdIndex++;
        return;
    }

    if(Tokens[rdIndex].value=="("){
        rdIndex++;
        E();
        if(rdIndex<Tokens.size()&&Tokens[rdIndex].value==")"){
            rdIndex++;
            return;
        }
        throw runtime_error("缺少右括号 )");
    }
    throw runtime_error("因子错误："+Tokens[rdIndex].value);
}

bool parseRD(){
    rdIndex=0;
    E();
    if(rdIndex!=Tokens.size()){
        throw runtime_error("表达式后存在多余字符");
    }
    return true;
}