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

    setWindowFilePath("Untitled");

    // Connect actions to menu items.
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNewClicked()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenClicked()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSaveClicked()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(onSaveAsClicked()));
    connect(ui->actionShowHideBrowser, SIGNAL(triggered()), this, SLOT(onShowHideBrowserClicked()));
    connect(ui->actionShowHideProperties, SIGNAL(triggered()), this, SLOT(onShowHidePropertiesClicked()));
    connect(ui->actionShowHideRules, SIGNAL(triggered()), this, SLOT(onShowHideRulesClicked()));

    // After L-System is opened, update rules and interpretations editor widget contents.
    connect(lSystem, SIGNAL(loaded(LSystem*)), ui->rulesEditorWidget, SLOT(load(LSystem*)));
    connect(lSystem, SIGNAL(loaded(LSystem*)), ui->interpretationsEditorWidget, SLOT(load(LSystem*)));

    // Update L-System on controls change
    connect(ui->startXDoubleSpinBox, SIGNAL(valueChanged(double)), lSystem, SLOT(setStartX(double)));
    connect(ui->startYDoubleSpinBox, SIGNAL(valueChanged(double)), lSystem, SLOT(setStartY(double)));
    connect(ui->startRotationSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setStartRot(int)));
    connect(ui->iterationsSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setIterations(int)));
    connect(ui->stepSpinBox, SIGNAL(valueChanged(int)), lSystem, SLOT(setStepLength(int)));
    connect(ui->backgroundWidget, SIGNAL(colorChanged(QColor)), lSystem, SLOT(setBackgroundColor(QColor)));
    connect(ui->foregroundWidget, SIGNAL(colorChanged(QColor)), lSystem, SLOT(setForegroundColor(QColor)));

    // Update controls on L-System change
    connect(lSystem, SIGNAL(startXWasChanged(double)), ui->startXDoubleSpinBox, SLOT(setValue(double)));
    connect(lSystem, SIGNAL(startYWasChanged(double)), ui->startYDoubleSpinBox, SLOT(setValue(double)));
    connect(lSystem, SIGNAL(startRotWasChanged(int)), ui->startRotationSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(iterationsWasChanged(int)), ui->iterationsSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(stepLengthWasChanged(int)), ui->stepSpinBox, SLOT(setValue(int)));
    connect(lSystem, SIGNAL(backgroundColorWasChanged(QColor)), ui->backgroundWidget, SLOT(setValue(QColor)));
    connect(lSystem, SIGNAL(foregroundColorWasChanged(QColor)), ui->foregroundWidget, SLOT(setValue(QColor)));

    // Connect rules editing signals to slots.
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasAdded()), lSystem, SLOT(addRule()));
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasRemoved(int)), lSystem, SLOT(removeRule(int)));
    connect(ui->rulesEditorWidget, SIGNAL(ruleWasChanged(int,std::string,std::string)), lSystem, SLOT(setRule(int,std::string,std::string)));

    // Connect interpretation editing signals to slots
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasAdded()), lSystem, SLOT(addInterpretation()));
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasChanged(int,CharInterpretation)), lSystem, SLOT(setInterpretation(int,CharInterpretation)));
    connect(ui->interpretationsEditorWidget, SIGNAL(interpretationWasRemoved(int)), lSystem, SLOT(removeInterpretation(int)));


    // Redraw lSystemView on lSystem change.
    connect(lSystem, SIGNAL(changed()), ui->centralWidget, SLOT(update()));

    connect(ui->randomizeButton, SIGNAL(clicked()), this, SLOT(onRandomizeColorsClicked()));


    connect(ui->axiomLineEdit, SIGNAL(editingFinished()), this, SLOT(onAxiomChanged()));


    connect(lSystem, SIGNAL(changed()), this, SLOT(onLSystemChanged()));

    // Set menu items shortcuts
    ui->actionNew->setShortcuts(QKeySequence::New);
    ui->actionOpen->setShortcuts(QKeySequence::Open);
    ui->actionSave->setShortcuts(QKeySequence::Save);
    ui->actionSaveAs->setShortcuts(QKeySequence::SaveAs);

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

void MainWindow::onNewClicked()
{
    if (unchangedOrConfirmedLosingChanges()) {
        lSystem->loadDefault();
        ui->axiomLineEdit->setText(lSystem->getStart().c_str());
        setWindowModified(false);
        setWindowFilePath("Untitled");
    }
}

void MainWindow::onOpenClicked()
{
    if (unchangedOrConfirmedLosingChanges()) {
        // find name of a file
        QString s = QFileDialog::getOpenFileName(
            this,
            tr("Open L-System File"),
            "",
            tr("L-System Files (*.lsys)")
        );
        QFile f(s);

        openFile(&f);
    }
}

void MainWindow::onSaveClicked()
{
    if (lSystem->getPath().empty()) {
        onSaveAsClicked();
    } else {
        QFile f(lSystem->getPath().c_str());
        lSystem->save(&f);
    }
}

void MainWindow::onSaveAsClicked()
{
    QString s = QFileDialog::getSaveFileName(this,tr("Save L-System File"), "", tr("L-System Files (*.lsys"));

    // do not save if user pressed cancel
    if (s.isNull()) { return; }

    QFile f(s);

    lSystem->save(&f);
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

bool MainWindow::unchangedOrConfirmedLosingChanges()
{
    if (isWindowModified()) {
        QMessageBox::StandardButton answer;
        answer = QMessageBox::question(
            this, "Question", "Current file was modified and not saved. Load new file?",
            QMessageBox::Yes | QMessageBox::No
        );
        if (answer == QMessageBox::No) {
            return false;
        }
    }
    return true;
}


void MainWindow::openFile(QFile *f)
{
    lSystem->load(f);
    ui->axiomLineEdit->setText(lSystem->getStart().c_str());
    setWindowModified(false);
    setWindowFilePath(f->fileName());
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (unchangedOrConfirmedLosingChanges())
    {
        QString path = fileSystemModel->filePath(ui->treeView->selectionModel()->currentIndex());

        QFile f(path);
        QFileInfo fi(f);

        // skip opening when user clicked on directory
        if (!fi.isDir()) {
            openFile(&f);
        }
    }
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

void MainWindow::onLSystemChanged()
{
    setWindowModified(true);
}
