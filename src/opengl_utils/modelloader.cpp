#include "modelloader.h"
#include <QUrl>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QDebug>


//Utility functions
static QStringList readFile(const QString& path);
static const QRegularExpression space_split("\\s+");

ModelLoader::ModelLoader()
{
}

void ModelLoader::loadFile(const QString &path)
{
    QStringList lines = readFile(path);

    for (QString line : lines)
    {
        if (line.startsWith("v") && !line.startsWith("vt") && !line.startsWith("vn"))
        {
            //It is a vertex position description
            QStringList words = line.split(space_split);
            bool OK = true;
            //words[0] is "v"
            float x = words[1].toFloat(&OK);
            float y = words[2].toFloat(&OK);
            float z = words[3].toFloat(&OK);
            if (!OK)
                qApp->exit(-1);

            vertices.append(QVector3D(x, y, z));
        }
        else if (line.startsWith("vn"))
        {
            //It is a normal position description
            QStringList words = line.split(space_split);
            bool OK = true;
            //words[0] is "v"
            float x = words[1].toFloat(&OK);
            float y = words[2].toFloat(&OK);
            float z = words[3].toFloat(&OK);
            if (!OK)
                qApp->exit(-1);

            normals.append(QVector3D(x, y, z));
        }
        else if (line.startsWith("vt"))
        {
            //It is a textures coordinates description
            QStringList words = line.split(space_split);
            bool OK = true;
            //words[0] is "v"
            float x = words[1].toFloat(&OK);
            float y = words[2].toFloat(&OK);
            if (!OK)
                qApp->exit(-1);

            texturesCoordinates.append(QVector2D(x, y));
        }
        else if (line.startsWith("f"))
        {
            //It's a face
            line.replace('/', ' ');
            auto values = line.split(space_split);
            //values[0] is "f"
            bool OK = true;
            int v1 = values[1].toInt(&OK);
            int vt1 = values[2].toInt(&OK);
            int vn1 = values[3].toInt(&OK);

            int v2 = values[4].toInt(&OK);
            int vt2 = values[5].toInt(&OK);
            int vn2 = values[6].toInt(&OK);

            int v3 = values[7].toInt(&OK);
            int vt3 = values[8].toInt(&OK);
            int vn3 = values[9].toInt(&OK);

            if (!OK)
                qApp->exit(-1);


            Vertex verticesToAdd[3] = {
                {vertices[v1], texturesCoordinates[vt1], normals[vn1]},
                {vertices[v2], texturesCoordinates[vt2], normals[vn2]},
                {vertices[v3], texturesCoordinates[vt3], normals[vn3]}
            };
            triangles.append({verticesToAdd[0], verticesToAdd[1], verticesToAdd[2]});

        }
    }


}

QVector<float> ModelLoader::toVBO(ModelLoader::ExportCategory type)
{
    QVector<float> result;
    if (type == ExportCategory::VerticesThenUVs)
    {
        for (const Triangle& triangle : triangles)
        {
            for (const Vertex& vertex : triangle.vertices)
            {
                result.append(vertex.pos.x());
                result.append(vertex.pos.y());
                result.append(vertex.pos.z());
                result.append(vertex.uvs.x());
                result.append(vertex.uvs.y());
            }
        }
    }

    return result;
}

static QStringList readFile(const QString &path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    if (!file.isOpen())
    {
        qDebug() << "FAILED TO OPEN FILE. Path is : " << path;
        qApp->exit(1);
    }

    QTextStream stream(&file);
    QStringList lines;
    while (true) {
        QString line = stream.readLine();
        if (line.isEmpty())
            break;
        lines << line;
    }

    file.close();
    return lines;
}
