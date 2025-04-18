#include "mainwindow.h"
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  displayLineEdit = new QLineEdit("0", this);
  displayLineEdit->setReadOnly(true);
  displayLineEdit->setAlignment(Qt::AlignRight);
  displayLineEdit->setMaxLength(15);

  zeroButton = new QPushButton("0", this);
  oneButton = new QPushButton("1", this);
  twoButton = new QPushButton("2", this);
  threeButton = new QPushButton("3", this);
  fourButton = new QPushButton("4", this);
  fiveButton = new QPushButton("5", this);
  sixButton = new QPushButton("6", this);
  sevenButton = new QPushButton("7", this);
  eightButton = new QPushButton("8", this);
  nineButton = new QPushButton("9", this);

  plusButton = new QPushButton("+", this);
  minusButton = new QPushButton("-", this);
  multiplyButton = new QPushButton("*", this);
  divideButton = new QPushButton("/", this);
  equalsButton = new QPushButton("=", this);

  clearButton = new QPushButton("AC", this);
  plusMinusButton = new QPushButton("+/-", this);
  percentageButton = new QPushButton("%", this);
  decimalButton = new QPushButton(".", this);

  QGridLayout *buttonsLayout = new QGridLayout;
  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addWidget(displayLineEdit);

  buttonsLayout->addWidget(clearButton, 0, 0);
  buttonsLayout->addWidget(plusMinusButton, 0, 1);
  buttonsLayout->addWidget(percentageButton, 0, 2);
  buttonsLayout->addWidget(divideButton, 0, 3);

  buttonsLayout->addWidget(sevenButton, 1, 0);
  buttonsLayout->addWidget(eightButton, 1, 1);
  buttonsLayout->addWidget(nineButton, 1, 2);
  buttonsLayout->addWidget(multiplyButton, 1, 3);

  buttonsLayout->addWidget(fourButton, 2, 0);
  buttonsLayout->addWidget(fiveButton, 2, 1);
  buttonsLayout->addWidget(sixButton, 2, 2);
  buttonsLayout->addWidget(minusButton, 2, 3);

  buttonsLayout->addWidget(oneButton, 3, 0);
  buttonsLayout->addWidget(twoButton, 3, 1);
  buttonsLayout->addWidget(threeButton, 3, 2);
  buttonsLayout->addWidget(plusButton, 3, 3);

  buttonsLayout->addWidget(zeroButton, 4, 0, 1, 2);
  buttonsLayout->addWidget(decimalButton, 4, 2);
  buttonsLayout->addWidget(equalsButton, 4, 3);

  mainLayout->addLayout(buttonsLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  connect(zeroButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(oneButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(twoButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(threeButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(fourButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(fiveButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(sixButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(sevenButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(eightButton, &QPushButton::clicked, this, &MainWindow::digitClicked);
  connect(nineButton, &QPushButton::clicked, this, &MainWindow::digitClicked);

  connect(plusButton, &QPushButton::clicked, this,
          &MainWindow::operatorClicked);
  connect(minusButton, &QPushButton::clicked, this,
          &MainWindow::operatorClicked);
  connect(multiplyButton, &QPushButton::clicked, this,
          &MainWindow::operatorClicked);
  connect(divideButton, &QPushButton::clicked, this,
          &MainWindow::operatorClicked);

  connect(equalsButton, &QPushButton::clicked, this,
          &MainWindow::equalsClicked);
  connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearClicked);
  connect(plusMinusButton, &QPushButton::clicked, this,
          &MainWindow::plusMinusClicked);
  connect(percentageButton, &QPushButton::clicked, this,
          &MainWindow::percentageClicked);
  connect(decimalButton, &QPushButton::clicked, this,
          &MainWindow::decimalClicked);

  firstOperand = 0.0;
  currentOperator = "";
  waitingForSecondOperand = false;
}

MainWindow::~MainWindow() {}

void MainWindow::digitClicked() {

  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  if (!clickedButton)
    return;

  QString digit = clickedButton->text();
  QString currentDisplay = displayLineEdit->text();

  if (waitingForSecondOperand) {

    displayLineEdit->setText(digit);
    waitingForSecondOperand = false;
  } else {

    if (currentDisplay == "0" && digit != ".") {
      displayLineEdit->setText(digit);
    } else {
      displayLineEdit->setText(currentDisplay + digit);
    }
  }
}

void MainWindow::operatorClicked() {

  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  if (!clickedButton)
    return;

  if (waitingForSecondOperand && !currentOperator.isEmpty()) {
    equalsClicked();
  }

  firstOperand = displayLineEdit->text().toDouble();

  currentOperator = clickedButton->text();

  waitingForSecondOperand = true;
}

void MainWindow::equalsClicked() {

  double secondOperand = displayLineEdit->text().toDouble();
  double result = 0.0;
  bool calculationError = false;

  if (currentOperator == "+") {
    result = firstOperand + secondOperand;
  } else if (currentOperator == "-") {
    result = firstOperand - secondOperand;
  } else if (currentOperator == "*") {
    result = firstOperand * secondOperand;
  } else if (currentOperator == "/") {
    if (secondOperand == 0.0) {

      displayLineEdit->setText("Error: Div by 0");
      calculationError = true;
    } else {
      result = firstOperand / secondOperand;
    }
  } else {

    result = secondOperand;
  }

  firstOperand = result;
  currentOperator = "";
  waitingForSecondOperand = false;
}

void MainWindow::clearClicked() {

  displayLineEdit->setText("0");
  firstOperand = 0.0;
  currentOperator = "";
  waitingForSecondOperand = false;
}

void MainWindow::plusMinusClicked() {

  QString currentDisplay = displayLineEdit->text();
  double currentValue = currentDisplay.toDouble();
  currentValue *= -1.0;
}

void MainWindow::percentageClicked() {

  QString currentDisplay = displayLineEdit->text();
  double currentValue = currentDisplay.toDouble();
  double result = currentValue / 100.0;
}

void MainWindow::decimalClicked() {

  QString currentDisplay = displayLineEdit->text();
  if (!currentDisplay.contains(".")) {

    if (waitingForSecondOperand) {
      displayLineEdit->setText("0.");
      waitingForSecondOperand = false;
    } else {
      displayLineEdit->setText(currentDisplay + ".");
    }
  }
}
