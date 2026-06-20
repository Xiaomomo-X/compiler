#include "semantic.h"
#include <stdexcept>
using namespace std;

vector<string> opStack;
vector<string> semanticStack;
vector<Quadruple> intermediateCode;
map<string,Token> symbolTable;
string semanticInfo;

int tempCounter=0;
int idx=0;
string newTemp(){
    string temp="t"+to_string(tempCounter);
    tempCounter++;
    return temp;
}

void expression(){
    multi_or_division();
    while(idx<Tokens.size()&&(Tokens[idx].value=="+"||Tokens[idx].value=="-")){
        string op=Tokens[idx].value;
        opStack.push_back(op);
        idx++;

        multi_or_division();

        string arg1=semanticStack.back();
        semanticStack.pop_back();
        string arg2=semanticStack.back();
        semanticStack.pop_back();
        string temp_op=opStack.back();
        opStack.pop_back();
        string temp=newTemp();

        if(symbolTable[arg1].type==num&&symbolTable[arg2].type==num){
            int num1=stoi(symbolTable[arg1].value);
            int num2=stoi(symbolTable[arg2].value);
            int result;

            if(temp_op=="+"){
                result=num2+num1;
            }
            else{
                result=num2-num1;
            }
            symbolTable[temp]={num,to_string(result)};
        }
        else{
            string value;
            if(symbolTable[arg2].value.empty()){
                value=arg2;
            }
            else{
                value=symbolTable[arg2].value;
            }

            value+=temp_op;
            if(symbolTable[arg1].value.empty()){
                value+=arg1;
            }
            else{
                value+=symbolTable[arg1].value;
            }
            symbolTable[temp]={id,value};
        }

        semanticStack.push_back(temp);
        intermediateCode.push_back({temp_op,arg2,arg1,temp});
    }
}

void multi_or_division(){
    factor();
    while(idx<Tokens.size()&&(Tokens[idx].value=="*"||Tokens[idx].value=="/")){
        string op=Tokens[idx].value;
        opStack.push_back(op);
        idx++;

        factor();

        string arg1=semanticStack.back();
        semanticStack.pop_back();
        string arg2=semanticStack.back();
        semanticStack.pop_back();
        string temp_op=opStack.back();
        opStack.pop_back();
        string temp=newTemp();

        if(symbolTable[arg1].type==num&&symbolTable[arg2].type==num){
            int num1=stoi(symbolTable[arg1].value);
            int num2=stoi(symbolTable[arg2].value);
            if(temp_op=="/"&&num1==0){
                throw runtime_error("除数不能为0");
            }
            int result;
            if(temp_op=="*"){
                result=num2*num1;
            }
            else{
                result=num2/num1;
            }

            symbolTable[temp]={num,to_string(result)};
        }
        else{
            string value;
            if(symbolTable[arg2].value.empty()){
                value=arg2;
            }
            else{
                value=symbolTable[arg2].value;
            }
            value+=temp_op;
            if(symbolTable[arg1].value.empty()){
                value+=arg1;
            }
            else{
                value+=symbolTable[arg1].value;
            }

            symbolTable[temp]={id,value};
        }

        semanticStack.push_back(temp);
        intermediateCode.push_back({
            temp_op,
            arg2,
            arg1,
            temp
        });
    }
}

void factor(){
    if(idx>=Tokens.size()){
        throw runtime_error("表达式不完整");
    }
    if(Tokens[idx].type==keyword){
        throw runtime_error("表达式中不能出现关键字 "+Tokens[idx].value);
    }

    Token token=Tokens[idx];
    if(token.value=="("){
        idx++;
        expression();
        if(idx<Tokens.size()&&Tokens[idx].value==")"){
            idx++;
            return;
        }
        throw runtime_error("缺少右括号 )");
    }

    if(token.type==id||token.type==num){
        idx++;
        string temp=newTemp();
        symbolTable[temp]=token;
        semanticStack.push_back(temp);
        intermediateCode.push_back({"=",token.value,"_",temp});
        return;
    }
    throw runtime_error("非法因子："+token.value);
}

void print(){
    semanticInfo.clear();
    semanticInfo+="=====四元式=====\n";
    for(auto &q:intermediateCode){
        semanticInfo+="{";
        semanticInfo+=q.op;
        semanticInfo+=",";
        semanticInfo+=q.arg1;
        semanticInfo+=",";
        semanticInfo+=q.arg2;
        semanticInfo+=",";
        semanticInfo+=q.result;
        semanticInfo+="}\n";
    }

    semanticInfo+="\n=====符号表=====\n";
    for(auto &item:symbolTable){
        semanticInfo+=item.first;
        semanticInfo+=" -> ";
        semanticInfo+=item.second.value;
        semanticInfo+="\n";
    }
}

bool semantic(){
    opStack.clear();
    semanticStack.clear();
    intermediateCode.clear();
    symbolTable.clear();
    semanticInfo.clear();

    tempCounter=0;
    idx=0;
    expression();
    if(idx!=Tokens.size()){
        throw runtime_error("表达式后存在多余字符");
    }
    print();
    return true;
}