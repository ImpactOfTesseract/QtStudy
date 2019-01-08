#include "restartbutton.h"

RestartButton::RestartButton(QRectF rect)
{
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::white);
    this->setPen(borderpen);

    this->setRect(rect);

    this->text = new QGraphicsTextItem("New game", this);
    this->text->setScale(1.5);
    this->text->setDefaultTextColor(Qt::yellow);
    this->text->setFont(QFont("terminal"));
    this->text->setPos(rect.left()+10, rect.top()+25);

    this->setAcceptHoverEvents(true);

    this->restart_sound.setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/sounds/restart.wav"));
}

void RestartButton::hoverEnterEvent (QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::yellow);
    this->setPen(borderpen);
    this->text->setDefaultTextColor(Qt::yellow);
    update (boundingRect());


    QGraphicsItem::hoverEnterEvent(event);
}

void RestartButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::white);
    this->setPen(borderpen);
    this->text->setDefaultTextColor(Qt::yellow);
    update (boundingRect());
    QGraphicsItem::hoverLeaveEvent(event);
}

void RestartButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        this->restart_sound.play();
        emit restart();
    }
};
