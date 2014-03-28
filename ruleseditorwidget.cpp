#include "ruleseditorwidget.h"
#include "ruleeditorwidget.h"
#include <QPushButton>

RulesEditorWidget::RulesEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    vbox = new QVBoxLayout(this);
    setLayout(vbox);

    addRule();
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

void RulesEditorWidget::loadRules(LSystem *lsystem)
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

void RulesEditorWidget::onAddClicked()
{
    addRule();
}
