#ifndef MANCALABOARD_H
#define MANCALABOARD_H

#endif // MANCALABOARD_H

#include <hole.h>

#include <QRandomGenerator>
#include <QDateTime>

#pragma once


const int  PLAYER_GRANARY = 6;     //индекс лунки игрока
const int  AI_GRANARY = 13;        //индекс лунки игрока-компьютера
const int PLAYER_FIRST = 0;        //индекс первой лунки игрока
const int AI_FIRST = 7;            //индекс первой лунки игрока-компьютера

const int ROW_SIZE = 7;            //размер игрового поля игрока вместе с его амбаром
const int START_OF_FIELD = 0;      //индекс начала поля
const int END_OF_FIELD = 13;       //индекс начала поля

const bool PLAYER = true;
const bool AI = false;



class MancalaBoard{

private:

    // список лунок доски; лунки с индексами 0-7 принадлежат игроку-человеку и формируют нижний ряд, где лунка с индеском 6 - его амбар;
    QList<Hole*> holes; //соответственно, лунки с индексами 8-15 принадлежат игроку-компьютеру, где лунка с индексом 13 - его амбар

    bool activePlayer; // текущий игрок, которому принадлежит ход. False для компьютера, true для человека.
    bool isGameOver;   // состояние, определяющее завершилась ли игра
    int difficulty;    // текущая сложность, используется как глубина поиска в ширину в алгоритме альфа-бета отсечения

//end of private

public:

    MancalaBoard();

    MancalaBoard(MancalaBoard *toCopy);

    void setDifficulty(int dif);                //устанавливает сложность, равную переданному параметру

    Hole* getHole(int i);                       // возвращает указатель на лунку с индексом i

    bool checkPlayer();                         //возвращает true если сейчас ходит игрок, иначе возвращает false

    QString statusReport();                     //сообщает о том, чей сейчас ход в виде строки

    void moveStones(int _index);                // Камни берутся из лунки под номером _index и распределяются против часовой стрелки, минуя амбар оппонента

    void initiateTheft(int _index);             //воруем камни из лунки, противоположной переданной в метод. Сворованные камни помещаются в амбар игрока, которому принадлежит ход

    void Famine(bool curPlayer);                //вызывается когда у одного из игроков кончились камни на его поле. Берёт оставшиеся камни на поле и начисляет их в амбар другого игрока

    void setPlayer(bool playerToSet);           //устанавливает игрока, которому принадлежит ход

    void MakeAIMove();                          //метод хода компьютерного оппонента

//end of public
};
