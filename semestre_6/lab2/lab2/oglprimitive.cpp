#include "oglprimitive.h"

OGLPrimitive::OGLPrimitive(QWidget* wgt) : QOpenGLWidget(wgt)
{
    primitiveType = "GL_LINES";
    alphaFunc = "GL_ALWAYS";
    slideW=477;
    slideH=622;
    ref = 0.0;
    sfactor = GL_SRC_ALPHA;
    dfactor = GL_ONE_MINUS_SRC_ALPHA;
}

void OGLPrimitive::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OGLPrimitive::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho(0, 270, 270, 0, -1, 1);
}

void OGLPrimitive::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(255.0f, 0.0f, 0.0f);

    if(primitiveType == "GL_LINES"){
        glLineWidth(3);

        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, slideW, slideH);

        glEnable(GL_ALPHA_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(sfactor, dfactor);

        if(alphaFunc == "GL_NEVER"){
            glAlphaFunc(GL_NEVER, ref);
        }else if(alphaFunc == "GL_LESS"){
            glAlphaFunc(GL_LESS, ref);
        }else if(alphaFunc == "GL_EQUAL"){
            glAlphaFunc(GL_EQUAL, ref);
        }else if(alphaFunc == "GL_LEQUAL"){
            glAlphaFunc(GL_LEQUAL, ref);
        }else if(alphaFunc == "GL_GREATER"){
            glAlphaFunc(GL_GREATER, ref);
        }else if(alphaFunc == "GL_NOTEQUAL"){
            glAlphaFunc(GL_NOTEQUAL, ref);
        }else if(alphaFunc == "GL_GEQUAL"){
            glAlphaFunc(GL_GEQUAL, ref);
        }else if(alphaFunc == "GL_ALWAYS"){
            glAlphaFunc(GL_ALWAYS, ref);
        }

        glColor4d(255.0f, 0.0f, 0.0f, 0.7f);
        glBegin (GL_POLYGON); // Рисуем правильную n-стороннюю форму
        for (int i = 0; i<1000; ++i){
           glVertex2f(70 + 50*cos(2 * 3.14 / 1000*i), 70 + 50*sin(2 * 3.14 / 1000*i));
        }
        glEnd();

        glBegin (GL_POLYGON); // Рисуем правильную n-стороннюю форму
        glColor4d(0.0f, 255.0f, 0.0f, 0.6f);
        for (int i = 0; i<1000; ++i){
           glVertex2f(140 + 50*cos(2 * 3.14 / 1000*i), 70 + 50*sin(2 * 3.14 / 1000*i));
        }
        glEnd();

        glBegin (GL_POLYGON); // Рисуем правильную n-стороннюю форму
        glColor4d(0.0f, 0.0f, 255.0f, 0.8f);
        for (int i = 0; i<1000; ++i){
           glVertex2f(105 + 50*cos(2 * 3.14 / 1000*i), 105 + 50*sin(2 * 3.14 / 1000*i));
        }
        glEnd();



        glDisable(GL_ALPHA_TEST);
        glDisable(GL_SCISSOR_TEST);

        glEnd();
    }else if(primitiveType == "GL_LINE_LOOP"){
        glLineWidth(3);

        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, slideW, slideH);

        glEnable(GL_ALPHA_TEST);
        if(alphaFunc == "GL_NEVER"){
            glAlphaFunc(GL_NEVER, ref);
        }else if(alphaFunc == "GL_LESS"){
            glAlphaFunc(GL_LESS, ref);
        }else if(alphaFunc == "GL_EQUAL"){
            glAlphaFunc(GL_EQUAL, ref);
        }else if(alphaFunc == "GL_LEQUAL"){
            glAlphaFunc(GL_LEQUAL, ref);
        }else if(alphaFunc == "GL_GREATER"){
            glAlphaFunc(GL_GREATER, ref);
        }else if(alphaFunc == "GL_NOTEQUAL"){
            glAlphaFunc(GL_NOTEQUAL, ref);
        }else if(alphaFunc == "GL_GEQUAL"){
            glAlphaFunc(GL_GEQUAL, ref);
        }else if(alphaFunc == "GL_ALWAYS"){
            glAlphaFunc(GL_ALWAYS, ref);
        }

        glBegin(GL_LINE_LOOP);
        glVertex2d(30, 40);
        glVertex2d(30, 80);
        glVertex2d(120, 160);
        glVertex2d(200, 160);

        glDisable(GL_ALPHA_TEST);
        glDisable(GL_SCISSOR_TEST);

        glEnd();
    }else if(primitiveType == "GL_TRIANGLES"){
        glLineWidth(3);
        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, slideW, slideH);

        glEnable(GL_ALPHA_TEST);
        if(alphaFunc == "GL_NEVER"){
            glAlphaFunc(GL_NEVER, ref);
        }else if(alphaFunc == "GL_LESS"){
            glAlphaFunc(GL_LESS, ref);
        }else if(alphaFunc == "GL_EQUAL"){
            glAlphaFunc(GL_EQUAL, ref);
        }else if(alphaFunc == "GL_LEQUAL"){
            glAlphaFunc(GL_LEQUAL, ref);
        }else if(alphaFunc == "GL_GREATER"){
            glAlphaFunc(GL_GREATER, ref);
        }else if(alphaFunc == "GL_NOTEQUAL"){
            glAlphaFunc(GL_NOTEQUAL, ref);
        }else if(alphaFunc == "GL_GEQUAL"){
            glAlphaFunc(GL_GEQUAL, ref);
        }else if(alphaFunc == "GL_ALWAYS"){
            glAlphaFunc(GL_ALWAYS, ref);
        }

        glBegin(GL_TRIANGLES);
        glVertex2d(30, 40);
        glVertex2d(30, 80);
        glVertex2d(120, 160);
        glVertex2d(200, 160);

        glDisable(GL_ALPHA_TEST);
        glDisable(GL_SCISSOR_TEST);

        glEnd();
    }else if(primitiveType == "GL_POLYGON"){
        glLineWidth(3);

        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, slideW, slideH);

        glEnable(GL_ALPHA_TEST);
        if(alphaFunc == "GL_NEVER"){
            glAlphaFunc(GL_NEVER, ref);
        }else if(alphaFunc == "GL_LESS"){
            glAlphaFunc(GL_LESS, ref);
        }else if(alphaFunc == "GL_EQUAL"){
            glAlphaFunc(GL_EQUAL, ref);
        }else if(alphaFunc == "GL_LEQUAL"){
            glAlphaFunc(GL_LEQUAL, ref);
        }else if(alphaFunc == "GL_GREATER"){
            glAlphaFunc(GL_GREATER, ref);
        }else if(alphaFunc == "GL_NOTEQUAL"){
            glAlphaFunc(GL_NOTEQUAL, ref);
        }else if(alphaFunc == "GL_GEQUAL"){
            glAlphaFunc(GL_GEQUAL, ref);
        }else if(alphaFunc == "GL_ALWAYS"){
            glAlphaFunc(GL_ALWAYS, ref);
        }

        glBegin(GL_LINE_LOOP);
        glVertex2d(30, 40);
        glVertex2d(60, 80);
        glVertex2d(130, 160);
        glVertex2d(200, 190);


        glDisable(GL_ALPHA_TEST);
        glDisable(GL_SCISSOR_TEST);

        glEnd();
    }

}

