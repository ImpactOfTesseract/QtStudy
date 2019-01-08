#ifndef RESTARTBUTTON_H
#define RESTARTBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QSoundEffect>
#include <QCoreApplication>

//кнопка для перезапуска игры с обработчиками событий наведения курсора на кнопку и последующего клика
class RestartButton : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

private:
    QGraphicsTextItem* text;
    QSoundEffect restart_sound;

public:
    RestartButton(QRectF rect);

protected:

    void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public slots:
    void mousePressEvent (QGraphicsSceneMouseEvent *event) override;
signals:
    void restart();     //сигнал, посылаемый в MainWindow для перезапуска игры
};

#endif // RESTARTBUTTON_H
