#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>

#include <QMatrix4x4>
#include <QVector3D>

class Camera : public QObject
{
    Q_OBJECT
    public:
        explicit Camera(QObject *parent = 0);
        const QMatrix4x4& matrix() const;

    signals:
        void moved();

    public slots:
        void lookAt(QVector3D pos, QVector3D target);
        void forward(float step = 1.0f);

    private:
        QMatrix4x4 view;
        QVector3D position;
        QVector3D target;

        void updateMatrix();
};

#endif // CAMERA_H
