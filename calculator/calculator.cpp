#include "calculator.h"
#include <QtMath> // For qAbs
#include <QDebug> // For debugging output (optional)

Calculator::Calculator(QWidget *parent)
    : QWidget(parent),
      currentResult(0.0),
      pendingOperator(""),
      waitingForOperand(true)
{
    // Create the display (QLineEdit)
    display = new QLineEdit("0");
    display->setReadOnly(true); // Make the display read-only
    display->setAlignment(Qt::AlignRight); // Align text to the right
    display->setMaxLength(15); // Limit the number of digits
    display->setStyleSheet("font-size: 20pt; padding: 5px;"); // Style the display

    // Create the main layout (Vertical Box Layout)
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display); // Add the display to the top

    // Create a grid layout for the buttons
    QGridLayout *buttonLayout = new QGridLayout;
    buttonLayout->setHorizontalSpacing(5); // Set horizontal spacing between buttons
    buttonLayout->setVerticalSpacing(5);   // Set vertical spacing between buttons

    // Define button layout
    // Row 0
    buttonLayout->addWidget(createButton("AC", SLOT(clearClicked())), 0, 0);
    buttonLayout->addWidget(createButton("+/-", SLOT(signClicked())), 0, 1);
    buttonLayout->addWidget(createButton("%", SLOT(percentClicked())), 0, 2);
    buttonLayout->addWidget(createButton("/", SLOT(operatorClicked())), 0, 3);

    // Row 1
    buttonLayout->addWidget(createButton("7", SLOT(digitClicked())), 1, 0);
    buttonLayout->addWidget(createButton("8", SLOT(digitClicked())), 1, 1);
    buttonLayout->addWidget(createButton("9", SLOT(digitClicked())), 1, 2);
    buttonLayout->addWidget(createButton("*", SLOT(operatorClicked())), 1, 3); // Adjusted based on image

    // Row 2
    buttonLayout->addWidget(createButton("4", SLOT(digitClicked())), 2, 0);
    buttonLayout->addWidget(createButton("5", SLOT(digitClicked())), 2, 1);
    buttonLayout->addWidget(createButton("6", SLOT(digitClicked())), 2, 2);
    buttonLayout->addWidget(createButton("-", SLOT(operatorClicked())), 2, 3);

    // Row 3
    buttonLayout->addWidget(createButton("1", SLOT(digitClicked())), 3, 0);
    buttonLayout->addWidget(createButton("2", SLOT(digitClicked())), 3, 1);
    buttonLayout->addWidget(createButton("3", SLOT(digitClicked())), 3, 2);
    buttonLayout->addWidget(createButton("+", SLOT(operatorClicked())), 3, 3);

    // Row 4
    buttonLayout->addWidget(createButton("0", SLOT(digitClicked())), 4, 0, 1, 2); // 0 button spans 2 columns
    buttonLayout->addWidget(createButton(".", SLOT(decimalClicked())), 4, 2);
    buttonLayout->addWidget(createButton("=", SLOT(equalsClicked())), 4, 3);

    mainLayout->addLayout(buttonLayout); // Add the button grid to the main layout

    setLayout(mainLayout); // Set the layout for the Calculator widget

    // Set fixed size for the window (optional, but helps match the design)
    // You can adjust these values based on how big you want the calculator
    setFixedSize(350, 400); // Example size
}

Calculator::~Calculator()
{
    // Layouts and their contained widgets are automatically deleted when the parent is deleted.
    // No need to manually delete display or buttons.
}

// Helper function to create a button and connect its clicked signal to a slot
QPushButton *Calculator::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->setFixedSize(50, 50); // Set a fixed size for the buttons
    button->setStyleSheet("font-size: 14pt;"); // Style the buttons
    connect(button, SIGNAL(clicked()), this, member); // Connect the clicked signal to the specified slot
    return button;
}

// Slot for digit buttons (0-9)
void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender()); // Get the button that was clicked
    if (!clickedButton) // Check if the sender is a QPushButton
        return;

    QString digitValue = clickedButton->text(); // Get the text of the button (the digit)

    if (display->text() == "0" && digitValue != ".") {
        // If the display is "0" and the clicked button is not ".", replace "0" with the digit
        display->setText(digitValue);
    } else if (waitingForOperand) {
        // If waiting for the second operand, clear the display and set the digit
        display->setText(digitValue);
        waitingForOperand = false;
    } else {
        // Otherwise, append the digit to the display
        display->setText(display->text() + digitValue);
    }
}

// Slot for operator buttons (+, -, *, /)
void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton)
        return;

    QString clickedOperator = clickedButton->text(); // Get the operator text

    if (currentResult == 0.0 && pendingOperator.isEmpty()) {
        // If this is the first operation, store the current display value as the initial result
        currentResult = display->text().toDouble();
    } else if (!waitingForOperand) {
        // If not waiting for an operand, perform the pending operation
        equalsClicked(); // Calculate the result of the previous operation
        currentResult = display->text().toDouble(); // The result is now the new currentResult
    }

    pendingOperator = clickedOperator; // Store the clicked operator
    waitingForOperand = true; // Now waiting for the next operand
}

// Slot for the equals button (=)
void Calculator::equalsClicked()
{
    double operand = display->text().toDouble(); // Get the current number in the display
    double result = 0.0;

    if (pendingOperator.isEmpty()) {
        // If no pending operator, do nothing or maybe just update display
        return;
    }

    // Perform the calculation based on the pending operator
    if (pendingOperator == "+") {
        result = currentResult + operand;
    } else if (pendingOperator == "-") {
        result = currentResult - operand;
    } else if (pendingOperator == "*") {
        result = currentResult * operand;
    } else if (pendingOperator == "/") {
        if (operand == 0.0) {
            // Handle division by zero error
            display->setText("Error: Div by Zero");
            currentResult = 0.0;
            pendingOperator = "";
            waitingForOperand = true;
            return;
        }
        result = currentResult / operand;
    }

    // Display the result
    // Use QString::number to control precision if needed, or simply set Double
    display->setText(QString::number(result));

    currentResult = result; // Update currentResult with the new result
    pendingOperator = ""; // Clear the pending operator
    waitingForOperand = true; // Ready for a new calculation or continued operations
}

// Slot for the AC (All Clear) button
void Calculator::clearClicked()
{
    display->setText("0"); // Reset display to 0
    currentResult = 0.0; // Reset current result
    pendingOperator = ""; // Clear pending operator
    waitingForOperand = true; // Reset waiting flag
}

// Slot for the +/- button
void Calculator::signClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (qAbs(value) > 0.000000001) { // Check if the value is not close to zero
        value *= -1; // Flip the sign
        display->setText(QString::number(value)); // Update display
    }
    // If value is 0, do nothing
}

// Slot for the % button
void Calculator::percentClicked()
{
    double value = display->text().toDouble();
    value *= 0.01; // Calculate percentage
    display->setText(QString::number(value)); // Update display
}

// Slot for the decimal point button (.)
void Calculator::decimalClicked()
{
    if (waitingForOperand) {
        // If waiting for a new operand, start with "0."
        display->setText("0.");
        waitingForOperand = false;
    } else if (!display->text().contains('.')) {
        // If the display doesn't already contain a decimal point, append one
        display->setText(display->text() + ".");
    }
    // If it already has a decimal, do nothing
}
