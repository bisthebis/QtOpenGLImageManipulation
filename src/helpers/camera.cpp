#include "camera.h"
#include <QVector3D>
#include <QMatrix4x4>


Camera::Camera(QObject *parent) : QObject(parent)
{

}

const QMatrix4x4& Camera::matrix() const
{
    return view;
}
void Camera::updateMatrix()
{
    view.lookAt(position, target, {0.0f, 1.0f, 0.0f});
}

void Camera::lookAt(QVector3D pos, QVector3D target)
{
    this->position = pos;
    this->target = target;
    updateMatrix();
}

void Camera::forward(float step)
{
    this->position += step * (target - position).normalized();
    updateMatrix();
}
