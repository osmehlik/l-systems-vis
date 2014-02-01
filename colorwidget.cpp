#include "colorwidget.h"
#include <QPainter>
#include <QColorDialog>
#include <QMenu>
#include <QClipboard>
#include <QApplication>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    managedColor = Qt::white;
    setMinimumWidth(32);
    setMinimumHeight(16);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showContextMenu(QPoint)));

    copyAction = new QAction("Copy", this);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyColorToClipboard()));
}

ColorWidget::~ColorWidget()
{
    delete copyAction;
}

void ColorWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    int w(size().width());
    int h(size().height());

    QRect widgetArea(0, 0, w - 1, h - 1);

    painter.fillRect(widgetArea, managedColor);
    painter.drawRect(widgetArea);
}

void ColorWidget::mouseReleaseEvent(QMouseEvent * event)
{
    QColor selectedColor = QColorDialog::getColor(
        managedColor, this, QString::fromUtf8("Set Color:"));

    if (selectedColor.isValid() && (selectedColor != managedColor)) {
        managedColor = selectedColor;
        emit colorChanged(managedColor);
    }
    update();
}

void ColorWidget::setValue(QColor color)
{
    managedColor = color;
    emit colorChanged(managedColor);
    update();
}

void ColorWidget::showContextMenu(const QPoint &point)
{
    QPoint globalCoordsPoint = mapToGlobal(point);

    QMenu menu;

    menu.addAction(copyAction);
    menu.exec(globalCoordsPoint);
}

void ColorWidget::copyColorToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();

    clipboard->setText(managedColor.name());
}
