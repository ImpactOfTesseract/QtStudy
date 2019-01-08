#include <mancalaboard.h>
#include <algorithm>

const int VERY_BIG = 9999999;
const int VERY_SMALL = -999999;

struct Node { //узел дерева, в котором хранятся возможные ходы при выполнении алгоритма альфа-бета отсечения
    QList<Node> children; //список детей для текущего хода
    MancalaBoard copyBoard;
    int this_index;

    int Evaluation(){
        if(this->copyBoard.checkPlayer())
            return -(this->copyBoard.getHole(6)->getStones() - this->copyBoard.getHole(13)->getStones());
        else return (this->copyBoard.getHole(6)->getStones() - this->copyBoard.getHole(13)->getStones());
    }
};


MancalaBoard::MancalaBoard(){ // конструктор доски без параметров. Генерирует лунки и заполняет их камнями.
    this->isGameOver = false;
    this->activePlayer = true;

    for(int i = 0; i<ROW_SIZE; i++){
        // Генерируем нижний ряд доски - ряд игрока-человека и его амбар
        if(i==6){ // Если текущая лунка седьмая, то генерируем её как амбар
            this->holes << new Hole(true, this->holes.size(), 0, QRectF(675, 60, 100, 150)); // задаём координаты и параметры
            break;
        }
        if(i==PLAYER_FIRST){ // если начало списка лунок, то индекс лунки равен нулю
            this->holes << new Hole(false, 0, 6, QRectF(200 + i*80, 150, 60, 90)); // задаём координаты и параметры
        }
        else
            this->holes << new Hole(false, this->holes.size(), 6, QRectF(200 + i*80, 150, 60, 90)); // задаём координаты и параметры
    }

    // Генерируем верхний ряд доски - ряд игрока-компьютера и его амбар
    for(int i = 0; i<ROW_SIZE; i++){
        if(i==6){ // если текущая лунка седьмая, то генерируем её как амбар
            this->holes << new Hole(true, this->holes.size(), 0, QRectF(90, 60, 100, 150)); // задаём координаты и параметры
            this->holes[this->holes.size()-1]->setAcceptedMouseButtons(nullptr);
            break;
        }
        else
            this->holes << new Hole(false, this->holes.size(), 6, QRectF(600 - i*80, 45, 60, 90)); // задаём координаты и параметры
            this->holes[this->holes.size()-1]->setAcceptHoverEvents(false);
            this->holes[this->holes.size()-1]->setAcceptedMouseButtons(nullptr);
    }
}

MancalaBoard::MancalaBoard(MancalaBoard *toCopy){
    for(int i = 0; i < 14; i++){
        this->holes << new Hole(toCopy->getHole(i));
    }

    this->activePlayer = toCopy->activePlayer;

}

Hole* MancalaBoard::getHole(int i) {return this->holes[i];}

bool MancalaBoard::checkPlayer() {return this->activePlayer;}

QString MancalaBoard::statusReport(){
    if(this->isGameOver)
        if(this->getHole(PLAYER_GRANARY)->getStones() > this->getHole(AI_GRANARY)->getStones())
            return QString("Player won with " + QString::number(this->getHole(PLAYER_GRANARY)->getStones()) + " stones against AI's " + QString::number(this->getHole(AI_GRANARY)->getStones()));
        else
            return QString("AI won with " + QString::number(this->getHole(AI_GRANARY)->getStones()) + " stones against Player's " + QString::number(this->getHole(PLAYER_GRANARY)->getStones()));
    else if(this->checkPlayer())
        return "It's player's turn!";
    else
        return "It's AI's turn! Right click to proceed";
}

