#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lsystemview.h"
#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFileSystemModel>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lSystem = new LSystem();
    ui->centralWidget->setLSystem(lSystem);

    // Update lsystem when controls changes


    connect(ui->startXDoubleSpinBox, SIGNAL(valueChanged(double)), lSystem, SLOT(setStartX(double)));
    connect(ui->startYDoubleSpinBox, SIGNAL(valueChanged(double)), lSystem, SLOT(setStartY(double)));
    connect(ui->startRotationSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setStartRot(int)));
    connect(ui->iterationsSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setIterations(int)));
    connect(ui->stepSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setStepLength(int)));
    connect(ui->backgroundWidget, SIGNAL(colorChanged(QColor)), lSystem, SLOT(setBackgroundColor(QColor)));
    connect(ui->foregroundWidget, SIGNAL(colorChanged(QColor)), lSystem, SLOT(setForegroundColor(QColor)));


    // Update controls when lsystem changes

    connect(lSystem, SIGNAL(startXWasChanged(double)), ui->startXDoubleSpinBox, SLOT(setValue(double)));
    connect(lSystem, SIGNAL(startYWasChanged(double)), ui->startYDoubleSpinBox, SLOT(setValue(double)));
    connect(lSystem, SIGNAL(startRotWasChanged(int)), ui->startRotationSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(iterationsWasChanged(int)), ui->iterationsSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(stepLengthWasChanged(int)), ui->stepSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(backgroundColorWasChanged(QColor)), ui->backgroundWidget, SLOT(setValue(QColor)));
    connect(lSystem, SIGNAL(foregroundColorWasChanged(QColor)), ui->foregroundWidget, SLOT(setValue(QColor)));

    // Redraw lSystemView on lSystem change.
    connect(lSystem, SIGNAL(lSystemWasChanged()), ui->centralWidget, SLOT(update()));

    // Connect actions to menu items.
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenClicked()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(onSaveAsClicked()));
    connect(ui->actionShowHideBrowser, SIGNAL(triggered()), this, SLOT(onShowHideBrowserClicked()));
    connect(ui->actionShowHideProperties, SIGNAL(triggered()), this, SLOT(onShowHidePropertiesClicked()));
    connect(ui->actionShowHideRules, SIGNAL(triggered()), this, SLOT(onShowHideRulesClicked()));

    connect(ui->randomizeButton, SIGNAL(clicked()), this, SLOT(onRandomizeColorsClicked()));

    // Connect rules editing signals to slots.
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasAdded()), lSystem, SLOT(addRule()));
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasRemoved(int)), lSystem, SLOT(removeRule(int)));
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasChanged(int,std::string,std::string)), lSystem, SLOT(setRule(int,std::string,std::string)));

    // Connect interpretation editing signals to slots
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasAdded()), lSystem, SLOT(addInterpretation()));
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasChanged(int,CharInterpretation)), lSystem, SLOT(setInterpretation(int,CharInterpretation)));
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasRemoved(int)), lSystem, SLOT(removeInterpretation(int)));

    connect(ui->axiomLineEdit, SIGNAL(editingFinished()), this, SLOT(onAxiomChanged()));


    // l-system directory browser

    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::homePath());

    QStringList nameFilters;

    nameFilters.append("*.lsys");

    fileSystemModel->setNameFilters(nameFilters);

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(1);
    ui->treeView->setHeaderHidden(true);


    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onSelectionChanged(const QItemSelection &, const QItemSelection &)));
}

MainWindow::~MainWindow()
{
    delete lSystem;
    delete ui;
}

void MainWindow::onOpenClicked()
{
    QString s = QFileDialog::getOpenFileName(this,
                                               tr("Open L-System File"), "", tr("L-System Files (*.lsys)"));
    QFile *f = new QFile(s);

    openFile(f);
}

void MainWindow::onSaveAsClicked()
{
    QString s = QFileDialog::getSaveFileName(this,tr("Save L-System File"), "", tr("L-System Files (*.lsys"));

    QFile *f = new QFile(s);

    lSystem->save(f);

    delete f;
}

void MainWindow::onShowHideBrowserClicked()
{
    ui->directoryBrowserDockWidget->setVisible(!ui->directoryBrowserDockWidget->isVisible());
}

void MainWindow::onShowHidePropertiesClicked()
{
    ui->parametersDockWidget->setVisible(!ui->parametersDockWidget->isVisible());
}

void MainWindow::onShowHideRulesClicked()
{
    ui->rulesEditorDockWidget->setVisible(!ui->rulesEditorDockWidget->isVisible());
}

void MainWindow::onRandomizeColorsClicked()
{
    lSystem->setRandomColors();
    update();
}

void MainWindow::openFile(QFile *f)
{
    lSystem->load(f);
    ui->rulesEditorWidget->loadRules(lSystem);
    ui->interpretationsEditorWidget->loadInterpretations(lSystem);
    ui->axiomLineEdit->setText(lSystem->getStart().c_str());
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QString path = fileSystemModel->filePath(ui->treeView->selectionModel()->currentIndex());

    QFile *f = new QFile(path);

    openFile(f);
}

void MainWindow::on_addRuleButton_clicked()
{
    ui->rulesEditorWidget->addRule();
}

void MainWindow::on_addInterpretationButton_clicked()
{
    lSystem->addInterpretation();
    ui->interpretationsEditorWidget->addInterpretation('?', MOVE_FORWARD);
}

void MainWindow::onAxiomChanged()
{
    lSystem->setStart(ui->axiomLineEdit->text().toStdString());
}
