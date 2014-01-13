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
            ui->lSystemView, SLOT(valueStartXChanged(double)));
    connect(ui->startYDoubleSpinBox, SIGNAL(valueChanged(double)),
            ui->lSystemView, SLOT(valueStartYChanged(double)));
    connect(ui->startRotationSpinBox, SIGNAL(valueChanged(int)),
            ui->lSystemView, SLOT(valueStartRotChanged(int)));
    connect(ui->iterationsSpinBox, SIGNAL(valueChanged(int)),
            ui->lSystemView, SLOT(valueIterationsChanged(int)));
    connect(ui->stepSpinBox, SIGNAL(valueChanged(int)),
            ui->lSystemView, SLOT(valueStepLengthChanged(int)));

    connect(ui->backgroundWidget, SIGNAL(colorChanged(QColor)),
            ui->lSystemView, SLOT(setBackgroundColor(QColor)));
    connect(ui->foregroundWidget, SIGNAL(colorChanged(QColor)),
            ui->lSystemView, SLOT(setForegroundColor(QColor)));

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenClicked()));
    connect(ui->actionShowHideBrowser, SIGNAL(triggered()), this, SLOT(onShowHideBrowserClicked()));
    connect(ui->actionShowHideProperties, SIGNAL(triggered()), this, SLOT(onShowHidePropertiesClicked()));

    connect(ui->randomizeButton, SIGNAL(clicked()), this, SLOT(onRandomizeColorsClicked()));

    updateControls();


    // l-system directory browser

    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::homePath());

    QStringList nameFilters;

    nameFilters.append("*.lsys");

    fileSystemModel->setNameFilters(nameFilters);

    ui->treeView->setModel(fileSystemModel);


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

void MainWindow::onShowHideBrowserClicked()
{
    ui->treeView->setVisible(!ui->treeView->isVisible());
}

void MainWindow::onShowHidePropertiesClicked()
{
    ui->parameters->setVisible(!ui->parameters->isVisible());
}

void MainWindow::onRandomizeColorsClicked()
{
    ui->lSystemView->lsystem.setRandomColors();
    updateControls();
    update();
}

void MainWindow::openFile(QFile *f)
{
    ui->lSystemView->lsystem.load(f);
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
    ui->startXDoubleSpinBox->setValue(ui->lSystemView->lsystem.startX);
    ui->startYDoubleSpinBox->setValue(ui->lSystemView->lsystem.startY);
    ui->startRotationSpinBox->setValue(ui->lSystemView->lsystem.startRot);
    ui->iterationsSpinBox->setValue(ui->lSystemView->lsystem.iterations);
    ui->stepSpinBox->setValue(ui->lSystemView->lsystem.stepLength);
    ui->backgroundWidget->setValue(ui->lSystemView->lsystem.backgroundColor);
    ui->foregroundWidget->setValue(ui->lSystemView->lsystem.foregroundColor);
}
