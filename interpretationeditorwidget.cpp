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
    interpretationActionComboBox = new QComboBox(this);

    QLabel *parameterLabel = new QLabel("Parameter:", this);
    parameterLineEdit = new QLineEdit(this);
    parameterLineEdit->setEnabled(false); // default value move forward currently requires no argument

    interpretationActionComboBox->addItem("Move Forward");
    interpretationActionComboBox->addItem("Draw Forward");
    interpretationActionComboBox->addItem("Rotate");
    interpretationActionComboBox->addItem("Push Matrix");
    interpretationActionComboBox->addItem("Pop Matrix");

    connect(interpretationActionComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInterpretationIndexChanged(int)));


    hbox->addWidget(symbolLabel);
    hbox->addWidget(symbolLineEdit);
    hbox->addWidget(interpretationLabel);
    hbox->addWidget(interpretationActionComboBox);
    hbox->addWidget(parameterLabel);
    hbox->addWidget(parameterLineEdit);

    setLayout(hbox);
}

void InterpretationEditorWidget::onInterpretationIndexChanged(int i)
{
    parameterLineEdit->setEnabled(i == ROTATE);
}

void InterpretationEditorWidget::setAction(CharInterpretationAction action)
{
    interpretationActionComboBox->setCurrentIndex(static_cast<int>(action));
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
    parameterLineEdit->setText(ss.str().c_str());
}
