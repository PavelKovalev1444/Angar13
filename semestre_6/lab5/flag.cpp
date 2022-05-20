#include "flag.h"

Flag::Flag()
{
    shaderProgram = new QOpenGLShaderProgram();
    t = 0.0;
}

void Flag::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
    init();
}

void Flag::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho(-2, 2, -2, 2, -1, 1);
}

void Flag::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->setUniformValue("coeff", t);

    glBegin(GL_POLYGON);
        glVertex2d(-0.75f, -0.1f);
        glVertex2d(-0.75f, 0.1f);
        glVertex2d(0.75f, 0.1f);
        glVertex2d(0.75f, -0.1f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(-0.1f, -0.75f);
        glVertex2d(-0.1f, 0.75f);
        glVertex2d(0.1f, 0.75f);
        glVertex2d(0.1f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(-0.75f, 0.15f);
        glVertex2d(-0.75f, 0.4f);
        glVertex2d(-0.35f, 0.15f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(-0.6f, 0.75f);
        glVertex2d(-0.15f, 0.75f);
        glVertex2d(-0.15f, 0.45f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(0.15f, 0.75f);
        glVertex2d(0.6f, 0.75f);
        glVertex2d(0.15f, 0.45f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(0.75f, 0.15f);
        glVertex2d(0.75f, 0.4f);
        glVertex2d(0.35f, 0.15f);
    glEnd();

    //bottom triangles

    glBegin(GL_TRIANGLES);
        glVertex2d(-0.75f, -0.15f);
        glVertex2d(-0.75f, -0.4f);
        glVertex2d(-0.35f, -0.15f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(-0.6f, -0.75f);
        glVertex2d(-0.15f, -0.75f);
        glVertex2d(-0.15f, -0.45f);
    glEnd();

    glBegin(GL_TRIANGLES);    
        glVertex2d(0.15f, -0.75f);
        glVertex2d(0.6f, -0.75f);
        glVertex2d(0.15f, -0.45f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2d(0.75f, -0.15f);
        glVertex2d(0.75f, -0.4f);
        glVertex2d(0.35f, -0.15f);
    glEnd();
}

void Flag::init(){
    std::string vertexCode;
    std::string fragmentCode;

    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/pavel/leti_laby/ComputerGraphics/lab5/lab5/flagVertShader.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/pavel/leti_laby/ComputerGraphics/lab5/lab5/flagFragShader.frag");

    shaderProgram->link();

    shaderProgram->bind();
}

void Flag::setTimer(){
    t += 0.5;
    update();
}
