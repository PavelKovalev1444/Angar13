#include "figure.h"

Figure::Figure()
{
    shaderProgram = new QOpenGLShaderProgram();
    z = 1.8;
    r = 0.2;
    R = 0.4;
    frequency = 16;
    x0 = 1.6;
    y0 = 1.6;
    camX = 3.5;
    camY = 3.5;
    camZ = 3.5;
    moveX = 0.0;
    moveY = 0.0;
    moveZ = 0.0;
    xAlpha = 0.0f;
    yAlpha = 0.0f;
    zAlpha = 0.0f;
    xScale = 1.0f;
    yScale = 1.0f;
    zScale = 1.0f;
    depth = true;
    hasAxis = false;
    isOrtho = true;
    light = 0;
}

void Figure::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    init();
}

void Figure::resizeGL(int width, int height){
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void Figure::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mProjectionMatrix;
    if(isOrtho){
        mProjectionMatrix.ortho(5, -5, -5, 5, -5, 14);
    }else{
        mProjectionMatrix.frustum(-2, 2, -3, 3, 1.5, 14);
    }

    QMatrix4x4 mViewMatrix;
    mViewMatrix.lookAt({camX, camY, camZ}, {0, 0, 0}, {0, 1, 0});

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(xAlpha, 1.0f, 0.0f, 0.0f);
    rotationMatrix.rotate(yAlpha, 0.0f, 1.0f, 0.0f);
    rotationMatrix.rotate(zAlpha, 0.0f, 0.0f, 1.0f);

    scaleMatrix.setToIdentity();
    scaleMatrix.scale(xScale, yScale, zScale);

    shaderProgram->setUniformValue("projection", mProjectionMatrix);
    shaderProgram->setUniformValue("view", mViewMatrix);
    shaderProgram->setUniformValue("model", modelMatrix);

    QVector3D lAmbient = {10.0, 10.0, 10.0};
    shaderProgram->setUniformValue("ambientLight", lAmbient);
    shaderProgram->setUniformValue("type", light);

    QVector3D lightAmbient = {0.25, 0.20725, 0.20725};
    QVector3D lightDiffuse = {1, 0.829, 0.829};
    QVector3D lightSpecular = {0.296648, 0.296648, 0.296648};

    bool directedLightFlag = false;

    if (light == 1){
        // направленный источник света
        QVector3D lightDirection = {-0.3, -1.2, -1.6};
        QVector3D cameraPos = {camX, camY, camZ};

        shaderProgram->setUniformValue("lightDirection", lightDirection);
        shaderProgram->setUniformValue("cameraPos", cameraPos);
        shaderProgram->setUniformValue("ambientLight", lightAmbient);
        shaderProgram->setUniformValue("diffuseLight", lightDiffuse);
        shaderProgram->setUniformValue("specularLight", lightSpecular);
        shaderProgram->setUniformValue("type", light);

    }else if(light == 2){
        // точечный источник света
        QVector3D lightPosition = {-1.0, 2.0, 5.0};
        QVector3D cameraPos = {camX, camY, camZ};

        shaderProgram->setUniformValue("lightPosition", lightPosition);
        shaderProgram->setUniformValue("cameraPos", cameraPos);
        shaderProgram->setUniformValue("ambientLight", lightAmbient);
        shaderProgram->setUniformValue("diffuseLight", lightDiffuse);
        shaderProgram->setUniformValue("specularLight", lightSpecular);
        shaderProgram->setUniformValue("lightConstant", 1.0f);
        shaderProgram->setUniformValue("lightLinear", 0.007f);
        shaderProgram->setUniformValue("lightQuadratic", 0.0019f);
        shaderProgram->setUniformValue("type", light);

        directedLightFlag = true;

    }else if(light == 3){
        // прожектор
        QVector3D lightPosition = {0.5, 2.0, 2.0};
        QVector3D lightDirection = {0.5, 2.0, 2.0};
        QVector3D cameraPos = {camX, camY, camZ};
        QVector3D cameraDir = {-camX, -camY, -camZ};
        float lightCutOff = cos(M_PI/6);

        shaderProgram->setUniformValue("lightPosition", cameraPos);
        shaderProgram->setUniformValue("cameraPos", cameraPos);
        shaderProgram->setUniformValue("lightDirection", cameraDir);
        shaderProgram->setUniformValue("lightCutOff", lightCutOff);
        shaderProgram->setUniformValue("ambientLight", lightAmbient);
        shaderProgram->setUniformValue("diffuseLight", lightDiffuse);
        shaderProgram->setUniformValue("specularLight", lightSpecular);
        shaderProgram->setUniformValue("lightConstant", 1.0f);
        shaderProgram->setUniformValue("lightLinear", 0.007f);
        shaderProgram->setUniformValue("lightQuadratic", 0.0019f);
        shaderProgram->setUniformValue("type", light);

    }
    if(depth){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    //drawWall();
    drawScene();
    if(directedLightFlag){
        drawLight();
    }
    if(hasAxis){
        drawAxis();
    }
    if(depth){
        glDisable(GL_DEPTH_TEST);
    }
}

void Figure::drawWall(){

    GLfloat surface[] = {
        2,0,2,   2,0,-2,
        -2,0,-2, -2,0,2
    };

    GLfloat colorSurface[] = {
        1,1,0, 1,1,0,
        1,1,0, 1,1,0
    };

    GLfloat normalsSurface[] = {
        0,1,0, 0,1,0,
        0,1,0, 0,1,0
    };

    shaderProgram->setAttributeArray("position", surface, 3, 0);
    shaderProgram->setAttributeArray("colors", colorSurface, 3, 0);
    shaderProgram->setAttributeArray("normal", normalsSurface, 3, 0);

    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    shaderProgram->enableAttributeArray("normal");

    glDrawArrays(GL_QUADS, 0, 4);

    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    shaderProgram->disableAttributeArray("normal");

    GLfloat array[] = {
        1, 0, 0,   1, 1, 0,
        0, 1, 1,   0, 0, 1,

        1, 1, 0,   0, 1, 0,
        -1, 1, 1,   0, 1, 1,

        0, 1, 1,   -1, 1, 1,
        -1, 0, 1,   0, 0, 1

    };

    GLfloat colors[] = {
        0, 1, 0,   0, 1, 0,
        0, 1, 0,   0, 1, 0,

        0, 0, 1,   0, 0, 1,
        0, 0, 1,   0, 0, 1,

        1, 0, 0,   1, 0, 0,
        1, 0, 0,   1, 0, 0
    };

    GLfloat normals[] = {
        1,0,1, 1,0,1,
        1,0,1, 1,0,1,

        0,1,0,    0,1,0,
        0,1,0,    0,1,0,

        -1,0,1,   -1,0,1,
        -1,0,1,   -1,0,1
    };
    glPointSize(2.0f);

    shaderProgram->setAttributeArray("position", array, 3, 0);
    shaderProgram->setAttributeArray("colors", colors, 3, 0);
    shaderProgram->setAttributeArray("normal", normals, 3, 0);

    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    shaderProgram->enableAttributeArray("normal");

    glDrawArrays(GL_QUADS, 0, 12);

    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    shaderProgram->disableAttributeArray("normal");
}

void Figure::drawScene()
{
    drawCone1(3.0, 0.0, 0.75, 1.0, 0.8, 0.0, 0.7);
    drawCone1(1.0, 0.0, 0.75, 3.0, 0.8, 0.5, 0.0);
    drawCone2(1.0, 0.0, 0.75, 1.0, 0.2, 0.9, 0.1);
    drawCone3(3.0, 0.0, 0.75, 3.0, 0.2, 0.8, 0.7);
}

void Figure::drawCone1(float x0, float y0, float r, float z, GLfloat red, GLfloat green, GLfloat blue)
{
    QMatrix4x4 rotateM;
    rotateM.setToIdentity();
    rotateM.rotate(0.0, 1.0f, 0.0f, 0.0f);
    rotateM.rotate(0.0, 0.0f, 1.0f, 0.0f);
    rotateM.rotate(345, 0.0f, 0.0f, 1.0f);

    QVector<GLfloat> coordsArrayDown(720*3);
    QVector<GLfloat> coordsArrayUp(720*3);
    QVector<GLfloat> coordsArraySide(720*3);

    QVector<GLfloat> normalsArrayDown(720*3);
    QVector<GLfloat> normalsArrayUp(720*3);
    QVector<GLfloat> normalsArraySide(720*3);

    QVector<GLfloat> colors(720*3);
    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red;
        colors[j+1] = green;
        colors[j+2] = blue;
        j+=3;
    }
    int i = 0;
    QVector4D curCoordinate;
    j = 0;
    for(float alpha = 0; alpha < 360; alpha+=0.5){
        curCoordinate.setX(x0 + r*cos(alpha) + moveX);
        curCoordinate.setY(y0 + moveY);
        curCoordinate.setZ(z + r*sin(alpha) + moveZ);
        curCoordinate.setW(1.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;
        coordsArrayDown[i] = curCoordinate.x();
        coordsArrayDown[i+1] = curCoordinate.y();
        coordsArrayDown[i+2] = curCoordinate.z();

        curCoordinate.setX(x0 + r/2*cos(alpha) + moveX);
        curCoordinate.setY(y0 + moveY);
        curCoordinate.setZ(z + r/2*sin(alpha) + moveZ);
        curCoordinate.setW(1.0f);
        curCoordinate = rotateM * curCoordinate;
        coordsArrayUp[i] = curCoordinate.x();
        coordsArrayUp[i+1] = curCoordinate.y() + 2.0;
        coordsArrayUp[i+2] = curCoordinate.z();

        if(j%2 == 0){
            coordsArraySide[i] = coordsArrayUp[i];
            coordsArraySide[i+1] = coordsArrayUp[i+1];
            coordsArraySide[i+2] = coordsArrayUp[i+2];
        }else{
            coordsArraySide[i] = coordsArrayDown[i];
            coordsArraySide[i+1] = coordsArrayDown[i+1];
            coordsArraySide[i+2] = coordsArrayDown[i+2];
        }
        i+=3;
        j+=1;
    }

    QVector3D p1 = QVector3D(coordsArrayDown[0], coordsArrayDown[1], coordsArrayDown[2]);
    QVector3D p2 = QVector3D(coordsArrayDown[3], coordsArrayDown[4], coordsArrayDown[5]);
    QVector3D p3 = QVector3D(coordsArrayDown[6], coordsArrayDown[7], coordsArrayDown[8]);
    QVector3D cDown = cDown.normal(p1, p2, p3);

    p1.setX(coordsArrayUp[0]);
    p1.setY(coordsArrayUp[1]);
    p1.setZ(coordsArrayUp[2]);
    p2.setX(coordsArrayUp[3]);
    p2.setY(coordsArrayUp[4]);
    p2.setZ(coordsArrayUp[5]);
    p3.setX(coordsArrayUp[6]);
    p3.setY(coordsArrayUp[7]);
    p3.setZ(coordsArrayUp[8]);
    QVector3D cUp = cUp.normal(p1, p2, p3);

    for(int a = 0; a < 720; a+=3){
        normalsArrayDown[a] = cDown.x();
        normalsArrayDown[a+1] = cDown.y();
        normalsArrayDown[a+2] = cDown.z();

        normalsArrayUp[a] = cUp.x();
        normalsArrayUp[a+1] = cUp.y();
        normalsArrayUp[a+2] = cUp.z();
    }

    for(int a = 0; a < 720; a+=9){
        p1.setX(coordsArraySide[a+0]);
        p1.setY(coordsArraySide[a+1]);
        p1.setZ(coordsArraySide[a+2]);
        p2.setX(coordsArraySide[a+3]);
        p2.setY(coordsArraySide[a+4]);
        p2.setZ(coordsArraySide[a+5]);
        p3.setX(coordsArraySide[a+6]);
        p3.setY(coordsArraySide[a+7]);
        p3.setZ(coordsArraySide[a+8]);

        QVector3D c = c.normal(p1, p2, p3);
        normalsArraySide[a+0] = c.x();
        normalsArraySide[a+1] = c.y();
        normalsArraySide[a+2] = c.z();
        normalsArraySide[a+3] = c.x();
        normalsArraySide[a+4] = c.y();
        normalsArraySide[a+5] = c.z();
        normalsArraySide[a+6] = c.x();
        normalsArraySide[a+7] = c.y();
        normalsArraySide[a+8] = c.z();
    }

    drawSurface(coordsArrayDown, colors, normalsArrayDown,GL_POLYGON);
    drawSurface(coordsArrayUp, colors, normalsArrayUp,GL_POLYGON);
    j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red + 0.2;
        colors[j+1] = green;
        colors[j+2] = blue;
        j+=3;
    }
    drawSurface(coordsArraySide, colors, normalsArraySide,GL_TRIANGLE_STRIP);
}

