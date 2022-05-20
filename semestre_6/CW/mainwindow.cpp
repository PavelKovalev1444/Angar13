#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* wgt = new QWidget();
    Figure* figure = new Figure();

    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->setSpacing(10);
    vBox->addStretch(1);

    QCheckBox* checkBox1 = new QCheckBox();
    checkBox1->setText(tr("Удалить невидимые грани/Прорисовать"));
    checkBox1->setChecked(true);
    connect(checkBox1, &QCheckBox::stateChanged, figure, &Figure::setEnableDepth);
    vBox->addWidget(checkBox1);

    QCheckBox* checkBox2 = new QCheckBox();
    checkBox2->setText(tr("Ортогональное/перспективное проецирование:"));
    checkBox2->setChecked(true);
    connect(checkBox2, &QCheckBox::stateChanged, figure, &Figure::setOrthoFrustum);
    vBox->addWidget(checkBox2);

    QLabel* t3 = new QLabel();
    t3->setText(tr("Перемещение фигуры по координатам:"));
    vBox->addWidget(t3);

    QHBoxLayout* figMoveBox = new QHBoxLayout();

    QLabel* xMove = new QLabel();
    xMove->setText("x:");
    QDoubleSpinBox* spinBoxMoveX = new QDoubleSpinBox();
    spinBoxMoveX->setMaximumWidth(50);
    spinBoxMoveX->setValue(0);
    spinBoxMoveX->setMinimum(-10);
    spinBoxMoveX->setMaximum(10);
    spinBoxMoveX->setSingleStep(0.1);
    connect(spinBoxMoveX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setXMove);

    QLabel* yMove = new QLabel();
    yMove->setText("y:");
    QDoubleSpinBox* spinBoxMoveY = new QDoubleSpinBox();
    spinBoxMoveY->setMaximumWidth(50);
    spinBoxMoveY->setValue(0);
    spinBoxMoveY->setMinimum(-10);
    spinBoxMoveY->setMaximum(10);
    spinBoxMoveY->setSingleStep(0.1);
    connect(spinBoxMoveY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setYMove);

    QLabel* zMove = new QLabel();
    zMove->setText("z:");
    QDoubleSpinBox* spinBoxMoveZ = new QDoubleSpinBox();
    spinBoxMoveZ->setMaximumWidth(50);
    spinBoxMoveZ->setValue(0);
    spinBoxMoveZ->setMinimum(-10);
    spinBoxMoveZ->setMaximum(10);
    spinBoxMoveZ->setSingleStep(0.1);
    connect(spinBoxMoveZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setZMove);

    figMoveBox->addWidget(xMove);
    figMoveBox->addWidget(spinBoxMoveX);
    figMoveBox->addWidget(yMove);
    figMoveBox->addWidget(spinBoxMoveY);
    figMoveBox->addWidget(zMove);
    figMoveBox->addWidget(spinBoxMoveZ);

    vBox->addLayout(figMoveBox);

    QLabel* t4 = new QLabel();
    t4->setText(tr("Поворот фигуры по координатам:"));
    vBox->addWidget(t4);

    QHBoxLayout* figRotBox = new QHBoxLayout();

    QLabel* xAplha = new QLabel();
    xAplha->setText("alpha x:");
    QDoubleSpinBox* spinBoxRotX = new QDoubleSpinBox();
    spinBoxRotX->setMaximumWidth(50);
    spinBoxRotX->setValue(0);
    spinBoxRotX->setMinimum(-180);
    spinBoxRotX->setMaximum(180);
    spinBoxRotX->setSingleStep(1);
    connect(spinBoxRotX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setXRot);

    QLabel* yAlpha = new QLabel();
    yAlpha->setText("alpha y:");
    QDoubleSpinBox* spinBoxRotY = new QDoubleSpinBox();
    spinBoxRotY->setMaximumWidth(50);
    spinBoxRotY->setValue(0);
    spinBoxRotY->setMinimum(-180);
    spinBoxRotY->setMaximum(180);
    spinBoxRotY->setSingleStep(1);
    connect(spinBoxRotY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setYRot);

    QLabel* zAlpha = new QLabel();
    zAlpha->setText("alpha z:");
    QDoubleSpinBox* spinBoxRotZ = new QDoubleSpinBox();
    spinBoxRotZ->setMaximumWidth(50);
    spinBoxRotZ->setValue(0);
    spinBoxRotZ->setMinimum(-180);
    spinBoxRotZ->setMaximum(180);
    spinBoxRotZ->setSingleStep(1);
    connect(spinBoxRotZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setZRot);

    figRotBox->addWidget(xAplha);
    figRotBox->addWidget(spinBoxRotX);
    figRotBox->addWidget(yAlpha);
    figRotBox->addWidget(spinBoxRotY);
    figRotBox->addWidget(zAlpha);
    figRotBox->addWidget(spinBoxRotZ);

    vBox->addLayout(figRotBox);

    QLabel* t5 = new QLabel();
    t5->setText(tr("Масштабирование фигуры по координатам:"));
    vBox->addWidget(t5);

    QHBoxLayout* figScaleBox = new QHBoxLayout();

    QLabel* xScale = new QLabel();
    xScale->setText("scale x:");
    QDoubleSpinBox* spinBoxScalX = new QDoubleSpinBox();
    spinBoxScalX->setMaximumWidth(50);
    spinBoxScalX->setValue(1.0);
    spinBoxScalX->setMinimum(0.1);
    spinBoxScalX->setMaximum(10);
    spinBoxScalX->setSingleStep(0.1);
    connect(spinBoxScalX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setXScal);

    QLabel* yScale = new QLabel();
    yScale->setText("scale y:");
    QDoubleSpinBox* spinBoxScalY = new QDoubleSpinBox();
    spinBoxScalY->setMaximumWidth(50);
    spinBoxScalY->setValue(1.0);
    spinBoxScalY->setMinimum(0.1);
    spinBoxScalY->setMaximum(10);
    spinBoxScalY->setSingleStep(0.1);
    connect(spinBoxScalY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setYScal);

    QLabel* zScale = new QLabel();
    zScale->setText("scale z:");
    QDoubleSpinBox* spinBoxScalZ = new QDoubleSpinBox();
    spinBoxScalZ->setMaximumWidth(50);
    spinBoxScalZ->setValue(1.0);
    spinBoxScalZ->setMinimum(0.1);
    spinBoxScalZ->setMaximum(10);
    spinBoxScalZ->setSingleStep(0.1);
    connect(spinBoxScalZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setZScal);

    figScaleBox->addWidget(xScale);
    figScaleBox->addWidget(spinBoxScalX);
    figScaleBox->addWidget(yScale);
    figScaleBox->addWidget(spinBoxScalY);
    figScaleBox->addWidget(zScale);
    figScaleBox->addWidget(spinBoxScalZ);

    vBox->addLayout(figScaleBox);

    QLabel* camPos = new QLabel();
    camPos->setText(tr("Координаты камеры:"));
    vBox->addWidget(camPos);

    QHBoxLayout* camPosBox = new QHBoxLayout();

    QLabel* xCam = new QLabel();
    xCam->setText("x:");
    QDoubleSpinBox* spinBoxCamX = new QDoubleSpinBox();
    spinBoxCamX->setMaximumWidth(50);
    spinBoxCamX->setValue(3.5);
    spinBoxCamX->setSingleStep(0.1);
    connect(spinBoxCamX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::camXChanged);

    QLabel* yCam = new QLabel();
    yCam->setText("y:");
    QDoubleSpinBox* spinBoxCamY = new QDoubleSpinBox();
    spinBoxCamY->setMaximumWidth(50);
    spinBoxCamY->setValue(3.5);
    spinBoxCamY->setSingleStep(0.1);
    connect(spinBoxCamY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::camYChanged);

    QLabel* zCam = new QLabel();
    zCam->setText("z:");
    QDoubleSpinBox* spinBoxCamZ = new QDoubleSpinBox();
    spinBoxCamZ->setMaximumWidth(50);
    spinBoxCamZ->setValue(3.5);
    spinBoxCamZ->setSingleStep(0.1);
    connect(spinBoxCamZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::camZChanged);

    camPosBox->addWidget(xCam);
    camPosBox->addWidget(spinBoxCamX);
    camPosBox->addWidget(yCam);
    camPosBox->addWidget(spinBoxCamY);
    camPosBox->addWidget(zCam);
    camPosBox->addWidget(spinBoxCamZ);

    vBox->addLayout(camPosBox);

    QLabel* t6 = new QLabel();
    t6->setText(tr("Задать мелкость разбиения:"));
    QSlider* slider6 = new QSlider(Qt::Horizontal);
    slider6->setMinimum(4);
    slider6->setMaximum(24);
    slider6->setFixedWidth(300);
    connect(slider6, &QSlider::valueChanged, figure, &Figure::setDivision);
    vBox->addWidget(t6);
    vBox->addWidget(slider6);

    QCheckBox* checkBox8 = new QCheckBox();
    checkBox8->setText(tr("Включить/убрать оси координат"));
    checkBox8->setChecked(false);
    connect(checkBox8, &QCheckBox::stateChanged, figure, &Figure::setEnableAxis);
    vBox->addWidget(checkBox8);

    QLabel* trr = new QLabel();
    trr->setText(tr("Малый радиус:"));
    QDoubleSpinBox* spinBox1 = new QDoubleSpinBox();
    spinBox1->setMaximumWidth(50);
    spinBox1->setValue(0.2);
    spinBox1->setSingleStep(0.1);
    vBox->addWidget(trr);
    vBox->addWidget(spinBox1);
    connect(spinBox1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setSmallRadius);

    QLabel* tR = new QLabel();
    tR->setText(tr("Большой радиус:"));
    QDoubleSpinBox* spinBox2 = new QDoubleSpinBox();
    spinBox2->setMaximumWidth(50);
    spinBox2->setValue(0.4);
    spinBox2->setSingleStep(0.1);
    vBox->addWidget(tR);
    vBox->addWidget(spinBox2);
    connect(spinBox2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), figure, &Figure::setBigRadius);

    QLabel* tLight = new QLabel();
    tLight->setText(tr("Тип света:"));
    QComboBox* lightList = new QComboBox();
    lightList->setMaximumWidth(180);
    lightList->addItem(tr("Света нет"));
    lightList->addItem(tr("Направленный свет"));
    lightList->addItem(tr("Точечный свет"));
    lightList->addItem(tr("Прожектор"));

    vBox->addWidget(tLight);
    vBox->addWidget(lightList);
    connect(lightList, &QComboBox::currentTextChanged, figure, &Figure::setLight);

    vBox->setSpacing(5);
    vBox->addStretch(1);

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(figure);
    hBox->addItem(vBox);

    wgt->setLayout(hBox);
    setCentralWidget(wgt);
    resize(900, 800);
}

MainWindow::~MainWindow()
{
}

