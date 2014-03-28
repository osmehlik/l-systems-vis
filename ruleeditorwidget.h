#ifndef RULEEDITORWIDGET_H
#define RULEEDITORWIDGET_H

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
