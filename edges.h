#ifndef EDGES_H
#define EDGES_H

#include <QImage>
#include "conversor.h"

class Edges
{
public:
    Edges();

    void sobelOperator(QImage *image, int threshold, Conversor::ChannelFilter channel);
};

#endif // EDGES_H
