#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libs.h"
#include "field.h"
#include "player.h"
#include "logger.h"
#include "careTaker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QWidget* wdgt;
    QLabel* lbl;
    QBoxLayout* box;
    QBoxLayout* interface;
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QScrollArea* area;
    QImage* imageZone;
    logger log;
    QRgb timeColour;
    QImage timeImage;
    MainWindow(QWidget *parent = 0);
    careTaker* saveAndLoad = nullptr;
    void restoreWindow();
    void drawCell(int x, int y, QImage img);
    void drawField();
    ~MainWindow();
protected:
   virtual void keyPressEvent(QKeyEvent *event);
private slots:
    void startGame();
    void loadGame();
    void exitGame();
signals:

};

#endif // MAINWINDOW_H
