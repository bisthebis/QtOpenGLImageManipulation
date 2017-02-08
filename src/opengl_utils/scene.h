#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QMap>
#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QOpenGLWidget *parent = 0);
    void init();

signals:

public slots:
  void draw(float timeFactor, const QMatrix4x4& projection, const QMatrix4x4& view);
private:
  QOpenGLWidget& parentWidget;
  QOpenGLShaderProgram shader;
  QOpenGLTexture texture;
  QOpenGLBuffer VBO;
  QOpenGLVertexArrayObject VAO;
  int cubeVerticesCount;
  QOpenGLContext* context;
  QOpenGLFunctions* f;


};

#endif // SCENE_H
