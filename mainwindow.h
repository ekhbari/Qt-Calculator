#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_clicked();
    void on_clear_clicked();
    void on_equal_clicked();

private:
    Ui::MainWindow *ui;
    QString currentInput;
    double operand1 = 0;
    QString operation;
    bool waitingForOperand2 = false;
};
#endif // MAINWINDOW_H