void OGLPrimitive::setPrimitive(QString type){
    primitiveType = type;
    update();
}

void OGLPrimitive::setSlideWidth(int w){
    slideW = w;
    update();
}

void OGLPrimitive::setSlideHeight(int h){
    slideH = h;
    update();
}

void OGLPrimitive::setAlphaFunc(QString type){
    alphaFunc = type;
    //qDebug() << "type = " << type;
    update();
}

void OGLPrimitive::setRef(int d){
    ref = d/255.0;
    //qDebug() << "ref = " << ref;
    update();
}

void OGLPrimitive::setSfactor(QString type){
    if(type == "GL_ZERO"){
        sfactor = GL_ZERO;
    }else if(type == "GL_ONE"){
        sfactor = GL_ONE;
    }else if(type == "GL_DST_COLOR"){
        sfactor = GL_DST_COLOR;
    }else if(type == "GL_ONE_MINUS_DST_COLOR"){
        sfactor = GL_ONE_MINUS_DST_COLOR;
    }else if(type == "GL_SRC_ALPHA"){
        sfactor = GL_SRC_ALPHA;
    }else if(type == "GL_ONE_MINUS_SRC_ALPHA"){
        sfactor = GL_ONE_MINUS_SRC_ALPHA;
    }else if(type == "GL_DST_ALPHA"){
        sfactor = GL_DST_ALPHA;
    }else if(type == "GL_ONE_MINUS_DST_ALPHA"){
        sfactor = GL_ONE_MINUS_DST_ALPHA;
    }else if(type == "GL_SRC_ALPHA_SATURATE"){
        sfactor = GL_SRC_ALPHA_SATURATE;
    }
    update();
}

void OGLPrimitive::setDfactor(QString type){
    if(type == "GL_ZERO"){
        dfactor = GL_ZERO;
    }else if(type == "GL_ONE"){
        dfactor = GL_ONE;
    }else if(type == "GL_SRC_COLOR"){
        dfactor = GL_SRC_COLOR;
    }else if(type == "GL_ONE_MINUS_SRC_COLOR"){
        dfactor = GL_ONE_MINUS_SRC_COLOR;
    }else if(type == "GL_SRC_ALPHA"){
        dfactor = GL_SRC_ALPHA;
    }else if(type == "GL_ONE_MINUS_SRC_ALPHA"){
        dfactor = GL_ONE_MINUS_SRC_ALPHA;
    }else if(type == "GL_DST_ALPHA"){
        dfactor = GL_DST_ALPHA;
    }else if(type == "GL_ONE_MINUS_DST_ALPHA"){
        dfactor = GL_ONE_MINUS_DST_ALPHA;
    }
    update();
}
