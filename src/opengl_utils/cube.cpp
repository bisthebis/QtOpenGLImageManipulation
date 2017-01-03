#include "cube.h"

#include <QVector3D>
#include <QOpenGLShaderProgram>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

Cube::Cube()
{
}

Cube::~Cube()
{
    vbo.destroy();
    vao.destroy();
}

void Cube::init()
{
    initializeOpenGLFunctions();

    vbo.create();
    vao.create();

    static const VertexData vertices[] =
    {
        //Superior face then inferior face, red
        {QVector3D(-1, 1, 1), QVector3D(1, 0, 0)},
        {QVector3D(-1, -1, 1), QVector3D(1, 0, 0)},
        {QVector3D(1, 1, 1), QVector3D(1, 0, 0)},
        {QVector3D(1, -1, 1), QVector3D(1, 0, 0)},
        {QVector3D(-1, -1, 1), QVector3D(1, 0, 0)},
        {QVector3D(1, 1, 1), QVector3D(1, 0, 0)},

        {QVector3D(-1, 1, -1), QVector3D(1, 0, 0)},
        {QVector3D(-1, -1, -1), QVector3D(1, 0, 0)},
        {QVector3D(1, 1, -1), QVector3D(1, 0, 0)},
        {QVector3D(1, -1, -1), QVector3D(1, 0, 0)},
        {QVector3D(-1, -1, -1), QVector3D(1, 0, 0)},
        {QVector3D(1, 1, -1), QVector3D(1, 0, 0)},

        //Lateral faces, blue. Constant x
        {QVector3D(-1, 1, 1), QVector3D(0, 0, 1)},
        {QVector3D(-1, -1, 1), QVector3D(0, 0, 1)},
        {QVector3D(-1, 1, -1), QVector3D(0, 0, 1)},
        {QVector3D(-1, -1, -1), QVector3D(0, 0, 1)},
        {QVector3D(-1, -1, 1), QVector3D(0, 0, 1)},
        {QVector3D(-1, 1, -1), QVector3D(0, 0, 1)},

        {QVector3D(1, 1, 1), QVector3D(0, 0, 1)},
        {QVector3D(1, -1, 1), QVector3D(0, 0, 1)},
        {QVector3D(1, 1, -1), QVector3D(0, 0, 1)},
        {QVector3D(1, -1, -1), QVector3D(0, 0, 1)},
        {QVector3D(1, -1, 1), QVector3D(0, 0, 1)},
        {QVector3D(1, 1, -1),QVector3D(0, 0, 1)},

        //Other lateral faces, constant y, gren
        {QVector3D(1, 1, 1), QVector3D(0, 1, 0)},
        {QVector3D(-1, 1, 1), QVector3D(0, 1, 0)},
        {QVector3D(1, 1, -1), QVector3D(0, 1, 0)},
        {QVector3D(-1, 1, -1), QVector3D(0, 1, 0)},
        {QVector3D(-1, 1, 1), QVector3D(0, 1, 0)},
        {QVector3D(1, 1, -1), QVector3D(0, 1, 0)},

        {QVector3D(1, -1, 1), QVector3D(0, 1, 0)},
        {QVector3D(-1, -1, 1), QVector3D(0, 1, 0)},
        {QVector3D(1, -1, -1), QVector3D(0, 1, 0)},
        {QVector3D(-1, -1, -1), QVector3D(0, 1, 0)},
        {QVector3D(-1, -1, 1), QVector3D(0, 1, 0)},
        {QVector3D(1, -1, -1),QVector3D(0, 1, 0)}


    };

    vao.bind();

    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (char*)12);
    glEnableVertexAttribArray(1);

}

void Cube::draw(QOpenGLShaderProgram& program)
{
    program.bind();
    vao.bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);

}
