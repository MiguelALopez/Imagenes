#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <QImage>
#include <iostream>
#include "conversor.h"

class Threshold
{
public:
    Threshold();

    int otsu(int total, int histogram[256]);
    void otsuGlobalThreshold(QImage *image);
    void manualThreshold(QImage *image, int threshold);
    void triangleThreshold(QImage *image);
    int triangleThresholdAux(QImage *image);
    void meanLocalThreshold(QImage *image, int window);
    void otsuLocalThreshold(QImage * image, int window);
};

#endif // THRESHOLD_H
