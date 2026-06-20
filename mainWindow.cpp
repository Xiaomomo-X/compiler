#include"mainWindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include"lexer.h"
#include"parse.h"
#include"parse_RD.h"
#include"semantic.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lexerButton,&QPushButton::clicked,this,&MainWindow::runlexer);
    connect(ui->parseButton,&QPushButton::clicked,this,&MainWindow::runparse);
    connect(ui->semanticButton,&QPushButton::clicked,this,&MainWindow::runsemantic);
}
void MainWindow::runlexer(){
    // 获取输入框内容
    QString text = ui->inputText->toPlainText();
    string str = text.toStdString();

    lexer(str);

    ui->outputText->clear();
    for(const auto &token : Tokens){
        QString line;
        line = QString("(%1 , %2)")
                .arg(token.type)
                .arg(QString::fromStdString(token.value));
        ui->outputText->append(line);
    }
    // 输出错误信息
    if(!errors.empty()){
        ui->outputText->append("\n=====错误信息=====\n");
        for(const auto &error : errors){
            ui->outputText->append(
                QString::fromStdString(error)
            );
        }
    }
}
void MainWindow::runparse(){
    QString text =ui->inputText->toPlainText();
    string str =text.toStdString();
    ui->outputText->clear();

    lexer(str);

    // 词法错误
    if(!errors.empty()){
        ui->outputText->append("=====词法错误=====\n");
        for(const auto &error:errors){
            ui->outputText->append(QString::fromStdString(error));
        }
        return ;
    }
    bool ok=parse();

    ui->outputText->setPlainText(QString::fromStdString(parseInfo));
    if(ok){
        ui->outputText->append("\n=====语法分析成功=====");
    }
    else{
        ui->outputText->append("\n=====语法分析失败=====");
    }
}
void MainWindow::runsemantic(){
    QString text=ui->inputText->toPlainText();
    string str=text.toStdString();
    lexer(str);
    ui->outputText->clear();
    // 先检查词法错误
    if(!errors.empty()){
        ui->outputText->append("=====词法错误=====");
        for(auto &e:errors){
            ui->outputText->append(QString::fromStdString(e));
        }
        return;
    }

    try{
        parseRD();
        semantic();
        ui->outputText->append(QString::fromStdString(semanticInfo));
    }
    catch(exception &e){
        ui->outputText->append("=====错误信息=====");
        ui->outputText->append(QString::fromStdString(e.what()));
    }
}
MainWindow::~MainWindow(){
    delete ui;
}