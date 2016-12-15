#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <QImage>
#include "conversor.h"

class ColorSpace
{
public:
    ColorSpace();

    void convertToGrayscale(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToHSV(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToHSL(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToOpponet(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToCMY(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToInverted(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
    void convertToRGB(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB);
};

#endif // COLORSPACE_H
