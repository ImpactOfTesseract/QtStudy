#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCoreApplication>

//Радио-кнопка для переключения сложности с обработчиками событий наведения на неё курсора и клика
class RadioButton : public QObject, public QGraphicsEllipseItem
{

    Q_OBJECT

private:
    QGraphicsTextItem* label;
    QString info;                               //информация, содержащаяся в кнопке

public:
    RadioButton(QString n_info, QRectF _rect);

    QString getInfo();

protected:

    void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


public slots:
    void mousePressEvent (QGraphicsSceneMouseEvent *event) override;

signals:
    void emitRadioSignal(QString buttonInfo);   //передаёт информацию из кнопки в MainWindow
};

#endif // RADIOBUTTON_H
