#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

class ColorWidget : public QWidget
{
    Q_OBJECT

    QColor managedColor;
public:
    explicit ColorWidget(QWidget *parent = 0);
    void setValue(QColor color);
protected:
    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent * event);
signals:
    void colorChanged(QColor color);
public slots:

};

#endif // COLORWIDGET_H
