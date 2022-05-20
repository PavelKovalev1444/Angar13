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
    depth = false;
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
        // нарисовать точку, которая светит
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
        float lightCutOff = cos(M_PI/3);

        shaderProgram->setUniformValue("lightPosition", cameraPos);
        shaderProgram->setUniformValue("cameraPos", cameraPos);
        shaderProgram->setUniformValue("lightDirection", cameraPos);
        shaderProgram->setUniformValue("lightCutOff", lightCutOff);
        shaderProgram->setUniformValue("ambientLight", lightAmbient);
        shaderProgram->setUniformValue("diffuseLight", lightDiffuse);
        shaderProgram->setUniformValue("specularLight", lightSpecular);
        shaderProgram->setUniformValue("lightConstant", 1.0f);
        shaderProgram->setUniformValue("lightLinear", 0.007f);
        shaderProgram->setUniformValue("lightQuadratic", 0.0019f);
        shaderProgram->setUniformValue("type", light);

    }

    QVector<GLfloat> coordsArraySmallCircle(720*3);
    QVector<GLfloat> coordsArrayBigCircle(720*3);
    QVector<GLfloat> blueColors(720*3);
    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        blueColors[j] = 1.0;
        blueColors[j+1] = 0.0;
        blueColors[j+2] = 0.8;
        j+=3;
    }
    if(depth){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    //drawConeCircle(r, z, coordsArraySmallCircle, blueColors, 0);//draw small circle
    //drawConeCircle(R, z - 1, coordsArrayBigCircle, blueColors, 1);//draw big circle
    //drawConeLines();
    drawWall();
    if(directedLightFlag){
        drawLight();
    }
    if(hasAxis){
        drawAxis();
    }
    if(depth){
        glDisable(GL_DEPTH_TEST);
    }
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
}

void Figure::drawCircle(float x0, float y0, float r, float z, QVector<GLfloat>& array, int normalSide){
    int i = 0;
    QVector4D curCoordinate;
    if(normalSide == 1){
        glNormal3f(0.0,r*(z + moveZ),r*r);
    }else{
        glNormal3f(0.0,-1*r*(z + moveZ),-1*r*r);
    }

    for(float alpha = 0; alpha < 360; alpha+=0.5){

        curCoordinate.setX(x0 + r*cos(alpha) + moveX);
        curCoordinate.setY(y0 + r*sin(alpha) + moveY);
        curCoordinate.setZ(z + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        array[i] = curCoordinate.x();
        array[i+1] = curCoordinate.y();
        array[i+2] = curCoordinate.z();
        i+=3;
    }
}

void Figure::drawConeCircle(float radius, float tmpZ, QVector<GLfloat>& array, QVector<GLfloat>& colorArray, int normalSide){
    drawCircle(x0, y0, radius, tmpZ, array, normalSide);
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_POLYGON, 0, 720);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
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

void Figure::drawConeLines(){
    float step = (360.0/(frequency))*M_PI/180;
    float radius = r;
    float tmpZ = z;
    QVector<GLfloat> coordsConeLines(frequency*6);
    QVector<GLfloat> colorsConeLines(frequency*6);

    QVector<GLfloat> coordsConeLines2(frequency*6);
    QVector<GLfloat> colorsConeLines2(frequency*6);

    QVector4D curCoordinate;
    int j = 0;
    for(int i = 0; i < frequency; i++){
        if(i%2 == 0){
            radius = r;
        }else{
            radius = R;
        }

        curCoordinate.setX(x0+radius*cos(i*step) + moveX);
        curCoordinate.setY(y0+radius*sin(i*step) + moveY);
        curCoordinate.setZ(tmpZ + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        coordsConeLines[j] = curCoordinate.x();
        coordsConeLines[j+1] = curCoordinate.y();
        coordsConeLines[j+2] = curCoordinate.z();

        if(i%2 == 0){
            radius = R;
            tmpZ = z - 1;
        }else{
            radius = r;
            tmpZ = z;
        }

        curCoordinate.setX(x0+radius*cos((i+1)*step) + moveX);
        curCoordinate.setY(y0+radius*sin((i+1)*step) + moveY);
        curCoordinate.setZ(tmpZ + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix*curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        coordsConeLines[j+3] = curCoordinate.x();
        coordsConeLines[j+4] = curCoordinate.y();
        coordsConeLines[j+5] = curCoordinate.z();

        colorsConeLines[j+0] = 0.0;
        colorsConeLines[j+1] = 0.0;
        colorsConeLines[j+2] = 1.0;

        colorsConeLines[j+3] = 0.0;
        colorsConeLines[j+4] = 0.0;
        colorsConeLines[j+5] = 1.0;

        colorsConeLines2[j+0] = 0.0;
        colorsConeLines2[j+1] = 1.0;
        colorsConeLines2[j+2] = 0.7;

        colorsConeLines2[j+3] = 0.0;
        colorsConeLines2[j+4] = 1.0;
        colorsConeLines2[j+5] = 0.7;

        if(i > 0 && i%2 == 1){
            QVector3D a = QVector3D(coordsConeLines[j-6] - coordsConeLines[j-3], coordsConeLines[j-5] - coordsConeLines[j-2], coordsConeLines[j-4] - coordsConeLines[j-1]);
            QVector3D b = QVector3D(coordsConeLines[j] - coordsConeLines[j-3], coordsConeLines[j+1] - coordsConeLines[j-2], coordsConeLines[j+2] - coordsConeLines[j-1]);
            QVector3D n;
            n.normal(a, b);
            glNormal3f(n.x(), n.y(), n.z());
        }

        j += 6;
    }

    j = 0;
    for(int i = 0; i < coordsConeLines2.size()/3 - 1; i++){
        coordsConeLines2[j] = coordsConeLines[j+3];
        coordsConeLines2[j+1] = coordsConeLines[j+4];
        coordsConeLines2[j+2] = coordsConeLines[j+5];
        j += 3;
    }
    coordsConeLines2[frequency*6 - 3] = coordsConeLines[0];
    coordsConeLines2[frequency*6 - 2] = coordsConeLines[1];
    coordsConeLines2[frequency*6 - 1] = coordsConeLines[2];

    glLineWidth(2.0);
    shaderProgram->setAttributeArray("position", coordsConeLines.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorsConeLines.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_TRIANGLES, 0, frequency*2);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");

    glLineWidth(2.0);
    shaderProgram->setAttributeArray("position", coordsConeLines2.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorsConeLines.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_TRIANGLES, 0, frequency*2);
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
