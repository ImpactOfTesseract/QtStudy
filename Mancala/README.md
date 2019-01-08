Mancala!

What is Mancala? if you want an in-depth detailed description, please visit this Wikipedia page: https://en.wikipedia.org/wiki/Mancala

Mancala is a simple, yet fun game. Both players control a field, which consists of 6 holes and one big hole, called The Granary. Each player starts with 6 stones in each on his normal holes and an empty granary. Your goal is to have more stones in your granary than your oponent has in his.

![screenshot1](https://github.com/ImpactOfTesseract/QtStudy/blob/master/Mancala/Screenshots/1.png)

To make a move simply choose a hole that has stones in it. When you make a move, all stones are taken from the chosen hole (leaving it empty) and then redistributed through the field in counter-clockwise fashion, leaving one stone in each hole.

![screenshot1](https://github.com/ImpactOfTesseract/QtStudy/blob/master/Mancala/Screenshots/2.png)

Player made a move from his first hole, which is now empty.

If turn ends on your side of the field, you gain one more turn! Feel free to abuse that rule to maximize the gain out of your turn.

If turn ends in the hole that is empty, player who made the turn STEALS all the stones from the opposite hole and puts them in his granary.

![screenshot1](https://github.com/ImpactOfTesseract/QtStudy/blob/master/Mancala/Screenshots/3.png

Player is about to make a move from the highlighted hole. Now, pay close attention...

![screenshot1](https://github.com/ImpactOfTesseract/QtStudy/blob/master/Mancala/Screenshots/4.png

Player stole all the stones from the opposite hole!

There is one last game rule\situation to talk about: Famine. If one of the players has no valid turns (all of his holes are empty) then his opponent takes all of the remaining stones on the board and puts them in their Granary.

With this knowledge you should be able to take on the AI and claim the victory!

Actually, let's talk about the AI. AI works through the alpha-beta pruning algorithm, which is a search algorithm that seeks to decrease the number of nodes evaluated by minimax algorithm (https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning). There are "Easy" and "Hard" difficulty settings that determine how deep does alpha-beta algorithm go. Despite the fact that this is an optimisation algorithm it still may take a lot of time to compute an optimal move, so chosen depths values are not exactly high, but they should be sufficient for pleasant, yet challenging experience.

Project structure:
main.cpp contains an entry into the program;
hole.cpp and hole.h contain an implementation of a single hole on the playfield;
mainwindow.cpp and mainwindow.h contain the layout of the ui;
mancalaboard.cpp and mancalaboard.h contain the game logic;
radiobutton.cpp and radiobutton.h define radiobuttons, that allow you to change difficulty on the fly;
restartbutton.cpp and restartbutton.h define the "New Game" button, that allows you to restart the game;
textarea.cpp and textarea.h define the text area, that shows the current status of the game.

folder "sounds" contains sounds for the game.
