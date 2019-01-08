#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsObject>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>

#pragma once

//Область экрана с анимированным текстом, оповещающим игрока о состоянии игры
class TextArea : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

public:
    TextArea(QRectF rect, QString n_label);

    void setText(QString newtext);

    void clear();

    QString getText();

private:
    QGraphicsTextItem* text;      //текст, выводящийся на экран
    QString temptext;             //последовательность символов, которые нужно вывести на экран
    int temppos;                  //текущая позиция в списке символов, которые нужно вывести на экран

};

#endif // TEXTAREA_H
