#ifndef SPLINE_H
#define SPLINE_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>
#include <QMouseEvent>
#include <QVector>
#include <QInputDialog>

class Spline: public QOpenGLWidget
{
protected:
    virtual void initializeGL();
    virtual void resizeGL(int, int );
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* );
    virtual void mouseReleaseEvent(QMouseEvent* );
    virtual void mouseMoveEvent(QMouseEvent* );
    virtual void mouseDoubleClickEvent(QMouseEvent* );
public:
    Spline();
    void countSpline();
    int countT(int n, int k, int i);
    float div(float a, int b);
    float N(int i, int k, float x, QVector<int> t);
    QPointF curPoint;
    QVector<QPointF> curPointV;
    QVector<QPointF> allPoints;
    QVector<float> weights;
    bool isMove;
    int movePointIndex;
    int n;
    int k;
    QVector<int> tVector;
};

#endif // SPLINE_H
