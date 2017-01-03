#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <QFile>
#include <QVector>
#include <QVector3D>
#include <QVector2D>

class ModelLoader
{
public:
    ModelLoader();
    void loadFile(const QString& path);

    enum ExportCategory {VerticesThenUVs};
    QVector<float> toVBO(ExportCategory type);

    struct Vertex {
        QVector3D pos;
        QVector2D uvs;
        QVector3D normals;
    };

    struct Triangle {
        Vertex vertices[3];
    };



private:
    // "Padding" because in file, indexes start with 1 instead of 0.
    QVector<QVector3D> vertices = {QVector3D(0,0,0)};
    QVector<QVector3D> normals = {QVector3D(0,0,0)};
    QVector<QVector2D> texturesCoordinates = {QVector2D(0,0)};
    QVector<Triangle> triangles;
};

#endif // MODELLOADER_H
