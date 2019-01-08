#include "textarea.h"
#include <QWidget>
#include <QPainter>
#include <QGraphicsObject>
#include <QMouseEvent>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>

TextArea::TextArea(QRectF rect, QString n_label)
{
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::white);
    this->setPen(borderpen);

    this->setRect(rect);
    this->text = new QGraphicsTextItem(n_label, this);
    this->text->setScale(1.5);
    this->text->setDefaultTextColor(Qt::white);
    this->text->setFont(QFont("terminal"));
    this->text->setPos(rect.left()+10, rect.top()+25);

    this->temptext = nullptr;
    this->temppos = 0;
}

void TextArea::setText(QString newtext){this->text->setHtml(newtext);}

void TextArea::clear(){this->text->setHtml("");}

QString TextArea::getText() {return this->text->toPlainText();}
