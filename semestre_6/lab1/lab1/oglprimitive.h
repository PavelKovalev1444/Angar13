#ifndef OGLPRIMITIVE_H
#define OGLPRIMITIVE_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>

class OGLPrimitive: public QOpenGLWidget
{

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
public:
    QString primitiveType;
    OGLPrimitive(QWidget* wgt = 0);
public slots:
    void setPrimitive(QString type);
};

#endif // OGLPRIMITIVE_H
