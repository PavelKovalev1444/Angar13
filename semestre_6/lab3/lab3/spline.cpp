#include "spline.h"

Spline::Spline(){
    curPoint = QPointF(-1.0, - 1.0);
    isMove = false;
    movePointIndex = -1;
    n = 6;
    k = 4;
    for(int i = 0;  i <= n + k; i++){
        tVector.push_back(countT(n, k, i));
    }

}

void Spline::countSpline(){
    if(curPointV.size() == 7){
        if(!allPoints.empty()){
            allPoints.clear();
        }
        for(int i = 1; i <= n - k + 2; i++){
            for(double x = i - 1; x <= i; x += 0.01){
                float rationalWeight = 0.0;
                for (int a = 0; a < curPointV.size(); a++){
                    float temp = N(a, k, x, tVector)*weights[a];
                    rationalWeight += temp;
                }
                allPoints.append(curPointV[i - 1]*N(i - 1, k, x, tVector)*weights[i - 1]/rationalWeight + curPointV[i]*N(i, k, x, tVector)*weights[i]/rationalWeight + curPointV[i+1]*N(i+1, k, x, tVector)*weights[i+1]/rationalWeight + curPointV[i+2]*N(i+2, k, x, tVector)*weights[i+2]/rationalWeight);
            }
        }
        allPoints.pop_back();
    }
}

float Spline::div(float a, int b){
    if(b == 0){
        return 0;
    }else{
        return a / float(b);
    }
}

float Spline::N(int i, int k, float x, QVector<int> t){
    if(k == 1){
        if(x >= t[i] && x < t[i+1]){
            return 1.0;
        }else{
            return 0.0;
        }
    }
    float a = div(x - t[i], t[i + k - 1] - t[i])*N(i, k - 1, x, t);
    float b = div(t[i + k] - x, t[i + k] - t[i + 1]) * N(i + 1, k - 1, x, t);
    return a + b;
}

int Spline::countT(int n, int k, int i){
    if(i < k){
        return 0;
    }else if (i >= k && i <= n){
        return i - k + 1;
    }else if (i > n){
        return n - k + 2;
    }
}

void Spline::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
}

void Spline::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho(0, 640, 480, 0, -1, 1);
}

void Spline::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(255.0f, 0.0f, 0.0f);
    for(int i = 0; i < curPointV.size(); i++){
        glVertex2d(curPointV[i].x(), curPointV[i].y());
    }
    glEnd();

    glPointSize(5.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 255.0f);
    for(int i = 0; i < allPoints.size(); i++){
        glVertex2d(allPoints[i].x(), allPoints[i].y());
    }
    glEnd();

    if(curPointV.size() == 7){
        glLineWidth(2.5);
        glBegin(GL_LINE_STRIP);
        glColor3d(0.0f, 255.0f, 0.0f);
        glVertex2d(curPointV[0].x(), curPointV[0].y());
        glVertex2d(curPointV[1].x(), curPointV[1].y());
        glVertex2d(curPointV[2].x(), curPointV[2].y());
        glVertex2d(curPointV[3].x(), curPointV[3].y());
        glVertex2d(curPointV[4].x(), curPointV[4].y());
        glVertex2d(curPointV[5].x(), curPointV[5].y());
        glVertex2d(curPointV[6].x(), curPointV[6].y());
        glEnd();
    }
}

void Spline::mousePressEvent(QMouseEvent* e){
    curPoint.setX(e->pos().x());
    curPoint.setY(e->pos().y());
    for(int i = 0; i < curPointV.size(); i++){
        if((curPointV[i].x() <= e->pos().x() + 15 && curPointV[i].x() >= e->pos().x() - 15) && (curPointV[i].y() <= e->pos().y() + 15 & curPointV[i].y() >= e->pos().y() - 15)){
            isMove = true;
            movePointIndex = i;
        }
    }
}

void Spline::mouseReleaseEvent(QMouseEvent* e){
    if(isMove){
        movePointIndex = -1;
        isMove = false;
        countSpline();
        update();
    }else if(e->pos().x() == curPoint.x() && e->pos().y() == curPoint.y() && curPointV.size() < n+1){
        bool hasYet = false;
        for(int i = 0; i < curPointV.size(); i++){
            if(curPointV[i].x() == e->pos().x() && curPointV[i].y() == e->pos().y()){
                hasYet = true;
            }
        }
        if(!hasYet){
            curPointV.push_back(curPoint);
            weights.push_back(1.0);
            countSpline();
            update();
        }
    }
}

void Spline::mouseMoveEvent(QMouseEvent* e){
    if(isMove){
        curPointV[movePointIndex].setX(e->pos().x());
        curPointV[movePointIndex].setY(e->pos().y());
        countSpline();
        update();
    }
}

void Spline::mouseDoubleClickEvent(QMouseEvent* e){
    int curPointIndex = -1;
    for(int i = 0; i < curPointV.size(); i++){
        if((curPointV[i].x() <= e->pos().x() + 15 && curPointV[i].x() >= e->pos().x() - 15) && (curPointV[i].y() <= e->pos().y() + 15 & curPointV[i].y() >= e->pos().y() - 15)){
            curPointIndex = i;
        }
    }
    if(curPointIndex != -1){
        QInputDialog* dialog = new QInputDialog();
        bool ok;
        double weight = dialog->getDouble(dialog, "Введите вес точки:", "Вес:", 0, 0, 2147483647, 1, &ok);
        if(ok){
            weights[curPointIndex] = weight;
            countSpline();
            update();
        }
    }
}