void Figure::drawCone2(float x0, float y0, float r, float z, GLfloat red, GLfloat green, GLfloat blue)
{
    QVector<GLfloat> coordsArrayDown(720*3);
    QVector<GLfloat> coordArrayUp(1*3);
    QVector<GLfloat> coordsArraySide(720*3);
    QVector<GLfloat> colors(720*3);

    QVector<GLfloat> normalsArrayDown(720*3);
    QVector<GLfloat> normalsArrayUp(720*3);
    QVector<GLfloat> normalsArraySide(720*3);

    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red;
        colors[j+1] = green;
        colors[j+2] = blue;
        j+=3;
    }
    int i = 0;
    QVector4D curCoordinate;

    QVector4D centrCoordinate;
    centrCoordinate.setX(x0 + moveX);
    centrCoordinate.setY(y0 + + moveY + 2);
    centrCoordinate.setZ(z + moveZ);
    centrCoordinate.setW(1.0);
    centrCoordinate = rotationMatrix * centrCoordinate;
    centrCoordinate = scaleMatrix * centrCoordinate;
    coordArrayUp[0] = centrCoordinate.x();
    coordArrayUp[1] = centrCoordinate.y();
    coordArrayUp[2] = centrCoordinate.z();

    j = 0;
    for(float alpha = 0; alpha < 360; alpha+=0.5){
        curCoordinate.setX(x0 + r*cos(alpha) + moveX);
        curCoordinate.setY(y0 + moveY);
        curCoordinate.setZ(z + r*sin(alpha) + moveZ);
        curCoordinate.setW(1.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;
        coordsArrayDown[i] = curCoordinate.x();
        coordsArrayDown[i+1] = curCoordinate.y();
        coordsArrayDown[i+2] = curCoordinate.z();

        if(j%2 == 0){
            coordsArraySide[i] = centrCoordinate[0];
            coordsArraySide[i+1] = centrCoordinate[1];
            coordsArraySide[i+2] = centrCoordinate[2];
        }else{
            coordsArraySide[i] = coordsArrayDown[i];
            coordsArraySide[i+1] = coordsArrayDown[i+1];
            coordsArraySide[i+2] = coordsArrayDown[i+2];
        }
        i+=3;
        j+=1;
    }

    QVector3D p1 = QVector3D(coordsArrayDown[0], coordsArrayDown[1], coordsArrayDown[2]);
    QVector3D p2 = QVector3D(coordsArrayDown[3], coordsArrayDown[4], coordsArrayDown[5]);
    QVector3D p3 = QVector3D(coordsArrayDown[6], coordsArrayDown[7], coordsArrayDown[8]);
    QVector3D cDown = cDown.normal(p1, p2, p3);

    for(int a = 0; a < 720; a+=3){
        normalsArrayDown[a] = cDown.x();
        normalsArrayDown[a+1] = cDown.y();
        normalsArrayDown[a+2] = cDown.z();
    }

    for(int a = 0; a < 720; a+=9){
        p1.setX(coordsArraySide[a+0]);
        p1.setY(coordsArraySide[a+1]);
        p1.setZ(coordsArraySide[a+2]);
        p2.setX(coordsArraySide[a+3]);
        p2.setY(coordsArraySide[a+4]);
        p2.setZ(coordsArraySide[a+5]);
        p3.setX(coordsArraySide[a+6]);
        p3.setY(coordsArraySide[a+7]);
        p3.setZ(coordsArraySide[a+8]);

        QVector3D c = c.normal(p1, p2, p3);
        normalsArraySide[a+0] = c.x();
        normalsArraySide[a+1] = c.y();
        normalsArraySide[a+2] = c.z();
        normalsArraySide[a+3] = c.x();
        normalsArraySide[a+4] = c.y();
        normalsArraySide[a+5] = c.z();
        normalsArraySide[a+6] = c.x();
        normalsArraySide[a+7] = c.y();
        normalsArraySide[a+8] = c.z();
    }

    normalsArrayUp[0] = normalsArraySide[0];
    normalsArrayUp[1] = normalsArraySide[1];
    normalsArrayUp[2] = normalsArraySide[2];

    drawSurface(coordsArrayDown, colors, normalsArrayDown, GL_POLYGON);
    drawSurface(coordArrayUp, colors, normalsArrayUp, GL_POINTS);
    j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red + 0.2;
        colors[j+1] = green;
        colors[j+2] = blue;
        j+=3;
    }
    drawSurface(coordsArraySide, colors, normalsArraySide, GL_TRIANGLE_STRIP);
}

