#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <QImage>
#include <iostream>
#include "conversor.h"

class Threshold
{
public:
    Threshold();

    void otsuThreshold(QImage *image, Conversor::ChannelFilter channel);
};

#endif // THRESHOLD_H