void MancalaBoard::moveStones(int _index){


    int stones = this->getHole(_index)->getStones(); //записываем в переменную stones количество камней в лунке, из которой делается ход
    this->getHole(_index)->removeStones();           //опустошаем лунку из которой делается ход
    _index++;                                        //переходим к следующей лунке



    while(stones--){    //Пока не кончились камни, изъятые из лунки, из которой совершается ход
        if(this->activePlayer){ // если сейчас ход игрока
            if(_index == AI_GRANARY){ // если текущая лунка - амбар компьютерного оппонента
                _index = START_OF_FIELD; // установить текущий индекс в начало поля
                this->getHole(START_OF_FIELD)->addStone();  //положить камень в текущую лунку
                if(stones>0)  // если всё еще остались камни
                    _index = START_OF_FIELD+1;  //перейти к следующей лунке
            }
            else{ //иначе текущая лунка - любая другая лунка на поле
                this->getHole(_index)->addStone();  //положить камень в текущую лунку
                if(stones>0)   // если еще остались камни
                    _index++;  // переходим к следующей лунке
            }
        }
        else{ //иначе если ход компьютерного оппонента
            if(_index == PLAYER_GRANARY){  // если текущая лунка - амбар игрока
                _index = PLAYER_GRANARY + 1; //переходим к следующей лунке после амбара игрока
                this->getHole(PLAYER_GRANARY+1)->addStone(); // кладем в неё камень
                if(stones>0)   //если всё еще остались камни
                    _index=PLAYER_GRANARY+2; //переходим к следующей лунке
            }
            else if(_index == END_OF_FIELD){ // иначе если конец поля
                this->getHole(END_OF_FIELD)->addStone(); // кладем в текущую лунку камень
                if(stones>0) // если всё еще остались камни
                    _index = START_OF_FIELD; // переходим в начало поля
            }
            else { // иначе если любая другая лунка
                this->getHole(_index)->addStone(); // кладём камень в текущую лунку
                if(stones>0) // если всё еще остались камни
                    _index++; // переходим к следующей лунке
            }
        }
    }

    if (this->activePlayer && _index > PLAYER_GRANARY) // если сейчас ход игрока и он завершился на поле противника
        this->activePlayer = false; // то ход переходит противнику

    if(this->activePlayer //если сейчас ходит игрок
            && _index < PLAYER_GRANARY //и если ход завершился на поле игрока, но не в амбаре
            && this->getHole(_index)->getStones() == 1) //и последняя лунка была пустой перед тем, как мы в неё поместили камень
        this->initiateTheft(_index); // то воруем камни из противоположной лунки

    if (!this->activePlayer && _index < PLAYER_GRANARY) //если сейчас ход противника и он завершился на поле игрока
        this->activePlayer = true; // то ход переходит игроку

    if(!this->activePlayer //если сейчас ходит противник
            && _index>PLAYER_GRANARY // и ход завершился на его поле
            && this->getHole(_index)->getStones() == 1) // и последняя лунка была пустой перед тем, как мы в неё поместили камень
         this->initiateTheft(_index); // то воруем камни из противоположной лунки


    bool isPlayerEmpty = true;
    bool isAIEmpty = true;

    //проверки на пустоту лунок полей игроков
    for(int i = PLAYER_FIRST; i<PLAYER_GRANARY; i++){
        if (this->getHole(i)->getStones() > 0)
           isPlayerEmpty = false;
    }

    for(int i = AI_FIRST; i<AI_GRANARY; i++){
        if (this->getHole(i)->getStones() > 0)
           isAIEmpty = false;
    }

    //есди оба поля пусты - конец игры
    if(isPlayerEmpty && isAIEmpty){
        this->isGameOver = true;
    } //если пусто лишь одно из полей - наступает голод
    else if (isPlayerEmpty)
        this->Famine(PLAYER);
    else if (isAIEmpty)
        this->Famine(AI);

}

void MancalaBoard::initiateTheft(int _index){
    if(this->activePlayer){ //если сейчас ход игрока
        this->getHole(PLAYER_GRANARY)->setStones // то установить количество камней для амбара игрока в количестве, равном
                (this->getHole(PLAYER_GRANARY)->getStones()+ // сумме камней в амбаре игрока на текущий момент
                 this->getHole(AI_GRANARY-(_index+1))->getStones()); // с камнями из лунки, противоположной пустой
        this->getHole(AI_GRANARY-(_index+1))->removeStones();          //опустошить лунку, противоположную пустой
    }
    else{ //иначе если сейчас ход оппонента
        this->getHole(AI_GRANARY)->setStones // то установить количество камней для амбара компьютера
                (this->getHole(AI_GRANARY)->getStones()+ //равное сумме камней из амбара компьютера на текущий момент
                 this->getHole(PLAYER_GRANARY-(_index-PLAYER_GRANARY))->getStones()); //плюс камни из лунки, противолежащие пустой
        this->getHole(PLAYER_GRANARY-(_index-PLAYER_GRANARY))->removeStones();  //опустошить лунку, противоположную пустой
    }
}

