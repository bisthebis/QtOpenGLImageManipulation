#include "opengldialogviewer.h"
#include "ui_opengldialogviewer.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>

OpenGLDialogViewer::OpenGLDialogViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenGLDialogViewer)
{
    ui->setupUi(this);
}

OpenGLDialogViewer::~OpenGLDialogViewer()
{
    delete ui;
}

void OpenGLDialogViewer::on_polygonModeToggle_clicked()
{
    static bool wired = false;
    static QOpenGLFunctions_3_3_Core* functions = ui->openGLWidget->context()->versionFunctions<QOpenGLFunctions_3_3_Core>();

    ui->openGLWidget->makeCurrent();
    functions->initializeOpenGLFunctions();

    if (!functions)
        return;
    wired = !wired;
    functions->glPolygonMode(GL_FRONT_AND_BACK, wired ? GL_LINE : GL_FILL);
}
