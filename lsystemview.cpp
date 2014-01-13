
#include "lsystem.h"
#include "lsystemview.h"
#include <QtGui>
#include <iostream>
#include <QColorDialog>
#include <stack>

LSystemView::LSystemView(QWidget *parent) :
    QWidget(parent)
{
}

void LSystemView::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);
    drawWidget(qp);
}

void LSystemView::drawWidget(QPainter &painter)
{
    int w(size().width());
    int h(size().height());

    QRect widgetArea(0, 0, w, h);

    painter.fillRect(widgetArea, lsystem.backgroundColor);

    int posX = static_cast<int>(lsystem.startX * w);
    int posY = static_cast<int>(lsystem.startY * h);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setPen(lsystem.foregroundColor);

    painter.translate(posX, posY);
    painter.rotate(lsystem.startRot);

    std::string lsystemstr = lsystem.evolve(lsystem.iterations);

    std::stack<QMatrix> matrices;

    for (unsigned i(0); i < lsystemstr.length(); ++i) {

        char processedCharacter = lsystemstr[i];

        // skip unknown symbols, they mean do nothing
        if (!lsystem.interpretation.count(processedCharacter)) continue;

        CharInterpretation interpretation = lsystem.interpretation[processedCharacter];

        switch (interpretation.action) {
            case MOVE_FORWARD:
                painter.translate(lsystem.stepLength, 0);
            break;
            case DRAW_FORWARD:
                painter.drawLine(0, 0, lsystem.stepLength, 0);
                painter.translate(lsystem.stepLength, 0);
            break;
            case ROTATE:
                painter.rotate(interpretation.param);
            break;
            case PUSH_MATRIX:
                matrices.push(painter.matrix());
            break;
            case POP_MATRIX:
                painter.setMatrix(matrices.top());
                matrices.pop();
            break;
        }
    }
}

void LSystemView::valueStartXChanged(double newValue)
{
    lsystem.startX = newValue;
    update();
}

void LSystemView::valueStartYChanged(double newValue)
{
    lsystem.startY = newValue;
    update();
}

void LSystemView::valueStartRotChanged(int newValue)
{
    lsystem.startRot = newValue;
    update();
}

void LSystemView::valueIterationsChanged(int newValue)
{
    lsystem.iterations = newValue;
    update();
}

void LSystemView::valueStepLengthChanged(int newValue)
{
    lsystem.stepLength = newValue;
    update();
}

void LSystemView::setBackgroundColor(QColor color)
{
    if (color.isValid()) {
        lsystem.backgroundColor = color;
    }
    update();
}

void LSystemView::setForegroundColor(QColor color)
{
    if (color.isValid()) {
        lsystem.foregroundColor = color;
    }
    update();
}
