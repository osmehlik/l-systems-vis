
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
