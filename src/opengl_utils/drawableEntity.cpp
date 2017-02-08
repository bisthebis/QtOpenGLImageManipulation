#include "drawableEntity.h"
#include "modelloader.h"
#include "../helpers/file_reading.h"

DrawableEntity::DrawableEntity(Scene *parent) : QObject(parent), texture(QOpenGLTexture::Target2D)
{

}

void DrawableEntity::load(QString model,
                          QString texturePath,
                          QString vertexShaderPath,
                          QString fragmentShaderPath,
                          QOpenGLFunctions& f)
{
    auto loader = ModelLoader();
    loader.loadFile(model);

    auto data = loader.toVBO(ModelLoader::VerticesThenUVs);
    vertexCount = data.size() / 5;

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();
    VBO.allocate(data.data(), data.size() * sizeof(float));

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, readFile(vertexShaderPath).join("\n"));
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, readFile(fragmentShaderPath).join("\n"));
    shader.link();
    shader.bind();
    {
        QString log = shader.log();
        if (!log.isEmpty())
            qDebug() << "Shader log : " << shader.log();
    }

    f.glVertexAttribPointer(shader.attributeLocation("input_vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    f.glEnableVertexAttribArray(shader.attributeLocation("input_vertex"));
    f.glVertexAttribPointer(shader.attributeLocation("UVs"), 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (char*)(3*sizeof(float)));
    f.glEnableVertexAttribArray(shader.attributeLocation("UVs"));

    const auto textureImage = QImage(texturePath).mirrored();
    texture.setData(textureImage);
    texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture.setMagnificationFilter(QOpenGLTexture::Linear);


}

void DrawableEntity::draw(float timeFactor, const QMatrix4x4 &projection, const QMatrix4x4 &view, QOpenGLFunctions& f)
{
    VAO.bind();
    texture.bind();
    shader.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    f.glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
