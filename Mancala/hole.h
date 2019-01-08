#ifndef HOLE_H
#define HOLE_H

#endif // HOLE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsObject>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCoreApplication>
#include <QSoundEffect>
#pragma once



//Объект класса Hole представляет из себя лунку игрового поля, в которой содержатся камни. Класс Hole унаследован от класса QGraphicsEllipseItem и пользуется реализованной в нём геометрией
//добавляя в неё игровую логику.

class Hole : public QObject, public QGraphicsEllipseItem{

    Q_OBJECT

private:
    QGraphicsTextItem* label;         // Текст, отображающий количество камней в лунке
    bool isGranary;                   // true если лунка является амбаром, false если это обычная лунка
    int index;                        // номер лунки на игровом поле
    int stones;                       // количество камней в лунке
    QSoundEffect onHoverSound;        // звуковой эффект, проигрывющийся при наведении курсора на лунку

//end of private

public:


    Hole(bool type, int _index, int _stones, QRectF _rect); //Стандартный конструктор с параметрами, в которых передаётся тип лунки, её номер, количество камней в ней и её геометрия

    Hole(Hole* toCopy);                                     //конструктор копирования, используется при создании копии поля для алгоритма альфа-бета отсечения

    int getIndex();                                         //возвращает индекс лунки

    bool checkGranary();                                    //проверяет, является ли лунка амбаром

    int getStones();                                        //возвращает количество камней в лунке

    void updateLabel();                                     //обновляет текстовое отображение количества камней в лунке на экране

    void addStone();                                        //добавляет один камень в лунку

    void setStones(int _stones);                            //задаёт количество камней в лунке, равное передаваемому параметру

    void removeStones();                                    //опустошает лунку

    void addStones(int stones);                             //добавляет в лунку переданное в параметре количество камней


//end of public

protected:

    void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;    //унаследованный от класса QGraphicsEllipseItem обработчик события попадания курсора на лунку

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;     //унаследованный от класса QGraphicsEllipseItem обработчик события покидания курсора из лунки

//end of protected

public slots:
    void mousePressEvent (QGraphicsSceneMouseEvent *event) override;    //унаследованный от класса QGraphicsEllipseItem обработчик события клика на лунку

signals:
    void sendIndex(int index);                                          //сигнал, посылаемый лункой при клике; Посылает в MainWindow индекс лунки, на которую был произведён клик
}; //end of Hole








