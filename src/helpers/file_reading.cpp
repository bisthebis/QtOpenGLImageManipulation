#include "file_reading.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>

QStringList readFile(const QString &path)
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
