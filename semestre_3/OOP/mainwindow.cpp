#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    wdgt = new QWidget(this);//основной виджет

    btn1 = new QPushButton("New game", wdgt);
    btn2 = new QPushButton("Load game", wdgt);
    btn3 = new QPushButton("Exit game", wdgt);
    box = new QHBoxLayout(wdgt);
    area = new QScrollArea();
    qDebug() << "line13";
    interface = new QVBoxLayout(wdgt);
    qDebug() << "line15";
    lbl = new QLabel(area);


    lbl->setMouseTracking(true);
    lbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    box->addItem(interface);
    interface->addWidget(btn1);
    interface->addWidget(btn2);
    interface->addWidget(btn3);

    box->addWidget(area);
    setMinimumSize(750, 660);
    setCentralWidget(wdgt);

    imageZone = new QImage(640, 640, QImage::Format_RGB888);

    int  i = 0, j = 0;
    while(i < 640){
        while(j < 640){
            imageZone->setPixel(i,j,qRgb(50,170,50));
            j++;
        }
        j = 0;
        i++;
    }
    restoreWindow();
    connect(btn1, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(loadGame()));
    connect(btn3, SIGNAL(clicked()), this, SLOT(exitGame()));
}

void MainWindow::restoreWindow(){
    lbl->resize(640, 640);
    lbl->setPixmap(QPixmap::fromImage(*imageZone));
}

void MainWindow::startGame(){
    field::getInstance()->createField(10, 10);
    player::getInstance()->fieldPtr = field::getInstance();
    field::getInstance()->enemyFill(*player::getInstance());
    drawField();
    restoreWindow();
}

void MainWindow::loadGame(){
    std::ifstream savePlayerFile("playerSave.txt", std::ios_base::in);
    std::ifstream saveFieldFile("fieldSave.txt", std::ios_base::in);
    try{
        if(!savePlayerFile.is_open())
            throw -1;
        if(!saveFieldFile.is_open())
            throw -1;
        std::vector<int> plVec;
        int numb;
        while(savePlayerFile >> numb){
            plVec.push_back(numb);
        }
        if(plVec.size() != 4){
            throw -1;
        }
        player::getInstance()->restoreFromFile(plVec[0], plVec[1],plVec[2],plVec[3]);
        int h = 0, w = 0;
        saveFieldFile >> h;
        saveFieldFile >> w;
        char** area = new char*[h];
        for(int m = 0; m < h; m++){
            area[m] = new char[w];
        }
        char tmp;
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                saveFieldFile >> tmp;
                area[i][j] = tmp;
            }
        }
        //player p(plVec[0], plVec[1],plVec[2],plVec[3]);
        field::getInstance()->restoreFromFile(h, w, area, *player::getInstance());
        field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].setIsPlayer(true);
        field::getInstance()->enemyFill(*player::getInstance());
        savePlayerFile.close();
        saveFieldFile.close();
    }
    catch(int a){
       std::cout << "File with save was damaged!. Stopping program.";
       exit(1);
    }
    drawField();
    restoreWindow();
}

void MainWindow::exitGame(){
    this->close();
}

void MainWindow::drawCell(int x, int y, QImage img){
    int i = 0, j = 0;
    while(i < 64){
        while(j < 64){
            timeColour = img.pixel(i, j);
            imageZone->setPixel(x*64 + i, y*64 + j, timeColour);
            j++;
        }
        j = 0;
        i++;
    }
}

