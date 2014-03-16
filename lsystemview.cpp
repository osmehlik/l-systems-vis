
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
    if (lsystem == NULL) {
        return;
    }


    int w(size().width());
    int h(size().height());

    QRect widgetArea(0, 0, w, h);

    painter.fillRect(widgetArea, lsystem->getBackgroundColor());

    int posX = static_cast<int>(lsystem->getStartX() * w);
    int posY = static_cast<int>(lsystem->getStartY() * h);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setPen(lsystem->getForegroundColor());

    painter.translate(posX, posY);
    painter.rotate(lsystem->getStartRot());

    std::string lsystemstr = lsystem->evolve(lsystem->getIterations());

    std::stack<QMatrix> matrices;







    for (unsigned i(0); i < lsystemstr.length(); ++i) {

        char processedCharacter = lsystemstr[i];
        int processedIndex = -1;

        // find symbol
        for (int i(0); i < lsystem->getNumInterpretations(); ++i) {
            if (lsystem->getInterpretationSymbol(i) == processedCharacter) {
                processedIndex = i;
            }
        }


        // skip unknown symbols, they mean do nothing
        if (processedIndex == -1) continue;

        const CharInterpretation &interpretation(lsystem->getInterpretation(processedIndex));

        switch (interpretation.action) {
            case MOVE_FORWARD:
                painter.translate(lsystem->getStepLength(), 0);
            break;
            case DRAW_FORWARD:
                painter.drawLine(0, 0, lsystem->getStepLength(), 0);
                painter.translate(lsystem->getStepLength(), 0);
            break;
            case ROTATE:
                painter.rotate(interpretation.param);
            break;
            case PUSH_MATRIX:
                matrices.push(painter.matrix());
            break;
            case POP_MATRIX:
                if (matrices.size() > 0) {
                    painter.setMatrix(matrices.top());
                    matrices.pop();
                }
            break;
        }
    }
}



void LSystemView::setLSystem(LSystem *lsystem)
{
    this->lsystem = lsystem;
}
