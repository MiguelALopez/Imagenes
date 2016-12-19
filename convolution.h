#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include<QImage>

class Convolution
{
public:
    Convolution();

    void averageFilter(QImage *imageOriginal, int window);
    void minimumFilter(QImage *imageOriginal, int window);
    void maximumFilter(QImage *imageOriginal, int window);
    void middleFilter(QImage *imageOriginal, int window);
    void gaussianFilterx3(QImage *imageOriginal);
    void gaussianFilterx5(QImage *imageOriginal);
    void gaussianFilterx7(QImage *imageOriginal);
    void nagaoFilter(QImage *imageOriginal);
private:

};

#endif // CONVOLUTION_H
