#ifndef INTERPRETATIONEDITORWIDGET_H
#define INTERPRETATIONEDITORWIDGET_H

#include <QWidget>
#include <QLineEdit>

class InterpretationEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InterpretationEditorWidget(QWidget *parent = 0);
protected:
    QLineEdit *parameterLineEdit;

signals:

public slots:
    void onInterpretationIndexChanged(int i);

};

#endif // INTERPRETATIONEDITORWIDGET_H
