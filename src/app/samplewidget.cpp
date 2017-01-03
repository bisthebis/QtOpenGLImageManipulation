#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>
#include "../helpers/line.h"
#include "../opengl_utils/cube.h"

static const char* vertex = "#version 330 \n"
                            "in vec3 input_vertex;"
                            "in vec2 uvs;"
                            "out vec2 oUVs;"
                            "uniform mat4 projection;"
                            "uniform mat4 view;"
                            "void main() {"
                            "   oUVs = uvs;"
                            "   gl_Position = projection * view * vec4(input_vertex, 1);"
                            "}";

static const char* frag = "#version 330 \n"
                          "uniform  sampler2D DiffTexture; \n"
                          "in vec2 oUVs; \n"
                          "out vec4 color; \n"
                          "void main() {color = texture(DiffTexture, oUVs);}";
QOpenGLBuffer VBO;
QOpenGLVertexArrayObject VAO;
QOpenGLTexture* texture;

SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f)
{
    timer.start();
    view.setToIdentity();
    view.lookAt({10, 10, 10}, {0, 0, 0},  {0, 0, 1});
}
SampleWidget::~SampleWidget()
{
    delete texture;
}

void SampleWidget::initializeGL()
{
    initializeOpenGLFunctions();
    setUpdatesEnabled(true);
    glClearColor(0, 0.5, 1, 1);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    auto context = QOpenGLContext::currentContext();
    qDebug() << QString("OpenGL Informations : GLES ? %0. Major version : %1. Minor version : %2")
                .arg
                (context->isOpenGLES())
                .arg
                (context->format().version().first)
                .arg(context->format().version().second);

    ModelLoader loader;
    loader.loadFile("cube.obj");
    auto data = loader.toVBO(ModelLoader::VerticesThenUVs);
    VAO.create();
    VAO.bind();

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, frag);
    shader.link();
    shader.bind();
    qDebug() << "Shader log : " << shader.log();

    VBO.create();
    VBO.bind();
    qDebug() << data;
    VBO.allocate(data.data(), data.size()*sizeof(float));

    glVertexAttribPointer(shader.attributeLocation("input_vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(shader.attributeLocation("input_vertex"));
    glVertexAttribPointer(shader.attributeLocation("uvs"), 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (char*)(3*sizeof(float)));
    glEnableVertexAttribArray(shader.attributeLocation("uvs"));

    texture = new QOpenGLTexture(QImage("texture.png").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    /*cube.init();

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, frag);
    shader.link();
    shader.bind();*/


}
void SampleWidget::resizeGL(int w, int h)
{
    float ratio = float(w) / float(h);
    projection.setToIdentity();
    projection.perspective(45, ratio, 0.1, 100);
}

void SampleWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time_factor = sin(double(timer.elapsed())/300);
    view.setToIdentity();
    view.lookAt({0+time_factor*5, 10+time_factor*10, 10}, {0, 0, 0},  {0, 0, 1});

    /*shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);

    cube.draw(shader);*/
    VAO.bind();
    texture->bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    update();


}

