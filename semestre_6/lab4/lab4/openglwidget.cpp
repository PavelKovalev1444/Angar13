#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    depth = 0;
}

void OpenGLWidget::initializeGL() {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();
    functions->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int width, int height) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void OpenGLWidget::paintGL() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        drawFractal();
    glEnd();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    if (event->delta() > 0 && depth < 5)
        depth++;
    if (event->delta() < 0 && depth > 0)
        depth--;
    update();
}

QString OpenGLWidget::getFractal(int iteration) {
    QString result = axiom;
    for (int i = 0; i < iteration; i++) {
        QString temp = result;
        result = "";
        for (auto symbol : temp) {
            switch(symbol.toLatin1()) {
                case 'A':
                    result += "CBAZ";
                    break;
                case 'B':
                    result += "ZBAD";
                    break;
                case 'C':
                    result += "ECDA";
                    break;
                case 'D':
                    result += "BCDE";
                    break;
                case 'E':
                    result += "CBAD";
                    break;
                case 'Z':
                    result += "BCDA";
                    break;
            }
        }
    }
    return result;
}

void OpenGLWidget::drawFractal() {
    QPoint point = QPoint(((int) qPow(2.0, 1.0 + depth)) - 1, 0);
    QPoint direction = QPoint(0, 1);
    GLfloat compressionRatio = 0.9 / (qPow(2.0, 1.0 + depth) - 1);

    QString fractal = getFractal(depth);
    for (auto symbol : fractal) {
        switch(symbol.toLatin1()) {
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

void OpenGLWidget::drawRotation(QPoint &start, QPoint &direction, GLfloat compressionRatio, bool isLeft) {
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

void OpenGLWidget::drawQuarterCircle(QPoint &center, QPoint &start, GLfloat compressionRatio, bool isLeft) {
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
