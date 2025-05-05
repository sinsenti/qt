#include "calculator.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), storedValue(0.0), newNumber(true) {
    setWindowTitle("Calculator");
    setFixedSize(300, 400);

    // Central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Display setup
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setText("0");
    display->setStyleSheet("QLineEdit { font-size: 24px; padding: 10px; }");
    mainLayout->addWidget(display);

    // Button grid setup
    QGridLayout *gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    // Button labels based on the described 5x4 grid
    const char* buttonLabels[5][4] = {
        {"AC", "+/-", "%", "/"},
        {"7", "8", "9", "*"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "+"},
        {"0", "0", ".", "="}
    };

    // Create and arrange buttons
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (row == 4 && col == 1) continue; // Skip extra "0" cell
            QPushButton *button = new QPushButton(buttonLabels[row][col], this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setStyleSheet("QPushButton { font-size: 18px; padding: 10px; }");
            if (row == 4 && col == 0) {
                gridLayout->addWidget(button, row, col, 1, 2); // "0" spans two columns
            } else {
                gridLayout->addWidget(button, row, col);
            }
            connect(button, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        }
    }
}

void Calculator::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString buttonText = button->text();

    if (buttonText >= "0" && buttonText <= "9") {
        if (newNumber) {
            display->setText(buttonText);
            newNumber = false;
        } else {
            display->setText(display->text() + buttonText);
        }
    }
    else if (buttonText == ".") {
        if (!display->text().contains(".")) {
            display->setText(display->text() + ".");
        }
    }
    else if (buttonText == "AC") {
        reset();
    }
    else if (buttonText == "+/-") {
        double value = display->text().toDouble();
        display->setText(QString::number(-value));
    }
    else if (buttonText == "%") {
        double value = display->text().toDouble();
        display->setText(QString::number(value / 100.0));
    }
    else if (buttonText == "=") {
        performOperation();
        newNumber = true;
    }
    else { // Arithmetic operators (+, -, *, /)
        performOperation();
        storedValue = display->text().toDouble();
        operation = buttonText;
        newNumber = true;
    }
}

void Calculator::performOperation() {
    if (operation.isEmpty()) return;

    double current = display->text().toDouble();
    double result = 0.0;
    if (operation == "+") result = storedValue + current;
    else if (operation == "-") result = storedValue - current;
    else if (operation == "*") result = storedValue * current;
    else if (operation == "/") {
        if (current == 0) {
            QMessageBox::warning(this, "Error", "Division by zero");
            reset();
            return;
        }
        result = storedValue / current;
    }
    display->setText(QString::number(result));
    operation.clear();
}

void Calculator::reset() {
    display->setText("0");
    storedValue = 0.0;
    operation.clear();
    newNumber = true;
}
