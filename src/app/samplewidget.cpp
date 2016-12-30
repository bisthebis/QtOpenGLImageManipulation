#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>

QOpenGLBuffer vbo;
QOpenGLVertexArrayObject vao;
float vertices[] = {
    -1, -1, -1,
    1, -1, -1,
    -1, 1, -1,

    1, 1, -1,
    -1, 1, -1,
    1, -1, -1,

    0, 0, 1,
    -1, -1, -1,
    1, -1, -1,

    0, 0, 1,
    1, -1, -1,
    1, 1, -1,

    0, 0, 1,
    1, 1, -1,
    -1, 1, -1,

    0, 0, 1,
    -1, 1, -1,
    -1, -1, -1

};
static const char* vertex = "attribute vec3 input_vertex; uniform mat4 projection; uniform mat4 view; void main(){gl_Position = projection * view * vec4(input_vertex, 1);}";
static const char* frag = "uniform float blue; void main() {gl_FragColor = vec4(1, 1, blue, 1);}";
QOpenGLShaderProgram shader;
QTime timer;

SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) : QOpenGLWidget(parent, f)
{
    timer.start();
    view.setToIdentity();
    view.lookAt({10, 10, 10}, {0, 0, 0},  {0, 0, 1});
}
SampleWidget::~SampleWidget()
{
}

void SampleWidget::initializeGL()
{
    setUpdatesEnabled(true);
    static QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
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

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    f->glEnableVertexAttribArray(0);

    vao.release();

    //Init shader;
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
    //qDebug() << "Drawing widget";
    static QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao.bind();
    float value = 0.5 * (1 + sin(double(timer.elapsed())/300));
    shader.setUniformValue("blue", value);
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    qDebug() << "sizeof(vertices)/12 == " << sizeof(vertices)/12;
    f->glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/12);
    update();


}

