#ifndef INTERPRETATIONSEDITORWIDGET_H
#define INTERPRETATIONSEDITORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "lsystem.h"

class InterpretationsEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InterpretationsEditorWidget(QWidget *parent = 0);
    void addInterpretation(char c, CharInterpretationAction action, int param = 0);
    void loadInterpretations(LSystem *lSystem);
    void removeContents();
protected:
    QVBoxLayout *vbox;
    LSystem *lsystem;
    size_t currentInterpretationIndex;
signals:

public slots:

};

#endif // INTERPRETATIONSEDITORWIDGET_H
