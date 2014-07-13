#include "interpretationeditorlistwidget.h"
#include "interpretationeditorwidget.h"

InterpretationEditorListWidget::InterpretationEditorListWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);

    currentInterpretationIndex = 0;

    setLayout(vbox);
}


void InterpretationEditorListWidget::addInterpretation(char c, CharInterpretationAction action, int param)
{
    InterpretationEditorWidget *interpretation = new InterpretationEditorWidget(this);

    interpretation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    interpretation->setAction(action);
    interpretation->setSymbol(c);
    interpretation->setParam(param);

    connect(interpretation, SIGNAL(changed(int,CharInterpretation)), this, SIGNAL(interpretationWasChanged(int,CharInterpretation)));
    connect(interpretation, SIGNAL(removed(int)), this, SIGNAL(interpretationWasRemoved(int)));

    vbox->addWidget(interpretation);

    emit interpretationWasAdded();
}

void InterpretationEditorListWidget::load(LSystem *lSystem)
{
    this->lsystem = lSystem;
    currentInterpretationIndex = 0;

    int numInterpretations = lSystem->getNumInterpretations();

    removeContents();

    blockSignals(true);
    for (int i(0); i < numInterpretations; ++i) {
        const CharInterpretation ci = lSystem->getInterpretation(i);
        addInterpretation(ci.symbol,ci.action,ci.param);
    }
    blockSignals(false);
}

void InterpretationEditorListWidget::removeContents()
{
    QLayoutItem *child;
    while ((child = vbox->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }
}

