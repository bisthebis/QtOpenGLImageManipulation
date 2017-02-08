#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QString>
#include "scene.h"

class DrawableEntity : public QObject
{
    Q_OBJECT
public:
    explicit DrawableEntity(Scene *parent = 0);
    void load(QString model, QString texture, QString vertexShaderPath, QString fragmentShaderPath, QOpenGLFunctions& f);

signals:

public slots:
    void draw(float timeFactor, const QMatrix4x4& projection, const QMatrix4x4& view, QOpenGLFunctions& f);

private:
    QOpenGLShaderProgram shader;
    QOpenGLTexture texture;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    int vertexCount;
};

#endif // OBJECT_H
