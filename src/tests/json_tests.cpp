#include "catch.hpp"

#include <QtCore>

TEST_CASE("Qt JSON samples","[json]")
{
    static QByteArray json = "{ \"files\" : ["
                             "{\"name\" : \"John\"},"
                             "{\"name\" : \"Paul\"}"
                             "]}";


    QJsonDocument doc = QJsonDocument::fromJson(json);;
    CHECK(doc.object().find("files") != doc.object().end());
    CHECK(doc.object().find("files")->isArray());
    auto array = doc.object()["files"];
    CHECK(array.toArray().size() == 2);
    CHECK(array.toArray().first().isObject());
    CHECK(array.toArray().first().toObject().value("name").toString() == "John");
    CHECK(array.toArray().at(1).toObject().value("name").toString() == "Paul");

}
