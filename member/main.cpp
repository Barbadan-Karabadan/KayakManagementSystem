#include "mainwindow.h"

#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection("../db/viena.db"))
        return EXIT_FAILURE;
    MainWindow w;
    w.show();
    return a.exec();
}
