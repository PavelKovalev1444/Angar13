#include "mainwindow.h"
#include <QApplication>
#include "field.h"
#include "player.h"

int main(int argc, char *argv[])
{
    field* f = f->getInstance();
    //f->createField(10, 10);
    player* p = p->getInstance();
    //f->enemyFill(*p);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
