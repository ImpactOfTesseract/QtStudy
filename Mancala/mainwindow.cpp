#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <hole.h>
#include <mancalaboard.h>

#include "QTimer"
#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSound>
#include <QRandomGenerator>
#include <QTime>
#include <QSoundEffect>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Mancala");

    this->tmr = new QTimer(this);

    this->textNarrator.setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/sounds/voice1.wav"));

    //задаём основные параметры сцены
    scene = new QGraphicsScene(QRectF(0,0,900,500));
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    connect(this->tmr, SIGNAL(timeout()), this, SLOT(updateText()));

    //инициализируем игровую доску
    if(this->board != nullptr)
        delete this->board;
    this->board = new MancalaBoard();
    this->board->setDifficulty(1);

    //инициализируем область с текстом
    this->textarea = new TextArea(QRectF(2, 0, 895, 100), this->board->statusReport());
    this->textarea->setPos(0,300);

    //инициализируем кнопку перезапуска игры
    this->b_restart = new RestartButton(QRectF(0, 0, 175, 95));
    this->b_restart->setPos(0,400);
    connect(this->b_restart, SIGNAL(restart()), this, SLOT(restart()));

    //инициализируем радио-кнопки для смены сложности
    this->difficulty_radio << new RadioButton("Easy", QRectF(0, 0, 15, 15));
    this->difficulty_radio[0]->setPos(200, 420);
    this->difficulty_radio[0]->setBrush(QBrush(Qt::white));
    connect(this->difficulty_radio[0], SIGNAL(emitRadioSignal(QString)), this, SLOT(radioButtonClicked(QString)));

    this->difficulty_radio << new RadioButton("Hard", QRectF(0, 0, 15, 15));
    this->difficulty_radio[1]->setPos(200, 470);
    connect(this->difficulty_radio[1], SIGNAL(emitRadioSignal(QString)), this, SLOT(radioButtonClicked(QString)));

    //добавляем сгенерированные объекты на сцену
    scene->clear();
    scene->addItem(this->difficulty_radio[0]);
    scene->addItem(this->difficulty_radio[1]);
    scene->addItem(this->textarea);
    scene->addItem(this->b_restart);

    graphicsView = new QGraphicsView(scene, ui->centralWidget);

    //добавляем лунки на игровую доску
    for(int i = 0; i<14; i++){
        scene->addItem(board->getHole(i));
        QObject::connect(board->getHole(i), SIGNAL(sendIndex(int)), this, SLOT(getIndexFromSignal(int)));
    }

    //отображаем сцену
    graphicsView->show();
} //End of MainWindow

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getIndexFromSignal(int _index){

    this->board->moveStones(_index);

    //если ход противника - забрать у игрока возможность наводиться на свои лунки
    if(this->board->checkPlayer()){
        for(int i = 0; i < 6; i++)
        {
            this->board->getHole(i)->setAcceptHoverEvents(true);
            this->board->getHole(i)->setAcceptedMouseButtons(Qt::LeftButton);
        }
    }
    else {
        for(int i = 0; i < 6; i++)
        {
            this->board->getHole(i)->setAcceptHoverEvents(false);
            this->board->getHole(i)->setAcceptedMouseButtons(nullptr);
        }
    }

    //обновить текст
    this->textarea->clear();

    this->tmr->setInterval(30);
    this->tmr->start();

    this->textNarrator.stop();

    graphicsView->show();
}

void MainWindow::updateText(){

    //как только был выведен весь текст - анимация останавливается
    if(this->textarea->getText().size() == this->board->statusReport().size()){
        this->tmr->stop();
    }

    //при каждом срабатывании таймера выводится один символ
    this->textarea->setText(this->textarea->getText() + this->board->statusReport().mid(this->textarea->getText().size(), 1));

    this->textNarrator.play();

    graphicsView->show();

}

//ход противника после нажатия правой кнопки мыши
void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton && !this->board->checkPlayer()){

        this->board->MakeAIMove();

        //если ход перешел игроку - разрешаем ему нажимать на свои кнопки
        if(this->board->checkPlayer()){
            for(int i = 0; i < 6; i++)
            {
                this->board->getHole(i)->setAcceptHoverEvents(true);
                this->board->getHole(i)->setAcceptedMouseButtons(Qt::LeftButton);
            }
        }
        else {
            for(int i = 0; i < 6; i++)
            {
                this->board->getHole(i)->setAcceptHoverEvents(false);
                this->board->getHole(i)->setAcceptedMouseButtons(nullptr);
            }
        }

        this->textarea->clear();

        this->tmr->setInterval(30);
        this->tmr->start();

        this->textNarrator.stop();

        graphicsView->show();
    }
}

void MainWindow::restart() {
    this->board->setPlayer(PLAYER);

    this->board->getHole(6)->removeStones();
    this->board->getHole(13)->removeStones();

    for(int i = 0; i < 6; i++){
        this->board->getHole(i)->setStones(6);
    }

    for(int i = 7; i < 13; i++){
        this->board->getHole(i)->setStones(6);
    }

    if(this->board->checkPlayer()){
        for(int i = 0; i < 6; i++)
        {
            this->board->getHole(i)->setAcceptHoverEvents(true);
            this->board->getHole(i)->setAcceptedMouseButtons(Qt::LeftButton);
        }
    }
    else {
        for(int i = 0; i < 6; i++)
        {
            this->board->getHole(i)->setAcceptHoverEvents(false);
            this->board->getHole(i)->setAcceptedMouseButtons(nullptr);
        }
    }

    this->textarea->clear();

    this->tmr->setInterval(30);
    this->tmr->start();

    this->textNarrator.stop();

    graphicsView->show();
}

void MainWindow::radioButtonClicked(QString info_got){

    if (info_got == "Easy"){
        this->difficulty_radio[0]->setBrush(QBrush(Qt::white));
        this->difficulty_radio[1]->setBrush(QBrush(Qt::black));
        this->board->setDifficulty(1);
    }
    else {
        this->difficulty_radio[0]->setBrush(QBrush(Qt::black));
        this->difficulty_radio[1]->setBrush(QBrush(Qt::white));
        this->board->setDifficulty(3);
    }

    graphicsView->show();
}





