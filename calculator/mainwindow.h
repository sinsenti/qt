#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void digitClicked();
  void operatorClicked();
  void equalsClicked();
  void clearClicked();
  void plusMinusClicked();
  void percentageClicked();
  void decimalClicked();

private:
  QLineEdit *displayLineEdit;

  QPushButton *zeroButton;
  QPushButton *oneButton;
  QPushButton *twoButton;
  QPushButton *threeButton;
  QPushButton *fourButton;
  QPushButton *fiveButton;
  QPushButton *sixButton;
  QPushButton *sevenButton;
  QPushButton *eightButton;
  QPushButton *nineButton;

  QPushButton *plusButton;
  QPushButton *minusButton;
  QPushButton *multiplyButton;
  QPushButton *divideButton;
  QPushButton *equalsButton;

  QPushButton *clearButton;
  QPushButton *plusMinusButton;
  QPushButton *percentageButton;
  QPushButton *decimalButton;

  double firstOperand;
  QString currentOperator;
  bool waitingForSecondOperand;
};

#endif
