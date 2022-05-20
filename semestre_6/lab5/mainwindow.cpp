#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* wgt = new QWidget();
    Flag* flagWidget = new Flag();

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(flagWidget);

    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, flagWidget, &Flag::setTimer);
    timer->start(100);

    wgt->setLayout(hBox);
    setCentralWidget(wgt);
    resize(640, 480);
}

MainWindow::~MainWindow()
{
}

