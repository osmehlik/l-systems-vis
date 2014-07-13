//
// File:      ruleeditorwidget.cpp
// Purpose:   A widget to view/edit one rule in a L-System.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

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

int RuleEditorWidget::getIndexInParent()
{
    return parent()->children().indexOf(this) - 1;
}

void RuleEditorWidget::onRemoveClicked()
{
    this->deleteLater();
    emit removed(getIndexInParent());
}

void RuleEditorWidget::onFromChanged()
{
    emit changed(getIndexInParent(), inputFrom->text().toStdString(), inputTo->text().toStdString());
}

void RuleEditorWidget::onToChanged()
{
    emit changed(getIndexInParent(), inputFrom->text().toStdString(), inputTo->text().toStdString());
}
