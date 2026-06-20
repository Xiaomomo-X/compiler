#include "parse.h"
#include <algorithm>
using namespace std;

int i=0;
string parseInfo;
string parseError;
vector<string> parseStack;
vector<production> grammar={
    {"E'",{"E"}},
    {"E",{"T","G"}},
    {"G",{"+","T","G"}},
    {"G",{}},
    {"T",{"F","S"}},
    {"S",{"*","F","S"}},
    {"S",{}},
    {"F",{"(","E",")"}},
    {"F",{"id"}}
};

map<string,int> ActionIndex={
    {"+",0},
    {"*",1},
    {"(",2},
    {")",3},
    {"id",4},
    {"#",5}
};

map<string,int> GotoIndex={
    {"E",0},
    {"G",1},
    {"T",2},
    {"S",3},
    {"F",4}
};

int ActionSize=ActionIndex.size();
int GotoSize=GotoIndex.size();
int rowLen=16;
vector<vector<string>> Action(rowLen,vector<string>(ActionSize,""));

vector<vector<string>>Goto(rowLen,vector<string>(GotoSize,""));

void saveAction(){
    for(auto &row:Action){
        fill(row.begin(),row.end(),"");
    }

    Action[0][ActionIndex["+"]]="S3";
    Action[0][ActionIndex["*"]]="S5";
    Action[0][ActionIndex["("]]="S6";
    Action[0][ActionIndex["id"]]="S7";

    Action[1][ActionIndex["#"]]="acc";

    Action[2][ActionIndex["+"]]="S3";
    Action[2][ActionIndex[")"]]="r3";
    Action[2][ActionIndex["#"]]="r3";

    Action[3][ActionIndex["("]]="S6";
    Action[3][ActionIndex["id"]]="S7";

    Action[4][ActionIndex["+"]]="r6";
    Action[4][ActionIndex["*"]]="S5";
    Action[4][ActionIndex[")"]]="r6";
    Action[4][ActionIndex["#"]]="r6";

    Action[5][ActionIndex["("]]="S6";
    Action[5][ActionIndex["id"]]="S7";

    Action[6][ActionIndex["("]]="S6";
    Action[6][ActionIndex["id"]]="S7";

    Action[7][ActionIndex["+"]]="r8";
    Action[7][ActionIndex["*"]]="r8";
    Action[7][ActionIndex[")"]]="r8";
    Action[7][ActionIndex["#"]]="r8";

    Action[8][ActionIndex[")"]]="r1";
    Action[8][ActionIndex["#"]]="r1";

    Action[9][ActionIndex["+"]]="S3";
    Action[9][ActionIndex[")"]]="r3";
    Action[9][ActionIndex["#"]]="r3";

    Action[10][ActionIndex["+"]]="r4";
    Action[10][ActionIndex[")"]]="r4";
    Action[10][ActionIndex["#"]]="r4";

    Action[11][ActionIndex["+"]]="r6";
    Action[11][ActionIndex["*"]]="S5";
    Action[11][ActionIndex[")"]]="r6";
    Action[11][ActionIndex["#"]]="r6";

    Action[12][ActionIndex[")"]]="S15";

    Action[13][ActionIndex[")"]]="r2";
    Action[13][ActionIndex["#"]]="r2";
    
    Action[14][ActionIndex["+"]]="r5";
    Action[14][ActionIndex[")"]]="r5";
    Action[14][ActionIndex["#"]]="r5";

    Action[15][ActionIndex["+"]]="r7";
    Action[15][ActionIndex["*"]]="r7";
    Action[15][ActionIndex[")"]]="r7";
    Action[15][ActionIndex["#"]]="r7";
}

void saveGoto(){
    for(auto &row:Goto){
        fill(row.begin(),row.end(),"");
    }

    Goto[0][GotoIndex["E"]]="1";
    Goto[0][GotoIndex["T"]]="2";
    Goto[0][GotoIndex["F"]]="4";

    Goto[2][GotoIndex["G"]]="8";

    Goto[3][GotoIndex["T"]]="9";
    Goto[3][GotoIndex["F"]]="4";

    Goto[4][GotoIndex["S"]]="10";

    Goto[5][GotoIndex["F"]]="11";

    Goto[6][GotoIndex["E"]]="12";
    Goto[6][GotoIndex["T"]]="2";
    Goto[6][GotoIndex["F"]]="4";

    Goto[9][GotoIndex["G"]]="13";

    Goto[11][GotoIndex["S"]]="14";
}

void printStack(){
    string s;
    for(auto &x:parseStack){
        s+=x+".";
    }
    while(s.length()<30){
        s+=" ";
    }
    parseInfo+=s;
}

void printStr(){
    string s;
    for(int j=i;j<Tokens.size();j++){
        s+=Tokens[j].value;
    }
    s+="#";
    while(s.length()<20){
        s+=" ";
    }
    parseInfo+=s;
}

void printAction(int m,int n){
    string token;
    if(i>=Tokens.size()){
        token="#";
    }
    else{
        token=Tokens[i].value;
    }
    parseInfo+="action["+to_string(m)+","+token+"]="+Action[m][n]+"\n";
}
void printGoto(int m,int x){
    parseInfo+="goto["+to_string(m)+","+parseStack.back()+"]="+Goto[m][x]+"\n";
}

string Type(){
    if(i>=Tokens.size()){
        return "#";
    }
    if(Tokens[i].type==id|| Tokens[i].type==num){
        return "id";
    }
    if(Tokens[i].type==keyword){
        parseError="语法错误：表达式中不能出现关键字 "+Tokens[i].value;
        return "#";
    }
    return Tokens[i].value;
}

bool parse(){

    parseInfo.clear();
    parseError.clear();
    parseStack.clear();

    parseInfo +="状态栈                        ""剩余输入串              ""动作\n";
    parseInfo +="-------------------------------------------------------------\n";

    i=0;
    saveAction();
    saveGoto();
    parseStack.push_back("0");
    parseStack.push_back("#");

    printStack();
    printStr();

    string first=Type();

    if(!parseError.empty()){
        parseInfo+=parseError+"\n";
        return false;
    }

    int m=0;
    int n=ActionIndex[first];
    printAction(m,n);

    while(true){
        string str=Action[m][n];
        if(str.empty()){
            parseInfo+=
            "语法错误\n";
            return false;
        }

        if(str[0]=='S'){
            string num;
            for(int j=1;j<str.size();j++){
                num+=str[j];
            }
            parseStack.insert(parseStack.begin(),num);
            parseStack.push_back(Type());
            i++;
            m=stoi(parseStack.front());
            n=ActionIndex[Type()];
            printStack();
            printStr();
            printAction(m,n);
        }

        else if(str[0]=='r'){
            string num;
            for(int j=1;j<str.size();j++){
                num+=str[j];
            }
            int production_index=stoi(num);
            production p=grammar[production_index];
            int len=p.right.size();
            for(int j=0;j<len;j++){
                parseStack.pop_back();
            }
            for(int j=0;j<len;j++){
                parseStack.erase(parseStack.begin());
            }
            parseStack.push_back(p.left);
            m=stoi(parseStack.front());
            int x=GotoIndex[p.left];

            printStack();
            printStr();
            printGoto(m,x);

            parseStack.insert(parseStack.begin(),Goto[m][x]);
            m=stoi(parseStack.front());
            n=ActionIndex[Type()];

            printStack();
            printStr();
            printAction(m,n);
        }
        else if(str=="acc"){
            parseInfo+="分析成功\n";
            return true;
        }
        else{
            parseInfo+="语法错误\n";
            return false;
        }
    }
}