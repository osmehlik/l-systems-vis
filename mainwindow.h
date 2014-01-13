#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateControls();

public slots:
    void onOpenClicked();
    void onShowHideBrowserClicked();
    void onShowHidePropertiesClicked();
    void onRandomizeColorsClicked();

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:

    void openFile(QFile *f);

    Ui::MainWindow *ui;
    QFileSystemModel *fileSystemModel;
};

#endif // MAINWINDOW_H
