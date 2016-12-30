#include <QtCore>
#include <QApplication>
#include <QWidget>
#include "opengldialogviewer.h"

int main(int argc, char** argv)
    {
        QApplication app(argc, argv);

        OpenGLDialogViewer window;
        window.show();

        return app.exec();

    }
