//
// File:      ruleeditorwidget.h
// Purpose:   A widget to view/edit one rule in a L-System.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#ifndef RULE_EDITOR_WIDGET_H
#define RULE_EDITOR_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

class RuleEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RuleEditorWidget(QWidget *parent = 0, const QString &from = "", const QString &to = "");
    int getIndexInParent();

signals:
    void changed(int i, std::string from, std::string to);
    void removed(int i);

public slots:
    void onRemoveClicked();
    void onFromChanged();
    void onToChanged();
protected:
    QLineEdit *inputFrom;
    QLineEdit *inputTo;
};

#endif // RULEEDITORWIDGET_H
