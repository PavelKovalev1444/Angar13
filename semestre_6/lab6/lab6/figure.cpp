#include "figure.h"

Figure::Figure()
{
    shaderProgram = new QOpenGLShaderProgram();
    z = 1.8;
    r = 0.2;
    R = 0.4;
    frequency = 4;
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
    hasAxis = true;
    isOrtho = true;
}

void Figure::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
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

    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(xAlpha, 1.0f, 0.0f, 0.0f);
    rotationMatrix.rotate(yAlpha, 0.0f, 1.0f, 0.0f);
    rotationMatrix.rotate(zAlpha, 0.0f, 0.0f, 1.0f);

    scaleMatrix.setToIdentity();
    scaleMatrix.scale(xScale, yScale, zScale);

    shaderProgram->setUniformValue("projection", mProjectionMatrix);
    shaderProgram->setUniformValue("view", mViewMatrix);

    QVector<GLfloat> coordsArraySmallCircle(720*3);
    QVector<GLfloat> coordsArrayBigCircle(720*3);
    QVector<GLfloat> blueColors(720*3);
    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        blueColors[j] = 1.0;
        blueColors[j+1] = 0.0;
        blueColors[j+2] = 1.0;
        j+=3;
    }
    if(depth){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    drawConeCircle(r, z, coordsArraySmallCircle, blueColors);//draw small circle
    drawConeCircle(R, z - 1, coordsArrayBigCircle, blueColors);//draw big circle
    drawConeLines();
    if(hasAxis){
        drawAxis();//draw axis
    }

    if(depth){
        glDisable(GL_DEPTH_TEST);
    }
}

void Figure::drawCircle(float x0, float y0, float r, float z, QVector<GLfloat>& array){
    int i = 0;
    QVector4D curCoordinate;
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

void Figure::drawConeCircle(float radius, float tmpZ, QVector<GLfloat>& array, QVector<GLfloat>& colorArray){
    drawCircle(x0, y0, radius, tmpZ, array);
    glPointSize(2.0f);
//    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
//    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_POINTS, 0, 720);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::drawAxis()
{
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

    shaderProgram->setAttributeArray("position", axes, 3, 0);
    shaderProgram->setAttributeArray("colors", colors, 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINES, 0, 6);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::drawConeLines()
{
    float step = (360.0/(frequency))*M_PI/180;
    float radius = r;
    float tmpZ = z;
    QVector<GLfloat> coordsConeLines(frequency*6);
    QVector<GLfloat> colorsConeLines(frequency*6);
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

        colorsConeLines[j] = 1.0;
        colorsConeLines[j+1] = 0.0;
        colorsConeLines[j+2] = 1.0;

        colorsConeLines[j+3] = 1.0;
        colorsConeLines[j+4] = 0.0;
        colorsConeLines[j+5] = 1.0;
        j += 6;
    }
    glLineWidth(2.0);
    shaderProgram->setAttributeArray("position", coordsConeLines.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorsConeLines.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINES, 0, frequency*2);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::init(){
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/pavel/leti_laby/ComputerGraphics/lab6/lab6/figureShadVert.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/pavel/leti_laby/ComputerGraphics/lab6/lab6/figureShadFrag.frag");
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
