#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow  {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        void runlexer();
        void runparse();
        void runsemantic();
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
};

#endif