#include "fractal.h"

Fractal::Fractal()
{
    recursionDepp = 1;
    axioma = "BABA";
}

void Fractal::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
}

void Fractal::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Fractal::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(255.0f, 0.0f, 255.0f);
    glBegin(GL_LINE_LOOP);
        drawFractal();
    glEnd();
}

void Fractal::drawFractal(){
    QPoint point = QPoint(((int) qPow(2.0, 1.0 + recursionDepp)) - 1, 0);
    QPoint direction = QPoint(0, 1);
    GLfloat compressionRatio = 0.9 / (qPow(2.0, 1.0 + recursionDepp) - 1);
    for(auto symbol : axioma){
        switch(symbol.toLatin1()){
            case 'A':
            case 'B':
                drawRotation(point, direction, compressionRatio, true);
                break;
            case 'C':
            case 'D':
                drawRotation(point, direction, compressionRatio, false);
                break;
            case 'E':
            case 'Z':
                point.rx() += direction.x();
                point.ry() += direction.y();
                glVertex2f(compressionRatio * point.x(), compressionRatio * point.y());
                point.rx() += direction.x();
                point.ry() += direction.y();
                glVertex2f(compressionRatio * point.x(), compressionRatio * point.y());
                break;
        }
    }
}

void Fractal::drawRotation(QPoint &start, QPoint &direction, GLfloat compressionRatio, bool isLeft) {
    QPoint end = QPoint(start.x() + direction.x(), start.y() + direction.y());
    QPoint endDirection;
    if (isLeft) {
        endDirection.rx() = -direction.y();
        endDirection.ry() = direction.x();
    } else {
        endDirection.rx() = direction.y();
        endDirection.ry() = -direction.x();
    }
    end.rx() += endDirection.x();
    end.ry() += endDirection.y();

    QPoint center = endDirection.x() == 0 ? QPoint(start.x(), end.y()) : QPoint(end.x(), start.y());
    drawQuarterCircle(center, start, compressionRatio, isLeft);

    start = end;
    direction = endDirection;
}

void Fractal::drawQuarterCircle(QPoint &center, QPoint &start, GLfloat compressionRatio, bool isLeft) {
    GLfloat angle;
    GLfloat radius;
    if (center.y() == start.y()) {
        angle = center.x() < start.x() ? 0 : 180;
        radius = abs(center.x() - start.x());
    } else {
        angle = center.y() < start.y() ? 90 : -90;
        radius = abs(center.y() - start.y());
    }

    for (int theta = 0; theta <= 90; theta++) {
        GLfloat xVertex = center.x() + radius * cos(M_PI * (angle + (isLeft ? 1 : -1) * theta) / 180);
        GLfloat yVertex = center.y() + radius * sin(M_PI * (angle + (isLeft ? 1 : -1) * theta) / 180);
        glVertex2f(compressionRatio * xVertex, compressionRatio * yVertex);
    }
}

void Fractal::setRecursionDepth(int pos){
    recursionDepp = pos;
    axioma = "BABA";
    replacement(recursionDepp, axioma);
    update();
}

void Fractal::replacement(int n, QString& lSystem){
    for(int step = 0; step < n - 1; step++){
        for(int i = 0; i < lSystem.size(); i++){
            if(lSystem[i] == 'A'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("CBAZ"));
            }else if(lSystem[i] == 'B'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("ZBAD"));
            }else if(lSystem[i] == 'C'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("ECDA"));
            }else if(lSystem[i] == 'D'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("BCDE"));
            }else if(lSystem[i] == 'E'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("CBAD"));
            }else if(lSystem[i] == 'Z'){
                lSystem.remove(i,1);
                lSystem.insert(i, QString("BCDA"));
            }
            i += 3;
        }
    }
}

