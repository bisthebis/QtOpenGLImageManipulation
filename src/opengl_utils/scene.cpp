#include "scene.h"
#include "modelloader.h"
#include "../helpers/file_reading.h"
#include "drawableEntity.h"
#include <QtCore>
#include <QOpenGLWidget>

Scene::Scene(QOpenGLWidget *parent) : QObject(parent), parentWidget(*parent), texture(QOpenGLTexture::Target2D)
{

}

void Scene::init() {
    static bool done = false;
    if (done)
        return;

    context = parentWidget.context();
    f = context->functions();

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

    f->glVertexAttribPointer(shader.attributeLocation("input_vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    f->glEnableVertexAttribArray(shader.attributeLocation("input_vertex"));
    f->glVertexAttribPointer(shader.attributeLocation("UVs"), 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (char*)(3*sizeof(float)));
    f->glEnableVertexAttribArray(shader.attributeLocation("UVs"));

    const auto textureImage = QImage(":/texture.png").mirrored();
    texture.setData(textureImage);
    texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture.setMagnificationFilter(QOpenGLTexture::Linear);

    done = true;
}

void Scene::draw(float timeFactor, const QMatrix4x4 &projection, const QMatrix4x4 &view)
{
    VAO.bind();
    texture.bind();
    shader.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    f->glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);
}
