#include "samplewidget.h"
#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtGui>
#include <QtCore>


SampleWidget::SampleWidget(QWidget *parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f),
    scene(this),
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

    //All drawable objects lie here.
    scene.init();

    auto context = QOpenGLContext::currentContext();
    qDebug() << QString("OpenGL Informations : GLES ? %0. Major version : %1. Minor version : %2")
                .arg
                (context->isOpenGLES() ? 'y' : 'n')
                .arg
                (context->format().version().first)
                .arg(context->format().version().second);
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

    scene.draw(time_factor, projection, view);

    update();


}

