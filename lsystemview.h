#ifndef LSYSTEMVIEW_H
#define LSYSTEMVIEW_H

#include <QWidget>
#include "lsystem.h"

class LSystemView : public QWidget
{
    Q_OBJECT
public:
    explicit LSystemView(QWidget *parent = 0);

   LSystem lsystem;



public slots:
    void valueStartXChanged(double newValue);
    void valueStartYChanged(double newValue);
    void valueStartRotChanged(int newValue);
    void valueIterationsChanged(int newValue);
    void valueStepLengthChanged(int newValue);
    void setRandomColors();
    void setBackgroundColor();
    void setForegroundColor();

protected:
    void paintEvent(QPaintEvent *e);
    void drawWidget(QPainter &qp);

};

#endif // LSYSTEMVIEW_H
