#ifndef RULE_EDITOR_LIST_WIDGET_H
#define RULE_EDITOR_LIST_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "lsystem.h"

class RuleEditorListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RuleEditorListWidget(QWidget *parent = 0);
    void addRule(const QString &from = "", const QString &to = "");
    //void addAddButton();
    void removeContents();

protected:
    QVBoxLayout *vbox;

public:
signals:
    void ruleWasChanged(int i, std::string from, std::string to);
    void ruleWasAdded();
    void ruleWasRemoved(int i);

public slots:
    void load(LSystem *lsystem);
    void onAddClicked();
};

#endif // RULESEDITORWIDGET_H
