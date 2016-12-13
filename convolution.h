#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include<QImage>
#include "conversor.h"

class Convolution
{
public:
    Convolution();

    void averageFilter(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void minimumFilter(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void maximumFilter(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void middleFilter(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void gaussianFilterx3(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void gaussianFilterx5(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
    void nagaoFilter(QImage *imageOriginal , QImage *imageResult, Conversor::ChannelFilter channel);
private:

};

#endif // CONVOLUTION_H
