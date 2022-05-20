#ifndef FRACTAL_H
#define FRACTAL_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QDebug>

class Fractal: public QOpenGLWidget
{
protected:
    virtual void initializeGL();
    virtual void resizeGL(int, int );
    virtual void paintGL();
public:
    Fractal();
    void drawFractal();
    void drawRotation(QPoint&, QPoint&, GLfloat, bool);
    void drawQuarterCircle(QPoint&, QPoint&, GLfloat, bool);
    void replacement(int, QString&);
    QString axioma;
    int recursionDepp;
public slots:
    void setRecursionDepth(int);
};

#endif // FRACTAL_H
