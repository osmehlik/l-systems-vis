#include "interpretationeditorwidget.h"
#include "lsystem.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QAction>

InterpretationEditorWidget::InterpretationEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    QLabel *symbolLabel = new QLabel("Symbol:", this);
    QLineEdit *symbolLineEdit = new QLineEdit(this);

    symbolLineEdit->setMaxLength(1);

    QLabel *interpretationLabel = new QLabel("Interpretation:", this);
    QComboBox *interpretationComboBox = new QComboBox(this);

    QLabel *parameterLabel = new QLabel("Parameter:", this);
    parameterLineEdit = new QLineEdit(this);
    parameterLineEdit->setEnabled(false); // default value move forward currently requires no argument

    interpretationComboBox->addItem("Move Forward");
    interpretationComboBox->addItem("Draw Forward");
    interpretationComboBox->addItem("Rotate");
    interpretationComboBox->addItem("Push Matrix");
    interpretationComboBox->addItem("Pop Matrix");

    connect(interpretationComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInterpretationIndexChanged(int)));


    hbox->addWidget(symbolLabel);
    hbox->addWidget(symbolLineEdit);
    hbox->addWidget(interpretationLabel);
    hbox->addWidget(interpretationComboBox);
    hbox->addWidget(parameterLabel);
    hbox->addWidget(parameterLineEdit);

    setLayout(hbox);
}

void InterpretationEditorWidget::onInterpretationIndexChanged(int i)
{
    parameterLineEdit->setEnabled(i == ROTATE);
}