void Figure::drawCone3(float x0, float y0, float r, float z, GLfloat red, GLfloat green, GLfloat blue)
{
    QVector<GLfloat> coordsArrayDown(720*3);
    QVector<GLfloat> coordsArrayCenter(720*3);
    QVector<GLfloat> coordsArrayUp(720*3);
    QVector<GLfloat> coordsArraySide1(720*3);
    QVector<GLfloat> coordsArraySide2(720*3);
    QVector<GLfloat> colors(720*3);

    QVector<GLfloat> normalsArrayDown(720*3);
    QVector<GLfloat> normalsArrayUp(720*3);
    QVector<GLfloat> normalsArraySide1(720*3);
    QVector<GLfloat> normalsArraySide2(720*3);

    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red;
        colors[j+1] = green;
        colors[j+2] = blue;
        j+=3;
    }

    QVector4D curCoordinate;
    j = 0;
    int i = 0;
    for(float alpha = 0; alpha < 360; alpha+=0.5){
        curCoordinate.setX(x0 + r*cos(alpha) + moveX);
        curCoordinate.setY(y0 + moveY);
        curCoordinate.setZ(z + r*sin(alpha) + moveZ);
        curCoordinate.setW(1.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;
        coordsArrayDown[i] = curCoordinate.x();
        coordsArrayDown[i+1] = curCoordinate.y();
        coordsArrayDown[i+2] = curCoordinate.z();

        coordsArrayUp[i] = curCoordinate.x();
        coordsArrayUp[i+1] = curCoordinate.y() + 2.0;
        coordsArrayUp[i+2] = curCoordinate.z();

        curCoordinate.setX(x0 + r/2*cos(alpha) + moveX);
        curCoordinate.setY(y0 + moveY);
        curCoordinate.setZ(z + r/2*sin(alpha) + moveZ);
        curCoordinate.setW(1.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;
        coordsArrayCenter[i] = curCoordinate.x();
        coordsArrayCenter[i+1] = curCoordinate.y() + 1.0;
        coordsArrayCenter[i+2] = curCoordinate.z();

        if(j%2 == 0){
            coordsArraySide1[i] = coordsArrayCenter[i];
            coordsArraySide1[i+1] = coordsArrayCenter[i+1];
            coordsArraySide1[i+2] = coordsArrayCenter[i+2];

            coordsArraySide2[i] = coordsArrayCenter[i];
            coordsArraySide2[i+1] = coordsArrayCenter[i+1];
            coordsArraySide2[i+2] = coordsArrayCenter[i+2];
        }else{
            coordsArraySide1[i] = coordsArrayDown[i];
            coordsArraySide1[i+1] = coordsArrayDown[i+1];
            coordsArraySide1[i+2] = coordsArrayDown[i+2];

            coordsArraySide2[i] = coordsArrayUp[i];
            coordsArraySide2[i+1] = coordsArrayUp[i+1];
            coordsArraySide2[i+2] = coordsArrayUp[i+2];
        }
        i+=3;
        j+=1;
    }

    QVector3D p1 = QVector3D(coordsArrayDown[0], coordsArrayDown[1], coordsArrayDown[2]);
    QVector3D p2 = QVector3D(coordsArrayDown[3], coordsArrayDown[4], coordsArrayDown[5]);
    QVector3D p3 = QVector3D(coordsArrayDown[6], coordsArrayDown[7], coordsArrayDown[8]);
    QVector3D cDown = cDown.normal(p1, p2, p3);

    p1.setX(coordsArrayUp[0]);
    p1.setY(coordsArrayUp[1]);
    p1.setZ(coordsArrayUp[2]);
    p2.setX(coordsArrayUp[3]);
    p2.setY(coordsArrayUp[4]);
    p2.setZ(coordsArrayUp[5]);
    p3.setX(coordsArrayUp[6]);
    p3.setY(coordsArrayUp[7]);
    p3.setZ(coordsArrayUp[8]);
    QVector3D cUp = cUp.normal(p1, p2, p3);

    for(int a = 0; a < 720; a+=3){
        normalsArrayDown[a] = cDown.x();
        normalsArrayDown[a+1] = cDown.y();
        normalsArrayDown[a+2] = cDown.z();

        normalsArrayUp[a] = cUp.x();
        normalsArrayUp[a+1] = cUp.y();
        normalsArrayUp[a+2] = cUp.z();
    }

    for(int a = 0; a < 720; a+=9){
        p1.setX(coordsArraySide1[a+0]);
        p1.setY(coordsArraySide1[a+1]);
        p1.setZ(coordsArraySide1[a+2]);
        p2.setX(coordsArraySide1[a+3]);
        p2.setY(coordsArraySide1[a+4]);
        p2.setZ(coordsArraySide1[a+5]);
        p3.setX(coordsArraySide1[a+6]);
        p3.setY(coordsArraySide1[a+7]);
        p3.setZ(coordsArraySide1[a+8]);

        QVector3D c1 = c1.normal(p1, p2, p3);
        normalsArraySide1[a+0] = c1.x();
        normalsArraySide1[a+1] = c1.y();
        normalsArraySide1[a+2] = c1.z();
        normalsArraySide1[a+3] = c1.x();
        normalsArraySide1[a+4] = c1.y();
        normalsArraySide1[a+5] = c1.z();
        normalsArraySide1[a+6] = c1.x();
        normalsArraySide1[a+7] = c1.y();
        normalsArraySide1[a+8] = c1.z();

        p1.setX(coordsArraySide2[a+0]);
        p1.setY(coordsArraySide2[a+1]);
        p1.setZ(coordsArraySide2[a+2]);
        p2.setX(coordsArraySide2[a+3]);
        p2.setY(coordsArraySide2[a+4]);
        p2.setZ(coordsArraySide2[a+5]);
        p3.setX(coordsArraySide2[a+6]);
        p3.setY(coordsArraySide2[a+7]);
        p3.setZ(coordsArraySide2[a+8]);

        QVector3D c2 = c2.normal(p1, p2, p3);
        normalsArraySide2[a+0] = c2.x();
        normalsArraySide2[a+1] = c2.y();
        normalsArraySide2[a+2] = c2.z();
        normalsArraySide2[a+3] = c2.x();
        normalsArraySide2[a+4] = c2.y();
        normalsArraySide2[a+5] = c2.z();
        normalsArraySide2[a+6] = c2.x();
        normalsArraySide2[a+7] = c2.y();
        normalsArraySide2[a+8] = c2.z();
    }

    drawSurface(coordsArrayDown, colors, normalsArrayDown, GL_POLYGON);
    drawSurface(coordsArraySide1, colors, normalsArraySide1, GL_TRIANGLE_STRIP);
    drawSurface(coordsArraySide2, colors, normalsArraySide2, GL_TRIANGLE_STRIP);
    j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        colors[j] = red - 0.2;
        colors[j+1] = green - 0.4;
        colors[j+2] = blue;
        j+=3;
    }
    drawSurface(coordsArrayUp, colors, normalsArrayUp, GL_POLYGON);
}

