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

    return result;
}

QLinkedList<QVector2D>::iterator Line::cutNthLine(int n)
{
        Q_ASSERT(n <= dots.size() - 2);
        auto it = dots.begin();
        while (n > 0)
        {
            ++it;
            --n;
        }
        QVector2D newDot = (1./2.) * (*it + *(it+1));

        return dots.insert(it+1, newDot);

}
