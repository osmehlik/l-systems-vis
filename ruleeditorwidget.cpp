#include "ruleeditorwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "mainwindow.h"

RuleEditorWidget::RuleEditorWidget(QWidget *parent, const QString &from, const QString &to) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    inputFrom = new QLineEdit(this);
    QLabel *labelFrom = new QLabel("From:", this);
    QLabel *labelTo = new QLabel("To:", this);
    inputTo = new QLineEdit(this);
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
    int i = parent()->children().indexOf(this) - 1;
    emit removed(i);
}

void RuleEditorWidget::onFromChanged()
{
    int i = parent()->children().indexOf(this) - 1;
    emit changed(i, inputFrom->text().toStdString(), inputTo->text().toStdString());
}

void RuleEditorWidget::onToChanged()
{
    int i = parent()->children().indexOf(this) - 1;
    emit changed(i, inputFrom->text().toStdString(), inputTo->text().toStdString());
}
