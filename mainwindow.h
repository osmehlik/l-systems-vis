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
    void onOpenClicked();
    void onSaveAsClicked();
    void onShowHideBrowserClicked();
    void onShowHidePropertiesClicked();
    void onShowHideRulesClicked();
    void onRandomizeColorsClicked();

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private slots:
    void on_addRuleButton_clicked();    
    void on_addInterpretationButton_clicked();

private:

    void openFile(QFile *f);

    Ui::MainWindow *ui;
    QFileSystemModel *fileSystemModel;
    LSystem *lSystem;
};

#endif // MAINWINDOW_H
