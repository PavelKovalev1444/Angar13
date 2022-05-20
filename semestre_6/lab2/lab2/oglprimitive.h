#ifndef OGLPRIMITIVE_H
#define OGLPRIMITIVE_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>

class OGLPrimitive: public QOpenGLWidget
{

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
public:
    QString primitiveType;
    QString alphaFunc;
    GLenum sfactor;
    GLenum dfactor;
    int slideW;
    int slideH;
    double ref;
    OGLPrimitive(QWidget* wgt = 0);
public slots:
    void setPrimitive(QString type);
    void setSlideWidth(int);
    void setSlideHeight(int);
    void setAlphaFunc(QString type);
    void setRef(int);
    void setSfactor(QString);
    void setDfactor(QString);
};

#endif // OGLPRIMITIVE_H
