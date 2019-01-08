#include "mainwindow.h"
#include <QApplication>
#include <hole.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QAudioDeviceInfo>
#include <QFileInfo>
#include <Windows.h>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    // Bug workaround. See https://bugreports.qt-project.org/browse/QTBUG-28766
    wchar_t dirpath[260];
    GetModuleFileName(nullptr, dirpath, 260);
    QFileInfo dir(QString::fromWCharArray(dirpath));
    QApplication::addLibraryPath(dir.absolutePath());

    MainWindow w;
    w.show();

    return a.exec();
}
