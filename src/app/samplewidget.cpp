#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>

QOpenGLBuffer vbo;
QOpenGLVertexArrayObject vao;
static float vertices[] = {0, 0.5,  0.5, -0.5, -0.5, -0.5};
QOpenGLShaderProgram shader;
QTime timer;

SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) : QOpenGLWidget(parent, f)
{
    timer.start();
}
SampleWidget::~SampleWidget()
{
}

void SampleWidget::initializeGL()
{
    setUpdatesEnabled(true);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0, 0.5, 1, 1);
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

    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    f->glEnableVertexAttribArray(0);

    vao.release();

    //Init shader;
    static const char* vertex = "attribute vec2 input_vertex; uniform mat4 projection; void main(){gl_Position = projection * vec4(input_vertex, 1.5, 1);}";
    static const char* frag = "uniform float blue; void main() {gl_FragColor = vec4(1, 1, blue, 1);}";
    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, frag);
    shader.link();
    shader.bind();
}
void SampleWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    //projection.frustum(-1 * ratio, 1 * ratio,  -1, 1, -1, 1);
    projection.setToIdentity();
    projection.perspective(45.0f, ratio, 0, 100);
    //projection = projection.transposed();
    qDebug() << projection;
    QVector4D result = projection * QVector4D(0,0.5,1.5,1);
    qDebug() << result / result.w();
}

void SampleWidget::paintGL()
{
    //qDebug() << "Drawing widget";
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT);

    vao.bind();
    float value = 0.5 * (1 + sin(double(timer.elapsed())/300));
    shader.setUniformValue("blue", value);
    shader.setUniformValue("projection", projection);
    f->glDrawArrays(GL_TRIANGLES, 0, 3);
    update();


}

