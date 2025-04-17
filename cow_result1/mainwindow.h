#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QVector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewGameClicked();
    void onCheckClicked();
    void onRecordsClicked();

private:
    QPushButton *newGameButton;
    QPushButton *recordsButton;
    QLineEdit *inputField;
    QPushButton *checkButton;
    QTableWidget *resultTable;

    QString secretNumber;
    int attempts;

    QVector<QPair<int, QString>> leaderboard;

    void saveLeaderboard();
    void loadLeaderboard();
    bool isRecord(int attempts);
};

#endif // MAINWINDOW_H