void MainWindow::drawField(){
    int i = 0, j = 0;
    while(i < field::getInstance()->getHeight()){
        while(j < field::getInstance()->getWidth()){
            if(field::getInstance()->getPointer()[i][j].getIsPlayer()){
                timeImage.load(QDir::currentPath() + "/player.jpg");
                drawCell(j, i, timeImage);
            }else if(!field::getInstance()->getPointer()[i][j].get_passability()){
                timeImage.load(QDir::currentPath() + "/wall.jpg");
                drawCell(j, i, timeImage);
            }else if(field::getInstance()->getPointer()[i][j].getIsEnemy()){
                timeImage.load(QDir::currentPath() + "/enemy.jpg");
                drawCell(j, i, timeImage);
            }else if(field::getInstance()->getPointer()[i][j].getElemPointer() && !field::getInstance()->getPointer()[i][j].getIsUsed()){
                if(field::getInstance()->getPointer()[i][j].getElemPointer()->isElem() == 1){
                    timeImage.load(QDir::currentPath() + "/heal.jpg");
                    drawCell(j, i, timeImage);
                }else if(field::getInstance()->getPointer()[i][j].getElemPointer()->isElem() == 2){
                    timeImage.load(QDir::currentPath() + "/gold.jpg");
                    drawCell(j, i, timeImage);
                }else if(field::getInstance()->getPointer()[i][j].getElemPointer()->isElem() == 3){
                    timeImage.load(QDir::currentPath() + "/bomb.jpg");
                    drawCell(j, i, timeImage);
                }
            }else if(field::getInstance()->getPointer()[i][j].get_passability()){
                timeImage.load(QDir::currentPath() + "/sand.jpg");
                drawCell(j, i, timeImage);
            }
            j++;
        }
        j = 0;
        i++;
   }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int key=event->key();
    switch(key){
        case Qt::Key_W:
            player::getInstance()->goUp();
            if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()){
                if(!field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getIsUsed()){
                    if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 1){
                        *player::getInstance() += 25;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 2){
                        *player::getInstance() += 1;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 3){
                        *player::getInstance() += -25;
                    }
                }
            }
            break;
        case Qt::Key_A:
            player::getInstance()->goLeft();
            if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()){
                if(!field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getIsUsed()){
                    if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 1){
                        *player::getInstance() += 25;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 2){
                        *player::getInstance() += 1;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 3){
                        *player::getInstance() += -25;
                    }
                }
            }
            break;
        case Qt::Key_S:
            player::getInstance()->goDown();
            if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()){
                if(!field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getIsUsed()){
                    if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 1){
                        *player::getInstance() += 25;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 2){
                        *player::getInstance() += 1;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 3){
                        *player::getInstance() += -25;
                    }
                }
            }
            break;
        case Qt::Key_D:
            player::getInstance()->goRight();
            if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()){
                if(!field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getIsUsed()){
                    if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 1){
                        *player::getInstance() += 25;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 2){
                        *player::getInstance() += 1;
                    }else if(field::getInstance()->getPointer()[player::getInstance()->getY()][player::getInstance()->getX()].getElemPointer()->isElem() == 3){
                        *player::getInstance() += -25;
                    }
                }
            }
            break;
        case Qt::Key_F:
            if(saveAndLoad){
                delete saveAndLoad;
            }
            saveAndLoad = new careTaker(field::getInstance(), player::getInstance());
            saveAndLoad->backup();
            break;
        case Qt::Key_L:
            saveAndLoad->undo();
            break;
    }
    for(int i = 0; i < field::getInstance()->getHeight(); i++){
        for(int j = 0; j < field::getInstance()->getWidth(); j++){
            if(field::getInstance()->getPointer()[i][j].getEnemyPointer()){
                field::getInstance()->getPointer()[i][j].getEnemyPointer()->doSomething();
            }
        }
    }
    qDebug() << "Hp = " << player::getInstance()->health;
    qDebug() << "Coins = " <<  player::getInstance()->goldCounter << "\n";
    log.update(player::getInstance());
    if(player::getInstance()->health == 0){
        delete saveAndLoad;
        this->close();
    }
    if(player::getInstance()->x == field::getInstance()->getWidth() - 1  && player::getInstance()->y == field::getInstance()->getHeight() - 1){
        delete saveAndLoad;
        this->close();
    }

    drawField();
    restoreWindow();
}

MainWindow::~MainWindow()
{

}
