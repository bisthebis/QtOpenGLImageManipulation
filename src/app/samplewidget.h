#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>

class SampleWidget : public QOpenGLWidget
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
};

#endif // SAMPLEWIDGET_H
