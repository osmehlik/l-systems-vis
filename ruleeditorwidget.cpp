#include "ruleeditorwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

RuleEditorWidget::RuleEditorWidget(QWidget *parent, const QString &from, const QString &to) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    QLineEdit *inputFrom = new QLineEdit(this);
    QLabel *labelFrom = new QLabel("From:", this);
    QLabel *labelTo = new QLabel("To:", this);
    QLineEdit *inputTo = new QLineEdit(this);
    QPushButton *remove = new QPushButton("Remove", this);

    inputFrom->setText(from);
    inputTo->setText(to);

    hbox->addWidget(labelFrom);
    hbox->addWidget(inputFrom);
    hbox->addWidget(labelTo);
    hbox->addWidget(inputTo);
    hbox->addWidget(remove);

    connect(remove, SIGNAL(clicked()), this, SLOT(onRemoveClicked()));
    connect(inputFrom, SIGNAL(editingFinished()), this, SLOT(onFromChanged()));
    connect(inputTo, SIGNAL(editingFinished()), this, SLOT(onToChanged()));

    setLayout(hbox);
}

void RuleEditorWidget::onRemoveClicked()
{
    this->deleteLater();
}

void RuleEditorWidget::onFromChanged()
{
    int index = parent()->children().indexOf(this);

}

void RuleEditorWidget::onToChanged()
{

}