void MancalaBoard::Famine(bool curPlayer){
    if (curPlayer){ //а иначе - камни переходят игроку
        for (int i = AI_FIRST; i<AI_GRANARY; i++){
            this->getHole(AI_GRANARY)->addStones(this->getHole(i)->getStones());
            this->getHole(i)->setStones(0);
        }
    }
    else{           //если голод настиг игрока - все камни на поле переходят компьютерному противнику
        for (int i = PLAYER_FIRST; i<PLAYER_GRANARY; i++){
            this->getHole(PLAYER_GRANARY)->addStones(this->getHole(i)->getStones());
            this->getHole(i)->setStones(0);
        }
    }
}

//алгоритм альфа-бета отсечения
int AlphaBetaPruning(Node node, int alpha, int beta, int depth){
    node.copyBoard.moveStones(node.this_index); //делаем копию доски

    if (depth == 0)                             //если мы достигли предельной глубины - возвращаем оценку текущего состояния
        return node.Evaluation();
        /***********************************************************/
    if(node.copyBoard.checkPlayer()){           //если ходит игрок минимизации
         int tempvalue = VERY_BIG;
         for(int i = 0; i < 6; i++){            //для каждого из возможного для него ходов генерируем детей, если в них больше нуля камней и рекурсивно вызываем эту же функцию
             if (node.copyBoard.getHole(i)->getStones() > 0){
             Node child; child.copyBoard = MancalaBoard(node.copyBoard); child.this_index = i;
             node.children << child;
             tempvalue = std::min(tempvalue, int(AlphaBetaPruning(node.children[node.children.size()-1], alpha, beta, depth - 1)));
             beta = std::min(beta, tempvalue);
             if (alpha > beta)     //альфа отсечение
                 break;
             }
         }
         return tempvalue;
     }
     else {                                     //если ходит игрок максимизации
         int tempvalue = VERY_SMALL;
         for(int i = 7; i < 13; i++){           //для каждого из возможного для него ходов генерируем детей, если в них больше нуля камней и рекурсивно вызываем эту же функцию
             if (node.copyBoard.getHole(i)->getStones() > 0){
             qInfo() << "oof";
             Node child; child.copyBoard = MancalaBoard(node.copyBoard); child.this_index = i;
             node.children << child;
             tempvalue = std::max(tempvalue, int(AlphaBetaPruning(node.children[node.children.size()-1], alpha, beta, depth - 1)));
             alpha = std::max(beta, tempvalue);
             if (alpha > beta)      //бета отсечение
                 break;
             }
         }
         return tempvalue;
     }
        /***********************************************************/
}

void MancalaBoard::MakeAIMove(){

    //для каждого из шести возможных ходов вызываем алгоритм альфа-бета отсечения, если количество камней в лунке больше нуля, после чего выбираем из них тот, у кого лучший показатель
    QList<int> results;
    int score = VERY_SMALL;
    int best_choice = 7;
    for(int i = 7; i < 13; i++){
        if(this->getHole(i)->getStones() > 0){
            int current_score = 0;
            Node current; current.copyBoard = new MancalaBoard(this); current.this_index = i;
            current_score = AlphaBetaPruning(current, VERY_SMALL, VERY_BIG, this->difficulty);
            if (current_score > score){
                best_choice = i;
                score = current_score;
            }
        }
    }

    this->moveStones(best_choice);
}

void MancalaBoard::setPlayer(bool playerToSet){this->activePlayer = playerToSet;}

void MancalaBoard::setDifficulty(int dif){this->difficulty = dif;}
