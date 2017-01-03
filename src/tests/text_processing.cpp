#include "catch.hpp"

#include <QtCore>

TEST_CASE("Qt Line processing","[parsing]")
{
    static const QStringList expected = {"Hello ", "World !"};
    static QString input = "Hello \nWorld !";

    QStringList result;

    QTextStream stream(&input);
    QString line;
    while (true) {
        line = stream.readLine();
        if (line.isEmpty())
            break;
        result << line;
    }

    CHECK(result == expected);
    if (result != expected)
    {
        qDebug() << "Unexpected string cutting : ";
        qDebug() << expected;
        qDebug() << result;
    }

}
