#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Быки и коровы");

    // Top Layout
    QHBoxLayout *topLayout = new QHBoxLayout;
    QPushButton *newGameButton = new QPushButton("Новая игра");
    QLabel *gameStatusLabel = new QLabel("Игра не начата");
    QPushButton *recordsButton = new QPushButton("Рекорды");

    topLayout->addWidget(newGameButton);
    topLayout->addWidget(gameStatusLabel);
    topLayout->addWidget(recordsButton);

    // Middle Layout
    QHBoxLayout *middleLayout = new QHBoxLayout;
    QLabel *enterNumberLabel = new QLabel("введи число");
    QLineEdit *numberLineEdit = new QLineEdit();
    QPushButton *checkButton = new QPushButton("Проверить!");

    middleLayout->addWidget(enterNumberLabel);
    middleLayout->addWidget(numberLineEdit);
    middleLayout->addWidget(checkButton);

    // Bottom Layout (using GridLayout for the table-like structure)
    QGridLayout *bottomLayout = new QGridLayout;
    QLabel *guessLabel = new QLabel("1");
    QLabel *resultLabel = new QLabel("2");


    bottomLayout->addWidget(guessLabel, 0, 0);
    bottomLayout->addWidget(resultLabel, 0, 1);

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}
