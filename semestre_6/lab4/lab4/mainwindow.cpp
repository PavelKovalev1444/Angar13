#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* wgt = new QWidget();
    Fractal* fractal = new Fractal();

    QSlider* slider = new QSlider(Qt::Horizontal, 0);
    slider->setMaximumWidth(100);
    slider->setMinimum(1);
    slider->setMaximum(5);
    slider->setValue(1);

    connect(slider, &QSlider::valueChanged, fractal, &Fractal::setRecursionDepth);

    QLabel* label = new QLabel();
    label->setText("Глубина рекурсии:");

    QVBoxLayout* vBox = new QVBoxLayout();

    vBox->addWidget(label);
    vBox->setSpacing(5);
    vBox->addWidget(slider);
    vBox->addStretch(1);

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(fractal);
    hBox->addLayout(vBox);

    wgt->setLayout(hBox);
    setCentralWidget(wgt);
    resize(640, 480);

}

MainWindow::~MainWindow()
{
}

