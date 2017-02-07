#include "opengldialogviewer.h"
#include "ui_opengldialogviewer.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_0>

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
    static QOpenGLFunctions_3_0* functions = ui->openGLWidget->context()->versionFunctions<QOpenGLFunctions_3_0>();

    if (!functions)
        {
            this->ui->polygonModeToggle->hide();
            return;
        }

    ui->openGLWidget->makeCurrent();
    functions->initializeOpenGLFunctions();

    wired = !wired;
    functions->glPolygonMode(GL_FRONT_AND_BACK, wired ? GL_LINE : GL_FILL);
}
