//
// File:      interpretationeditorlistwidget.h
// Purpose:   A widget showing a list of interpretation editor widgets.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#ifndef INTERPRETATION_EDITOR_LIST_WIDGET_H
#define INTERPRETATION_EDITOR_LIST_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "lsystem.h"

class InterpretationEditorListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InterpretationEditorListWidget(QWidget *parent = 0);
    void addInterpretation(char c, CharInterpretationAction action, int param = 0);

    void removeContents();
protected:
    QVBoxLayout *vbox;
    LSystem *lsystem;
    size_t currentInterpretationIndex;
signals:
    void interpretationWasChanged(int i, CharInterpretation ci);
    void interpretationWasAdded();
    void interpretationWasRemoved(int i);

public slots:
    void load(LSystem *lSystem);
};

#endif // INTERPRETATIONSEDITORWIDGET_H
