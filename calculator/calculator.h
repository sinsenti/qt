#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLineEdit>

class Calculator : public QMainWindow {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    double storedValue;
    QString operation;
    bool newNumber;

    void reset();
    void performOperation();
};

#endif // CALCULATOR_H
