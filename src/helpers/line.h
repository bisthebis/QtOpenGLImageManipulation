#ifndef LINE_H
#define LINE_H

#include <QLinkedList>
#include <QVector2D>
#include <QVector>


class Line
{
public:
    Line();
    void pushDot(const QVector2D& dot);
    QVector<float> toVBO(); // format is x1, y1, x2, y2...
    auto cutNthLine(int n) -> QLinkedList<QVector2D>::iterator;

private:
    QLinkedList<QVector2D> dots;

};

#endif // LINE_H
