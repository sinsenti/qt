#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Create the application instance
    Calculator w;               // Create an instance of our Calculator window
    w.setWindowTitle("Simple Calculator"); // Set the window title
    w.show();                   // Show the window

    return a.exec();            // Start the application event loop
}
