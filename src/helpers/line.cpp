#include "line.h"
#include <QVector>

Line::Line()
{

}

void Line::pushDot(const QVector2D &dot)
{
    dots.append(dot);
}

QVector<float> Line::toVBO()
{
    QVector<float> result;
    result.reserve(2*dots.size());
    for (const auto dot : dots)
    {
        result.append(dot.x());
        result.append(dot.y());
    }

}
