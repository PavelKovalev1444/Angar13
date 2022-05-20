#ifndef FIGURE_H
#define FIGURE_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QtMath>
#include <QDepthTest>

class Figure: public QOpenGLWidget
{
protected:
    virtual void initializeGL();
    virtual void resizeGL(int, int );
    virtual void paintGL();
public:
    Figure();
    void init();
    void drawCircle(float, float, float, float, QVector<GLfloat>&);
    void drawConeCircle(float, float, QVector<GLfloat>& ,QVector<GLfloat>& );
    void drawAxis();
    void drawConeLines();
    QOpenGLShaderProgram* shaderProgram;
    QMatrix4x4 rotationMatrix;
    QMatrix4x4 scaleMatrix;
    float r;
    float R;
    float x0;
    float y0;
    float z;
    float camX;
    float camY;
    float camZ;
    float moveX;
    float moveY;
    float moveZ;
    float xAlpha;
    float yAlpha;
    float zAlpha;
    float xScale;
    float yScale;
    float zScale;
    int frequency;
    bool depth;
    bool hasAxis;
    bool isOrtho;
public slots:
    void setEnableAxis(bool );
    void setDivision(int );
    void setSmallRadius(float );
    void setBigRadius(double );
    void setEnableDepth(bool );
    void camXChanged(float );
    void camYChanged(float );
    void camZChanged(float );
    void setOrthoFrustum(bool );
    void setXMove(float );
    void setYMove(float );
    void setZMove(float );
    void setXRot(float );
    void setYRot(float );
    void setZRot(float );
    void setXScal(float );
    void setYScal(float );
    void setZScal(float );
};

#endif // FIGURE_H
