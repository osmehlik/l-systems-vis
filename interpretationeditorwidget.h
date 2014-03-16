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
protected:
    QLineEdit *symbolLineEdit;
    QComboBox *interpretationActionComboBox;
    QLineEdit *parameterLineEdit;

signals:

public slots:
    void onInterpretationIndexChanged(int i);

};

#endif // INTERPRETATIONEDITORWIDGET_H
