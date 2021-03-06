#ifndef OPENGLDIALOGVIEWER_H
#define OPENGLDIALOGVIEWER_H

#include <QDialog>

namespace Ui {
class OpenGLDialogViewer;
}

class OpenGLDialogViewer : public QDialog
{
    Q_OBJECT

public:
    explicit OpenGLDialogViewer(QWidget *parent = 0);
    ~OpenGLDialogViewer();

private slots:
    void on_polygonModeToggle_clicked();

private:
    Ui::OpenGLDialogViewer *ui;
};

#endif // OPENGLDIALOGVIEWER_H
