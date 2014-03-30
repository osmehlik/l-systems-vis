#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("L-Systems Vis");
    MainWindow w;
    w.show();

    return a.exec();
}
