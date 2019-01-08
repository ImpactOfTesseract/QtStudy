#include <hole.h>

Hole::Hole(bool type, int _index, int _stones, QRectF _rect){
    QPen borderpen;

    //задаём основные параметры лунки
    this->isGranary = type;
    this->index = _index;
    this->stones = _stones;
    this->setRect(_rect);

    //задаём визуальные параметры лунки
    borderpen.setWidth(5); borderpen.setBrush(Qt::white);
    this->setPen(borderpen);

    //работа с текстом внутри лунки, который отображает количество содержащихся в ней камней
    this->label = new QGraphicsTextItem(QString::number(this->stones), this);
    this->label->setScale(1.3);
    this->label->setDefaultTextColor(Qt::white);
    this->label->setFont(QFont("terminal"));
    if(type == true){//если лунка - амбар
        this->label->setPos(_rect.left()+33, _rect.top()+50);
    }
    else
        this->label->setPos(_rect.left()+13, _rect.top()+35);

    if (!this->isGranary) //если лунка не является амбаром, то она принимает события наведения на неё мыши
        this->setAcceptHoverEvents(true);

    this->onHoverSound.setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/sounds/hover.wav"));
} //end of Hole(bool, int, int, QRectF)

Hole::Hole(Hole* toCopy){
    this->stones = toCopy->getStones();
    this->label = nullptr;
} //end of Hole(Hole*)

int Hole::getIndex()  {return this->index;}

bool Hole::checkGranary() {return this->isGranary;}

int Hole::getStones() {return this->stones;}

void Hole::updateLabel(){
    if (this->label != nullptr)
    this->label->setHtml(QString::number(this->stones));
}

void Hole::addStone() {this->stones++; updateLabel();}

void Hole::setStones(int _stones) {this->stones = _stones; updateLabel();}

void Hole::removeStones() {this->stones = 0; updateLabel();}

void Hole::addStones(int stones) {this->stones+=stones;}

void Hole::hoverEnterEvent (QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::yellow);
    this->setPen(borderpen);
    this->label->setDefaultTextColor(Qt::yellow);
    update (boundingRect());
    this->onHoverSound.play();


    QGraphicsItem::hoverEnterEvent(event);
}

void Hole::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPen borderpen;
    borderpen.setWidth(5); borderpen.setColor(Qt::white);
    this->setPen(borderpen);
    this->label->setDefaultTextColor(Qt::white);
    update (boundingRect());
    QGraphicsItem::hoverLeaveEvent(event);
}

void Hole::mousePressEvent (QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){

        QPen borderpen;
        borderpen.setWidth(5); borderpen.setColor(Qt::white);
        this->setPen(borderpen);
        this->label->setDefaultTextColor(Qt::white);
        update (boundingRect());

        emit sendIndex(this->getIndex());
    }
}
