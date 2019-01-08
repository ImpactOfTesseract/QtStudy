#include "radiobutton.h"

RadioButton::RadioButton(QString n_info, QRectF _rect)
{
    this->info = n_info;

    this->setRect(_rect);

    QPen borderpen;
    borderpen.setWidth(2); borderpen.setBrush(Qt::white);
    this->setPen(borderpen);

    this->label = new QGraphicsTextItem(n_info, this);
    this->label->setScale(1.3);
    this->label->setDefaultTextColor(Qt::white);
    this->label->setFont(QFont("terminal"));
    this->label->setPos(_rect.right()+10, _rect.top()-6);
    this->setAcceptHoverEvents(true);
}

void RadioButton::hoverEnterEvent (QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(2); borderpen.setColor(Qt::yellow);
    this->setPen(borderpen);
    this->label->setDefaultTextColor(Qt::yellow);
    update (boundingRect());
    QGraphicsItem::hoverEnterEvent(event);
}

void RadioButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(2); borderpen.setColor(Qt::white);
    this->setPen(borderpen);
    this->label->setDefaultTextColor(Qt::white);
    update (boundingRect());
    QGraphicsItem::hoverLeaveEvent(event);
}

QString RadioButton::getInfo(){return this->info;}

void RadioButton::mousePressEvent (QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit emitRadioSignal(this->getInfo());
    }
}
