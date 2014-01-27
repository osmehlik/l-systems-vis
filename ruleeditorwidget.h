#ifndef RULEEDITORWIDGET_H
#define RULEEDITORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class RuleEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RuleEditorWidget(QWidget *parent = 0, const QString &from = "", const QString &to = "");

signals:

public slots:
    void onRemoveClicked();
    void onFromChanged();
    void onToChanged();
};

#endif // RULEEDITORWIDGET_H
