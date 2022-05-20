#include "mainwindow.h"
#include <QWidget>
#include "oglprimitive.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList distros = {"GL_LINES", "GL_LINE_LOOP", "GL_TRIANGLES", "GL_POLYGON"};

    QWidget* wgt = new QWidget();

    OGLPrimitive* primitive = new OGLPrimitive();
    QHBoxLayout* box1 = new QHBoxLayout();
    QVBoxLayout* boxVertical = new QVBoxLayout();
    boxVertical->setSpacing(20);
    boxVertical->addStretch(1);
    QComboBox* combo = new QComboBox();

    combo->addItems(distros);

    connect(combo, &QComboBox::currentTextChanged, primitive, &OGLPrimitive::setPrimitive);

    QLabel* label1 = new QLabel();
    label1->setText("Выбор примитива:");

    boxVertical->addWidget(label1);
    boxVertical->addWidget(combo);

    /*Прозрачность*/

    QLabel* label2 = new QLabel();
    label2->setText("Тест прозрачности:");
    boxVertical->addWidget(label2);

    QLabel* labelAlphaFunc = new QLabel();
    labelAlphaFunc->setText("GLenum func:");
    boxVertical->addWidget(labelAlphaFunc);

    QComboBox* alphaFunc = new QComboBox();
    QStringList distros2 = {"GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL", "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL", "GL_ALWAYS"};
    alphaFunc->addItems(distros2);

    connect(alphaFunc, &QComboBox::currentTextChanged, primitive, &OGLPrimitive::setAlphaFunc);

    boxVertical->addWidget(alphaFunc);

    QLabel* labelRef = new QLabel();
    labelRef->setText("Ref parameter:");
    boxVertical->addWidget(labelRef);

    QSlider* ref = new QSlider(Qt::Horizontal, 0);
    ref->setMinimum(0);
    ref->setMaximum(255);
    ref->setMaximumWidth(100);
    connect(ref, &QSlider::valueChanged, primitive, &OGLPrimitive::setRef);

    boxVertical->addWidget(ref);

    /*Отсечение*/

    QLabel* label3 = new QLabel();
    label3->setText("Тест отсечения:");
    boxVertical->addWidget(label3);

    QSlider* slideW = new QSlider(Qt::Horizontal, 0);
    QSlider* slideH = new QSlider(Qt::Horizontal, 0);

    slideW->setMaximumWidth(100);
    slideW->setMinimum(0);
    slideW->setMaximum(477);
    slideW->setValue(477);
    slideH->setMaximumWidth(100);
    slideH->setMinimum(0);
    slideH->setMaximum(622);
    slideH->setValue(622);

    QLabel* label4 = new QLabel();
    label4->setText("Ширина отсечения:");
    boxVertical->addWidget(label4);
    boxVertical->addWidget(slideW);

    QLabel* label5 = new QLabel();
    label5->setText("Высота отсечения:");
    boxVertical->addWidget(label5);
    boxVertical->addWidget(slideH);

    boxVertical->addStretch(1);

    connect(slideW, &QSlider::valueChanged, primitive, &OGLPrimitive::setSlideWidth);
    connect(slideH, &QSlider::valueChanged, primitive, &OGLPrimitive::setSlideHeight);

    /*Тест смешения цветов*/

    QLabel* label6 = new QLabel();
    label6->setText("Тест смешения:");
    boxVertical->addWidget(label6);

    QLabel* label7 = new QLabel();
    label7->setText("Sfactor:");
    boxVertical->addWidget(label7);

    QComboBox* sfactor = new QComboBox();
    QStringList distros3 = {"GL_ZERO", "GL_ONE", "GL_DST_COLOR", "GL_ONE_MINUS_DST_COLOR", "GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"};
    sfactor->addItems(distros3);
    connect(sfactor, &QComboBox::currentTextChanged, primitive, &OGLPrimitive::setSfactor);

    boxVertical->addWidget(sfactor);

    QLabel* label8 = new QLabel();
    label8->setText("Dfactor:");
    boxVertical->addWidget(label8);

    QComboBox* dfactor = new QComboBox();
    QStringList distros4 = {"GL_ZERO", "GL_ONE", "GL_SRC_COLOR", "GL_ONE_MINUS_SRC_COLOR", "GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA"};
    dfactor->addItems(distros4);
    connect(dfactor, &QComboBox::currentTextChanged, primitive, &OGLPrimitive::setDfactor);

    boxVertical->addWidget(dfactor);

    box1->addWidget(primitive);
    box1->addLayout(boxVertical);

    wgt->setLayout(box1);

    setCentralWidget(wgt);
    resize(640, 640);
}

MainWindow::~MainWindow()
{
}
