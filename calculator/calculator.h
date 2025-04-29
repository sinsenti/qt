#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

class Calculator : public QWidget
{
    Q_OBJECT // Macro needed for Qt's meta-object system (signals and slots)

public:
    Calculator(QWidget *parent = nullptr); // Constructor
    ~Calculator(); // Destructor

private slots:
    // Slots to handle button clicks
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();
    void signClicked();
    void percentClicked();
    void decimalClicked();

private:
    QLineEdit *display; // Display area
    QPushButton *createButton(const QString &text, const char *member); // Helper to create buttons

    double currentResult; // Stores the result of previous operations
    QString pendingOperator; // Stores the operator waiting to be applied
    bool waitingForOperand; // Flag to indicate if we are waiting for the second operand
};

#endif // CALCULATOR_H
