#ifndef INTERPRETATIONEDITORWIDGET_H
#define INTERPRETATIONEDITORWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include "lsystem.h"

class InterpretationEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InterpretationEditorWidget(QWidget *parent = 0);
    void setSymbol(char c);
    void setAction(CharInterpretationAction action);
    void setParam(int i);
    char getSymbol();
    CharInterpretationAction getAction();
    int getParam();
    CharInterpretation getInterpretation();
    int getIndexInParent();
protected:
    QLineEdit *symbolLineEdit;
    QComboBox *actionComboBox;
    QLineEdit *paramLineEdit;
    LSystem *lsystem;
signals:
    void changed(int i, CharInterpretation ci);
    void removed(int i);
public slots:
    void onInterpretationIndexChanged(int i);
    void onSymbolChanged();
    void onParamChanged();
    void onRemoveClicked();
};

#endif // INTERPRETATIONEDITORWIDGET_H
