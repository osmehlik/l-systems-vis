#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QFileSystemModel>
#include "lsystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onNewClicked();
    void onOpenClicked();
    void onSaveClicked();
    void onSaveAsClicked();
    void onShowHideBrowserClicked();
    void onShowHidePropertiesClicked();
    void onShowHideRulesClicked();
    void onRandomizeColorsClicked();

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onAxiomChanged();
    void onLSystemChanged();
private slots:
    void on_addRuleButton_clicked();    
    void on_addInterpretationButton_clicked();

private:
    bool unchangedOrConfirmedLosingChanges();
    void openFile(QFile *f);

    Ui::MainWindow *ui;
    QFileSystemModel *fileSystemModel;
    LSystem *lSystem;
};

#endif // MAINWINDOW_H
