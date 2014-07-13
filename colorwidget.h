//
// File:      colorwidget.h
// Purpose:   A widget to view and edit color.
// Copyright: Oldrich Smehlik, <oldrich@smehlik.net>
// License:   See LICENSE.md file
//

#ifndef COLOR_WIDGET_H
#define COLOR_WIDGET_H

#include <QWidget>

class ColorWidget : public QWidget
{
    Q_OBJECT

    QColor managedColor;
    QAction *copyAction;

public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();

protected:
    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent * event);
signals:
    void colorChanged(QColor color);
public slots:
    void showContextMenu(const QPoint &point);
    void copyColorToClipboard();
    void setValue(QColor color);
};

#endif // COLORWIDGET_H
