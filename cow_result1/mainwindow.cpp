#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Быки и коровы");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topLayout = new QHBoxLayout();
    newGameButton = new QPushButton("Новая игра", this);
    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::onNewGameClicked);
    topLayout->addWidget(newGameButton);

    QLabel *statusLabel = new QLabel("Игра не начата", this);
    topLayout->addWidget(statusLabel);

    recordsButton = new QPushButton("Рекорды", this);
    connect(recordsButton, &QPushButton::clicked, this, &MainWindow::onRecordsClicked);
    topLayout->addWidget(recordsButton);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите число");
    inputLayout->addWidget(inputField);

    checkButton = new QPushButton("Проверить", this);
    checkButton->setEnabled(false);
    connect(checkButton, &QPushButton::clicked, this, &MainWindow::onCheckClicked);
    inputLayout->addWidget(checkButton);

    topLayout->addLayout(inputLayout);

    resultTable = new QTableWidget(this);
    resultTable->setColumnCount(3);
    resultTable->setHorizontalHeaderLabels(QStringList() << "Попытка" << "Ваше число" << "Результат");
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultTable->verticalHeader()->hide();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(resultTable);

    secretNumber.clear();
    attempts = 0;

    loadLeaderboard();
}

MainWindow::~MainWindow() {
    saveLeaderboard();
}

void MainWindow::onNewGameClicked() {
    secretNumber.clear();
    while (secretNumber.size() < 4) {
        int digit = QRandomGenerator::global()->bounded(10);
        if (!secretNumber.contains(QChar('0' + digit))) {
            secretNumber += QChar('0' + digit);
        }
    }

    qDebug() << "Secret number:" << secretNumber;

    attempts = 0;
    resultTable->clearContents();
    resultTable->setRowCount(0);

    inputField->setEnabled(true);
    checkButton->setEnabled(true);
    inputField->clear();
}

void MainWindow::onCheckClicked() {
    QString guess = inputField->text();

    if (guess.length() != 4 || !guess.toInt()) {
        QMessageBox::warning(this, "Ошибка", "Введите 4-значное число!");
        return;
    }

    attempts++;

    int bulls = 0, cows = 0;
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secretNumber[i]) {
            bulls++;
        } else if (secretNumber.contains(guess[i])) {
            cows++;
        }
    }

    resultTable->insertRow(resultTable->rowCount());
    resultTable->setItem(attempts - 1, 0, new QTableWidgetItem(QString::number(attempts)));
    resultTable->setItem(attempts - 1, 1, new QTableWidgetItem(guess));
    resultTable->setItem(attempts - 1, 2, new QTableWidgetItem(QString("%1 быков, %2 коров").arg(bulls).arg(cows)));

    if (bulls == 4) {
        QMessageBox::information(this, "Победа!", "Вы угадали число за " + QString::number(attempts) + " попыток!");

        if (isRecord(attempts)) {
            bool ok;
            QString name = QInputDialog::getText(this, "Новое достижение", "Введите ваше имя:", QLineEdit::Normal, "", &ok);
            if (ok && !name.isEmpty()) {
                leaderboard.append({attempts, name});
                saveLeaderboard();
            }
        }

        onNewGameClicked();
    }
}

void MainWindow::onRecordsClicked() {
    QString leaderboardText;
    for (const auto &record : leaderboard) {
        leaderboardText += QString("%1\t%2\n").arg(record.first).arg(record.second);
    }
    QMessageBox::information(this, "Рекорды", leaderboardText);
}

void MainWindow::saveLeaderboard() {
    QFile file("records.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto &record : leaderboard) {
            out << record.first << "\t" << record.second << "\n";
        }
        file.close();
    }
}

void MainWindow::loadLeaderboard() {
    QFile file("records.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("\t");
            if (parts.size() == 2) {
                leaderboard.append({parts[0].toInt(), parts[1]});
            }
        }
        file.close();
    }
}

bool MainWindow::isRecord(int attempts) {
    if (leaderboard.size() < 10) return true;
    return attempts < leaderboard.last().first;
}
