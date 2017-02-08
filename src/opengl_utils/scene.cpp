#include "scene.h"
#include "modelloader.h"
#include "../helpers/file_reading.h"
#include "drawableEntity.h"
#include <QtCore>
#include <QOpenGLWidget>

Scene::Scene(QOpenGLWidget *parent) : QObject(parent), parentWidget(*parent), texture(QOpenGLTexture::Target2D)
{

}

void Scene::init() {
    static bool done = false;
    if (done)
        return;

    context = parentWidget.context();
    f = context->functions();

    entities["Cube"] = new DrawableEntity(this);
    entities["Cube"]->load(":/cube.obj", ":/texture.png", ":/shaders/3d_plain_textured.vert", ":/shaders/3d_plain_textured.frag", *f);

    done = true;
}

void Scene::draw(float timeFactor, const QMatrix4x4 &projection, const QMatrix4x4 &view)
{
    for (auto item : entities)
        item->draw(timeFactor, projection, view, *f);
}
