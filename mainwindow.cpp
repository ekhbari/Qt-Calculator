#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        if (button->text() == "C")
            connect(button, &QPushButton::clicked, this, &MainWindow::on_clear_clicked);
        else if (button->text() == "=")
            connect(button, &QPushButton::clicked, this, &MainWindow::on_equal_clicked);
        else
            connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_button_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString text = button->text();

    if (text == "+" || text == "-" || text == "*" || text == "/") {
        operand1 = currentInput.toDouble();
        operation = text;
        currentInput.clear();
        waitingForOperand2 = true;
    } else {
        currentInput += text;
        ui->lineEdit->setText(currentInput);
    }
}

void MainWindow::on_equal_clicked() {
    if (!waitingForOperand2) return;

    double operand2 = currentInput.toDouble();
    double result = 0;

    if (operation == "+") result = operand1 + operand2;
    else if (operation == "-") result = operand1 - operand2;
    else if (operation == "*") result = operand1 * operand2;
    else if (operation == "/") {
        if (operand2 == 0) {
            ui->lineEdit->setText("خطأ: قسمة على صفر");
            return;
        }
        result = operand1 / operand2;
    }

    ui->lineEdit->setText(QString::number(result));
    currentInput = QString::number(result);
    waitingForOperand2 = false;
}

void MainWindow::on_clear_clicked() {
    currentInput.clear();
    operand1 = 0;
    operation.clear();
    waitingForOperand2 = false;
    ui->lineEdit->clear();
}