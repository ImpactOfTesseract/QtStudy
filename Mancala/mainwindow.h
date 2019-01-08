#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mancalaboard.h>
#include <textarea.h>
#include <restartbutton.h>
#include <radiobutton.h>

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSoundEffect>
#include "QTimer"
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QTime>
#include <QSoundEffect>
#include <QDir>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QGraphicsView* graphicsView;                      //Виджет для размещения объектов QGraphicsScene
    QGraphicsScene* scene;                            //Объект для размещения объектов QGraphicsItem
    QList<RadioButton*> difficulty_radio;             //Список кнопок RadioButton, регулирующих сложность

    MancalaBoard* board = nullptr;                    //объект игровой доски
    TextArea* textarea = nullptr;                     //область с анимированным текстом
    RestartButton* b_restart = nullptr;               //кнопка для начала новой игры

    QTimer* tmr;                                      //таймер для анимированного текста

    QSoundEffect textNarrator;                        //звуковой эффект для анимированного текста

//end of private

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;



//end of public
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;   //обработчик нажатия кнопки мыши

//end of protected
public slots:
    void getIndexFromSignal(int _index);                         //слот, получающий сигнал из Hole, в котором содержится индекс лунки, на которую кликнул игрок
    void updateText();                                           //слот, который обновляет текст в TextArea при истечении времени таймера
    void restart();                                              //слот, получающий сигнал из RestartButton; Начинает игру заново
    void radioButtonClicked(QString info_got);                   //слот, получающий сигнал из RadioButton; Позволяет менять сложность прямо во время игры
};

#endif // MAINWINDOW_H
