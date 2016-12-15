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
    void manualThreshold(QImage *image, int threshold1, int threshold2);
    int triangleThreshold(QImage *image, int tiki);
    void localThreshold(QImage *image);
};

#endif // THRESHOLD_H
