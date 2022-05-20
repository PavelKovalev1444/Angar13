#include "oglprimitive.h"

OGLPrimitive::OGLPrimitive(QWidget* wgt) : QOpenGLWidget(wgt)
{
    primitiveType = "GL_LINES";
}

void OGLPrimitive::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OGLPrimitive::resizeGL(int width, int height){
    qDebug() << width << " " << height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 144, 144);
    glOrtho(0, 270, 270, 0, -1, 1);
}

void OGLPrimitive::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(255.0f, 0.0f, 0.0f);

    //qDebug() << this->size();

    if(primitiveType == "GL_LINES"){
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2d(30, 40);
        glVertex2d(30, 80);
        glVertex2d(70, 80);
        glVertex2d(140, 80);
        glEnd();
    }else if(primitiveType == "GL_LINE_LOOP"){
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glVertex2d(30, 40);
        glVertex2d(30, 80);
        glVertex2d(120, 160);
        glVertex2d(200, 160);
        glEnd();
    }else if(primitiveType == "GL_TRIANGLES"){
        glLineWidth(3);
        glBegin(GL_TRIANGLES);
        glVertex2d(30, 40);
        glVertex2d(30, 80);
        glVertex2d(120, 160);
        glVertex2d(200, 160);
        glEnd();
    }else if(primitiveType == "GL_POLYGON"){
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glVertex2d(30, 40);
        glVertex2d(60, 80);
        glVertex2d(130, 160);
        glVertex2d(200, 190);
        glEnd();
    }

}

void OGLPrimitive::setPrimitive(QString type){
    primitiveType = type;
    update();
}
