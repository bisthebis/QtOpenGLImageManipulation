#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLShaderProgram;

class Cube : public QOpenGLFunctions
{
public:
    Cube();
    virtual ~Cube();
    void init();

    void draw(QOpenGLShaderProgram&);

private:

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
};

#endif // CUBE_H
