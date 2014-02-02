#include "interpretationseditorwidget.h"
#include "interpretationeditorwidget.h"

InterpretationsEditorWidget::InterpretationsEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);


    addInterpretation('F', DRAW_FORWARD, 20);

    setLayout(vbox);
}


void InterpretationsEditorWidget::addInterpretation(char c, CharInterpretationAction action, int param)
{
    InterpretationEditorWidget *interpretation = new InterpretationEditorWidget(this);

    vbox->addWidget(interpretation);
}
