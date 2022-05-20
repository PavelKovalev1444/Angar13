#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* wgt = new QWidget();
    Spline* spline = new Spline();

    QVBoxLayout* box = new QVBoxLayout();
    box->addWidget(spline);

    wgt->setLayout(box);
    setCentralWidget(wgt);
    resize(640, 480);
}

MainWindow::~MainWindow()
{
}

