#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTime>
#include "../opengl_utils/cube.h"
#include "../opengl_utils/modelloader.h"
#include "../opengl_utils/scene.h"

class QOpenGLTexture;

class SampleWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    SampleWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~SampleWidget();

protected:
    virtual void paintGL() Q_DECL_OVERRIDE;
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;

private:
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QTime timer;
    QOpenGLShaderProgram shader;
    QOpenGLTexture texture;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    Scene scene;
    int cubeVerticesCount;

};

#endif // SAMPLEWIDGET_H
