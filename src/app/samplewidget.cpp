#include "samplewidget.h"
#include <QDebug>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>
#include "../helpers/line.h"
#include "../opengl_utils/cube.h"
#include "../helpers/file_reading.h"


SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f),
    texture(QOpenGLTexture::Target2D)
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
    initializeOpenGLFunctions();
    setUpdatesEnabled(true);
    glClearColor(0, 0.5, 1, 1);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    auto context = QOpenGLContext::currentContext();
    qDebug() << QString("OpenGL Informations : GLES ? %0. Major version : %1. Minor version : %2")
                .arg
                (context->isOpenGLES() ? 'y' : 'n')
                .arg
                (context->format().version().first)
                .arg(context->format().version().second);

    ModelLoader loader;
    loader.loadFile(":/cube.obj");
    auto data = loader.toVBO(ModelLoader::VerticesThenUVs);
    cubeVerticesCount = data.size() / 5;
    VAO.create();
    VAO.bind();

    QStringList vertSource = readFile(":/shaders/3d_plain_textured.vert");
    QStringList fragSource = readFile(":/shaders/3d_plain_textured.frag");

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertSource.join("\n"));
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragSource.join("\n"));
    shader.link();
    shader.bind();
    {
        QString log = shader.log();
        if (!log.isEmpty())
            qDebug() << "Shader log : " << shader.log();
    }


    VBO.create();
    VBO.bind();
    VBO.allocate(data.data(), data.size()*sizeof(float));

    glVertexAttribPointer(shader.attributeLocation("input_vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(shader.attributeLocation("input_vertex"));
    glVertexAttribPointer(shader.attributeLocation("UVs"), 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (char*)(3*sizeof(float)));
    glEnableVertexAttribArray(shader.attributeLocation("UVs"));

    const auto textureImage = QImage(":/texture.png").mirrored();
    texture.setData(textureImage);
    texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture.setMagnificationFilter(QOpenGLTexture::Linear);



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

    VAO.bind();
    texture.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);


    update();


}

