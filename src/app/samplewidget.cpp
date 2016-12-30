#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>
#include "../helpers/line.h"

QOpenGLBuffer vbo;
QOpenGLBuffer vbo2;
QOpenGLBuffer vbo_line;
QOpenGLVertexArrayObject vao, vao_line;
static float vertices[] = {
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

static float colors[] = {
    1,1,1,
    1,1,1,
    1,1,1,

    1,1,1,
    1,1,1,
    1,1,1,

    0,0,1,
    0,0,1,
    0,0,1,

    0,1,0,
    0,1,0,
    0,1,0,

    0,1,1,
    1,1,0,
    1,0,1,

    1,0,0,
    1,0,0,
    1,0,0,
};
static const char* vertex = "attribute vec3 input_vertex; attribute vec3 color; varying vec3 oColor; uniform mat4 projection; uniform mat4 view; void main(){oColor = color; gl_Position = projection * view * vec4(input_vertex, 1);}";
static const char* frag = "varying vec3 oColor; void main() {gl_FragColor = vec4(oColor, 1);}";
static const char* vertex_line = "attribute vec2 input_vertex; uniform mat4 projection; uniform mat4 view; void main(){gl_Position = projection * view * vec4(input_vertex, 0, 1);}";
static const char* frag_line = "void main() {gl_FragColor = vec4(1, 1, 1, 1);}";
QOpenGLShaderProgram shader;
QTime timer;
static int sizeOfLine;

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

    /*vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    f->glEnableVertexAttribArray(0);

    vbo2.create();
    vbo2.bind();
    vbo2.allocate(colors, sizeof(colors));
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    f->glEnableVertexAttribArray(1);



    vao.release();*/

    Line line;
    line.pushDot({0,0});
    line.pushDot({1,1});
    line.pushDot({2,0});
    line.pushDot({3,1});
    line.pushDot({4,0});
    *line.cutNthLine(0) += {0, -1};
    auto data = line.toVBO();
    sizeOfLine = data.length()/2;
    qDebug() << data;
    qDebug() << "Length : " << data.length();

    vao_line.create();
    vao_line.bind();

    vbo_line.create();
    vbo_line.bind();
    vbo_line.allocate(data.constData(), data.size()*sizeof(float));
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    f->glEnableVertexAttribArray(0);

    //Init shader;
    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_line);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, frag_line);
    shader.link();
    shader.bind();//*/
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

    float value = sin(double(timer.elapsed())/300);
    view.setToIdentity();
    view.lookAt({0, 10+value*10, 10}, {0, 0, 0},  {0, 0, 1});

    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);

    /*vao.bind();
    //shader.setUniformValue("value", value);

    f->glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/12);*/

    vao.bind();
    f->glDrawArrays(GL_LINE_STRIP, 0, sizeOfLine);



    update();


}

