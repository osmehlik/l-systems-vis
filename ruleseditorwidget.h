#ifndef RULESEDITORWIDGET_H
#define RULESEDITORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "lsystem.h"

class RulesEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulesEditorWidget(QWidget *parent = 0);
    void addRule(const QString &from = "", const QString &to = "");
    //void addAddButton();
    void removeContents();
    void loadRules(LSystem *lsystem);

protected:
    QVBoxLayout *vbox;

public:
signals:
    void ruleWasChanged(int i, std::string from, std::string to);
    void ruleWasAdded();
    void ruleWasRemoved(int i);

public slots:
    void onAddClicked();
};

#endif // RULESEDITORWIDGET_H
