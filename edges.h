#ifndef EDGES_H
#define EDGES_H

#include <QImage>

class Edges
{
public:
    Edges();

    void sobelOperator(QImage *image, int threshold);
};

#endif // EDGES_H
