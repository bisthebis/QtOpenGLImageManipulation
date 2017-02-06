#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QTime>
#include "../opengl_utils/cube.h"
#include "../opengl_utils/modelloader.h"

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
    Cube cube;
    QTime timer;
    QOpenGLShaderProgram shader;
    QOpenGLTexture texture;

};

#endif // SAMPLEWIDGET_H
