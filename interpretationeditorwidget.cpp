#include "interpretationeditorwidget.h"
#include "lsystem.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QAction>
#include <sstream>

InterpretationEditorWidget::InterpretationEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    QLabel *symbolLabel = new QLabel("Symbol:", this);
    symbolLineEdit = new QLineEdit(this);

    symbolLineEdit->setMaxLength(1);

    QLabel *interpretationLabel = new QLabel("Interpretation:", this);
    actionComboBox = new QComboBox(this);

    QLabel *parameterLabel = new QLabel("Parameter:", this);
    paramLineEdit = new QLineEdit(this);
    paramLineEdit->setEnabled(false); // default value move forward currently requires no argument

    actionComboBox->addItem("Move Forward");
    actionComboBox->addItem("Draw Forward");
    actionComboBox->addItem("Rotate");
    actionComboBox->addItem("Push Matrix");
    actionComboBox->addItem("Pop Matrix");

    connect(actionComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInterpretationIndexChanged(int)));
    connect(symbolLineEdit, SIGNAL(editingFinished()),
            this, SLOT(onSymbolChanged()));
    connect(paramLineEdit, SIGNAL(editingFinished()),
            this, SLOT(onParamChanged()));

    hbox->addWidget(symbolLabel);
    hbox->addWidget(symbolLineEdit);
    hbox->addWidget(interpretationLabel);
    hbox->addWidget(actionComboBox);
    hbox->addWidget(parameterLabel);
    hbox->addWidget(paramLineEdit);

    setLayout(hbox);
}

void InterpretationEditorWidget::onInterpretationIndexChanged(int i)
{
    paramLineEdit->setEnabled(i == ROTATE);
    if (lsystem) {
        lsystem->setInterpretationAction(lsystemInterpretationIndex, static_cast<CharInterpretationAction>(i));
    }
}

void InterpretationEditorWidget::onSymbolChanged()
{
    if (lsystem) {
        char c = symbolLineEdit->text().toStdString().at(0);
        lsystem->setInterpretationLetter(lsystemInterpretationIndex, c);
    }
}

void InterpretationEditorWidget::onParamChanged()
{
    if (lsystem) {
        std::stringstream ss;
        ss.str(paramLineEdit->text().toStdString());
        int param;

        ss >> param;

        lsystem->setInterpretationParam(lsystemInterpretationIndex, param);
    }
}

void InterpretationEditorWidget::setLSystem(LSystem *lsystem, int lsystemInterpretationIndex)
{
    this->lsystem = lsystem;
    this->lsystemInterpretationIndex = lsystemInterpretationIndex;
}

void InterpretationEditorWidget::setAction(CharInterpretationAction action)
{
    actionComboBox->setCurrentIndex(static_cast<int>(action));
}

void InterpretationEditorWidget::setSymbol(char c)
{
    std::stringstream ss;
    ss << c;
    symbolLineEdit->setText(ss.str().c_str());
}

void InterpretationEditorWidget::setParam(int i)
{
    std::stringstream ss;
    ss << i;
    paramLineEdit->setText(ss.str().c_str());
}
