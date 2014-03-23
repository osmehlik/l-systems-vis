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
    void setLSystem(LSystem *lsystem, int lSystemInterpretationIndex);
protected:
    QLineEdit *symbolLineEdit;
    QComboBox *actionComboBox;
    QLineEdit *paramLineEdit;
    LSystem *lsystem;
    int lsystemInterpretationIndex;
signals:

public slots:
    void onInterpretationIndexChanged(int i);
    void onSymbolChanged();
    void onParamChanged();
};

#endif // INTERPRETATIONEDITORWIDGET_H
