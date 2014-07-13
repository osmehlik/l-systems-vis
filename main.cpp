//
// File:      main.cpp
// Purpose:   The entry point of a program.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

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
