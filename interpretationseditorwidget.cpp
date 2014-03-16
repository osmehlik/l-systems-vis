#include "interpretationseditorwidget.h"
#include "interpretationeditorwidget.h"

InterpretationsEditorWidget::InterpretationsEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);


    //addInterpretation('F', DRAW_FORWARD, 20);

    setLayout(vbox);
}


void InterpretationsEditorWidget::addInterpretation(char c, CharInterpretationAction action, int param)
{
    InterpretationEditorWidget *interpretation = new InterpretationEditorWidget(this);

    interpretation->setAction(action);
    interpretation->setSymbol(c);
    interpretation->setParam(param);

    vbox->addWidget(interpretation);
}

void InterpretationsEditorWidget::loadInterpretations(LSystem *lSystem)
{
    int numInterpretations = lSystem->getNumInterpretations();

    removeContents();

    for (int i(0); i < numInterpretations; ++i) {
        const CharInterpretation ci = lSystem->getInterpretation(i);
        addInterpretation(ci.symbol,ci.action,ci.param);
    }
}

void InterpretationsEditorWidget::removeContents()
{
    QLayoutItem *child;
    while ((child = vbox->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }
}
