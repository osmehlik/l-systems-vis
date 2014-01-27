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

    connect(ui->startXDoubleSpinBox, SIGNAL(valueChanged(double)),
            ui->centralWidget, SLOT(valueStartXChanged(double)));
    connect(ui->startYDoubleSpinBox, SIGNAL(valueChanged(double)),
            ui->centralWidget, SLOT(valueStartYChanged(double)));
    connect(ui->startRotationSpinBox, SIGNAL(valueChanged(int)),
            ui->centralWidget, SLOT(valueStartRotChanged(int)));
    connect(ui->iterationsSpinBox, SIGNAL(valueChanged(int)),
            ui->centralWidget, SLOT(valueIterationsChanged(int)));
    connect(ui->stepSpinBox, SIGNAL(valueChanged(int)),
            ui->centralWidget, SLOT(valueStepLengthChanged(int)));

    connect(ui->backgroundWidget, SIGNAL(colorChanged(QColor)),
            ui->centralWidget, SLOT(setBackgroundColor(QColor)));
    connect(ui->foregroundWidget, SIGNAL(colorChanged(QColor)),
            ui->centralWidget, SLOT(setForegroundColor(QColor)));

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenClicked()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(onSaveAsClicked()));
    connect(ui->actionShowHideBrowser, SIGNAL(triggered()), this, SLOT(onShowHideBrowserClicked()));
    connect(ui->actionShowHideProperties, SIGNAL(triggered()), this, SLOT(onShowHidePropertiesClicked()));
    connect(ui->actionShowHideRules, SIGNAL(triggered()), this, SLOT(onShowHideRulesClicked()));

    connect(ui->randomizeButton, SIGNAL(clicked()), this, SLOT(onRandomizeColorsClicked()));

    updateControls();


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

    ui->centralWidget->lsystem.save(f);

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
    ui->centralWidget->lsystem.setRandomColors();
    updateControls();
    update();
}

void MainWindow::openFile(QFile *f)
{
    ui->centralWidget->lsystem.load(f);
    ui->rulesEditorWidget->loadRules(&(ui->centralWidget->lsystem));
    updateControls();
    update();
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QString path = fileSystemModel->filePath(ui->treeView->selectionModel()->currentIndex());

    QFile *f = new QFile(path);

    openFile(f);
}


void MainWindow::updateControls()
{
    ui->startXDoubleSpinBox->setValue(ui->centralWidget->lsystem.startX);
    ui->startYDoubleSpinBox->setValue(ui->centralWidget->lsystem.startY);
    ui->startRotationSpinBox->setValue(ui->centralWidget->lsystem.startRot);
    ui->iterationsSpinBox->setValue(ui->centralWidget->lsystem.iterations);
    ui->stepSpinBox->setValue(ui->centralWidget->lsystem.stepLength);
    ui->backgroundWidget->setValue(ui->centralWidget->lsystem.backgroundColor);
    ui->foregroundWidget->setValue(ui->centralWidget->lsystem.foregroundColor);
}

void MainWindow::on_addRuleButton_clicked()
{
   ui->rulesEditorWidget->addRule();
}
