#include "colorwidget.h"
#include <QPainter>
#include <QColorDialog>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    managedColor = Qt::white;
    setMinimumWidth(32);
    setMinimumHeight(16);
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
}
