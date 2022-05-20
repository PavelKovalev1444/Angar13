#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include "oglprimitive.h"
#include <QVBoxLayout>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList distros = {"GL_LINES", "GL_LINE_LOOP", "GL_TRIANGLES", "GL_POLYGON"};

    QWidget* wgt = new QWidget();

    OGLPrimitive* primitive = new OGLPrimitive();
    QVBoxLayout* box = new QVBoxLayout();
    QComboBox* combo = new QComboBox();

    combo->addItems(distros);

    connect(combo, &QComboBox::currentTextChanged, primitive, &OGLPrimitive::setPrimitive);

    box->addWidget(combo);
    box->addWidget(primitive);

    wgt->setLayout(box);

    setCentralWidget(wgt);
    resize(640, 640);
}

MainWindow::~MainWindow()
{
}