void Figure::drawSurface(QVector<GLfloat>& array, QVector<GLfloat>& colorArray, QVector<GLfloat>& normalArray, GLenum mode)
{
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("normal", normalArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    shaderProgram->enableAttributeArray("normal");
    glDrawArrays(mode, 0, array.size()/3);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    shaderProgram->disableAttributeArray("normal");
}

void Figure::drawLight(){
    shaderProgram->setUniformValue("type", 4);
    glPointSize(12.0f);
    GLfloat surface[] = {-1.0, 2.0, 5.0};
    GLfloat colorSurface[] = {1,1,1};
    GLfloat normalsSurface[] = {0,1,0};
    shaderProgram->setAttributeArray("position", surface, 3, 0);
    shaderProgram->setAttributeArray("colors", colorSurface, 3, 0);
    shaderProgram->setAttributeArray("normal", normalsSurface, 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    shaderProgram->enableAttributeArray("normal");
    glDrawArrays(GL_POINTS, 0, 1);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    shaderProgram->disableAttributeArray("normal");
}

void Figure::drawAxis(){
    GLfloat axes[] = {
        -4, 0, 0,   4, 0, 0,
        0, -4, 0,   0, 4, 0,
        0, 0, -4,   0, 0, 4
    };
    GLfloat colors[] = {
        1, 0, 0,   1, 0, 0,
        0, 1, 0,   0, 1, 0,
        0, 0, 1,   0, 0, 1
    };

    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    shaderProgram->setAttributeArray("position", axes, 3, 0);
    shaderProgram->setAttributeArray("colors", colors, 3, 0);
    glDrawArrays(GL_LINES, 0, 6);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::init(){
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/pavel/leti_laby/ComputerGraphics/CW/CW/figureShadVert.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/pavel/leti_laby/ComputerGraphics/CW/CW/figureShadFrag.frag");
    shaderProgram->link();
    shaderProgram->bind();
}

void Figure::setEnableAxis(bool checkbox){
    hasAxis = checkbox;
    update();
}

void Figure::setDivision(int tmpDivision){
    frequency = tmpDivision;
    update();
}

void Figure::setSmallRadius(float tmpr){
    r = tmpr;
    update();
}

void Figure::setBigRadius(double tmpR){
    R = tmpR;
    update();
}

void Figure::setEnableDepth(bool depthCheck)
{
    depth = depthCheck;
    update();
}

void Figure::camXChanged(float camXtmp)
{
    camX = (float)camXtmp;
    update();
}

void Figure::camYChanged(float camYtmp)
{
    camY = (float)camYtmp;
    update();
}

void Figure::camZChanged(float camZtmp)
{
    camZ = camZtmp;
    update();
}

void Figure::setOrthoFrustum(bool tmpOrtho)
{
    isOrtho = tmpOrtho;
    update();
}

void Figure::setXMove(float tmpX){
    moveX = tmpX;
    update();
}

void Figure::setYMove(float tmpY){
    moveY = tmpY;
    update();
}

void Figure::setZMove(float tmpZ){
    moveZ = tmpZ;
    update();
}

void Figure::setXRot(float xalphatmp){
    xAlpha = xalphatmp;
    update();
}

void Figure::setYRot(float yalphatmp){
    yAlpha = yalphatmp;
    update();
}

void Figure::setZRot(float zalphatmp){
    zAlpha = zalphatmp;
    update();
}

void Figure::setXScal(float xScalTmp)
{
    xScale = xScalTmp;
    update();
}

void Figure::setYScal(float yScalTmp)
{
    yScale = yScalTmp;
    update();
}

void Figure::setZScal(float zScalTmp)
{
    zScale = zScalTmp;
    update();
}

void Figure::setLight(QString lightType)
{
    if(lightType == "Света нет"){
        light = 0;
    }else if(lightType == "Направленный свет"){
        light = 1;
    }else if(lightType == "Точечный свет"){
        light = 2;
    }else if(lightType == "Прожектор"){
        light = 3;
    }
    update();
}
