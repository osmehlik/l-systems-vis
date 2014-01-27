#include "ruleseditorwidget.h"
#include "ruleeditorwidget.h"
#include <QPushButton>

RulesEditorWidget::RulesEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);
    setLayout(vbox);

    //addRule();
    //addRule();
    //addRule();
    addRule();
    //addAddButton();
}

void RulesEditorWidget::removeContents()
{
    QLayoutItem *child;
    while ((child = vbox->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }
}

void RulesEditorWidget::addRule(const QString &from, const QString &to) {
    RuleEditorWidget *rule = new RuleEditorWidget(this, from, to);
    vbox->addWidget(rule);
}

/*
void RulesEditorWidget::addAddButton()
{
    QPushButton *add = new QPushButton("Add", this);
    vbox->addWidget(add);


    connect(add, SIGNAL(clicked()), this, SLOT(onAddClicked()));
}
*/

void RulesEditorWidget::loadRules(LSystem *lsystem)
{
    removeContents();
    for(Rules::iterator rulesIt = lsystem->rules.begin(); rulesIt != lsystem->rules.end(); ++rulesIt) {
        addRule(rulesIt->first.c_str(), rulesIt->second.c_str());
    }
    //addAddButton();
}

void RulesEditorWidget::onAddClicked()
{
    addRule();
}
