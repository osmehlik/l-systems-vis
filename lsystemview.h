//
// File:      lsystemview.h
// Purpose:   A widget to display L-System.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#ifndef LSYSTEMVIEW_H
#define LSYSTEMVIEW_H

#include <QWidget>
#include "lsystem.h"

class LSystemView : public QWidget
{
    Q_OBJECT

public:
    explicit LSystemView(QWidget *parent = 0);
    void setLSystem(LSystem *lsystem);

protected:
    void paintEvent(QPaintEvent *e);
    void drawWidget(QPainter &qp);
    LSystem *lsystem;
};

#endif // LSYSTEMVIEW_H
