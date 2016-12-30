#include "opengldialogviewer.h"
#include "ui_opengldialogviewer.h"

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
