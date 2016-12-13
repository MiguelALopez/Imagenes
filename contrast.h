#ifndef CONTRAST_H
#define CONTRAST_H

#include <QImage>
#include "conversor.h"

class Contrast
{
public:
    Contrast();

    void gammaCorrection(QImage *image, Conversor::ChannelFilter channel, double rate);
    void histogramEqualization(QImage *image, Conversor::ChannelFilter channel);
    void contrastStretching(QImage *image, Conversor::ChannelFilter channel);
};

#endif // CONTRAST_H
