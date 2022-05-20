#ifndef FLAG_H
#define FLAG_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Flag: public QOpenGLWidget
{
protected:
    virtual void initializeGL();
    virtual void resizeGL(int, int );
    virtual void paintGL();
public:
    Flag();
    void init();
    QOpenGLShaderProgram* shaderProgram;
    float t;
public slots:
    void setTimer();
};

#endif // FLAG_H
