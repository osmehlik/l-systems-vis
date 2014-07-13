//
// File:      interpretationeditorwidget.cpp
// Purpose:   A widget to view and edit an interpretation of a symbol in a L-System.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#include "interpretationeditorwidget.h"
#include "lsystem.h"
#include <QPushButton>
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

    QPushButton *removeButton = new QPushButton("Remove", this);

    connect(actionComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInterpretationIndexChanged(int)));
    connect(symbolLineEdit, SIGNAL(editingFinished()),
            this, SLOT(onSymbolChanged()));
    connect(paramLineEdit, SIGNAL(editingFinished()),
            this, SLOT(onParamChanged()));
    connect(removeButton, SIGNAL(clicked()),
            this, SLOT(onRemoveClicked()));

    hbox->addWidget(symbolLabel);
    hbox->addWidget(symbolLineEdit);
    hbox->addWidget(interpretationLabel);
    hbox->addWidget(actionComboBox);
    hbox->addWidget(parameterLabel);
    hbox->addWidget(paramLineEdit);

    hbox->addWidget(removeButton);

    setLayout(hbox);
}

int InterpretationEditorWidget::getIndexInParent()
{
    return parent()->children().indexOf(this) - 1;
}

void InterpretationEditorWidget::onInterpretationIndexChanged(int i)
{
    paramLineEdit->setEnabled(i == ROTATE);
    emit changed(getIndexInParent(), getInterpretation());
}

void InterpretationEditorWidget::onSymbolChanged()
{
    emit changed(getIndexInParent(), getInterpretation());
}

void InterpretationEditorWidget::onParamChanged()
{
    emit changed(getIndexInParent(), getInterpretation());
}

void InterpretationEditorWidget::onRemoveClicked()
{
    this->deleteLater();
    emit removed(getIndexInParent());
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

char InterpretationEditorWidget::getSymbol()
{
    std::string s = symbolLineEdit->text().toStdString();
    return static_cast<char>(s.size() > 0 ? s.at(0) : ' ');
}

CharInterpretationAction InterpretationEditorWidget::getAction()
{
    return static_cast<CharInterpretationAction>(actionComboBox->currentIndex());
}

int InterpretationEditorWidget::getParam()
{
    std::stringstream ss;
    ss.str(paramLineEdit->text().toStdString());
    int param;

    ss >> param;
    return param;
}

CharInterpretation InterpretationEditorWidget::getInterpretation()
{
    CharInterpretation result;

    result.symbol = getSymbol();
    result.action = getAction();
    result.param = getParam();

    return result;
}
