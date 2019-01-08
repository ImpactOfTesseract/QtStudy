#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <mancalaboard.h>
#include <QSoundEffect>
#include <textarea.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    QGraphicsTextItem* status_strip;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private:
    Ui::MainWindow *ui;
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;

    MancalaBoard* board = nullptr;
    TextArea* textarea = nullptr;

    QTimer* tmr;
    int timer_timeouts;

    QSoundEffect textNarrator;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;


public slots:
    void playButtonClicked();
    void getIndexFromSignal(int _index);
    void updateText();
};

#endif // MAINWINDOW_H
