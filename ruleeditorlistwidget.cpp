//
// File:      ruleeditorlistwidget.cpp
// Purpose:   A widget showing a list of rule editor widgets.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#include "ruleeditorlistwidget.h"
#include "ruleeditorwidget.h"
#include <QPushButton>

RuleEditorListWidget::RuleEditorListWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);
    setLayout(vbox);

    addRule();
}

void RuleEditorListWidget::removeContents()
{
    QLayoutItem *child;
    while ((child = vbox->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }
}

void RuleEditorListWidget::addRule(const QString &from, const QString &to) {
    RuleEditorWidget *rule = new RuleEditorWidget(this, from, to);

    connect(rule, SIGNAL(removed(int)), this, SIGNAL(ruleWasRemoved(int)));
    connect(rule, SIGNAL(changed(int, std::string, std::string)), this, SIGNAL(ruleWasChanged(int,std::string,std::string)));


    vbox->addWidget(rule);
    emit ruleWasAdded();
}

/*
void RulesEditorWidget::addAddButton()
{
    QPushButton *add = new QPushButton("Add", this);
    vbox->addWidget(add);


    connect(add, SIGNAL(clicked()), this, SLOT(onAddClicked()));
}
*/

void RuleEditorListWidget::load(LSystem *lsystem)
{
    removeContents();

    for (size_t i(0); i < lsystem->getNumRules(); ++i) {
        blockSignals(true);
        addRule(lsystem->getRuleFrom(i).c_str(), lsystem->getRuleTo(i).c_str());
        blockSignals(false);
    }

    update();
    //addAddButton();
}

void RuleEditorListWidget::onAddClicked()
{
    addRule();
}
