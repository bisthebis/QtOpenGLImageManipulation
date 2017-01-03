#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>
#include "../helpers/line.h"
#include "../opengl_utils/cube.h"

static const char* vertex = "attribute vec3 input_vertex;"
                            "attribute vec3 color;"
                            "varying vec3 oColor;"
                            "uniform mat4 projection;"
                            "uniform mat4 view;"
                            "void main() {"
                            "   oColor = color;"
                            "   gl_Position = projection * view * vec4(input_vertex, 1);"
                            "}";

static const char* frag = "varying vec3 oColor; void main() {gl_FragColor = vec4(oColor, 1);}";

SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) : QOpenGLWidget(parent, f)
{
    timer.start();
    view.setToIdentity();
    view.lookAt({10, 10, 10}, {0, 0, 0},  {0, 0, 1});
}
SampleWidget::~SampleWidget()
{
    if (cube)
        delete cube;
}

void SampleWidget::initializeGL()
{
    setUpdatesEnabled(true);
    f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0, 0.5, 1, 1);
    f->glDisable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);
    auto context = QOpenGLContext::currentContext();
    qDebug() << QString("OpenGL Informations : GLES ? %0. Major version : %1. Minor version : %2")
                .arg
                (context->isOpenGLES())
                .arg
                (context->format().version().first)
                .arg(context->format().version().second);

    cube = new Cube();

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, frag);
    shader.link();
    shader.bind();

}
void SampleWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    projection.setToIdentity();
    projection.perspective(45, ratio, 0.1, 100);
}

void SampleWidget::paintGL()
{
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time_factor = sin(double(timer.elapsed())/300);
    view.setToIdentity();
    view.lookAt({0+time_factor*5, 10+time_factor*10, 10}, {0, 0, 0},  {0, 0, 1});

    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);

    cube->draw(shader);


    update();


}

