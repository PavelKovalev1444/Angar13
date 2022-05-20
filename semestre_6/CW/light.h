#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

struct Light{
    QVector4D lightPos;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

#endif // LIGHT_H
