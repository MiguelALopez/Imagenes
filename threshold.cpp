#include "threshold.h"

Threshold::Threshold()
{

}

void Threshold::otsuThreshold(QImage *image, Conversor::ChannelFilter channel){
    int histogram[256];
    int w = image->width();
    int h = image->height();

    // Se inicializa el arreglo en 0
    for(int i = 0; i < 256; i++){
        histogram[i] = 0;
    }

    // Se llena el histograma con los valores correspondientes
    for(int i = 0; i < w ; i++){
        for(int j = 0; j < h; j++){
//            if (QColor(image->pixel(i, j)).red() != 0 && QColor(image->pixel(i, j)).red() != 1 &&
//                    QColor(image->pixel(i, j)).red() != 2){
                histogram[QColor(image->pixel(i, j)).red()]++;
//            }
        }
    }

    // Total numver of pixels
    int total = image->height() * image->width();

    double sum = 0;
    for(int i = 0; i < 256; i++){
        sum += i * histogram[i];
    }

    double sumB = 0;
    int wB = 0;
    int wF = 0;

    double varMax = 0;
    int threshold = 0;

    for(int i = 0; i < 256; i++){
        wB += histogram[i];
        if(wB == 0){
            continue;
        }

        wF = total - wB;
        if(wF == 0){
            break;
        }

        sumB += (double)(i * histogram[i]);

        double mB = sumB / wB;          // Mean Background
        double mF = (sum - sumB) / wF;  // Mean Foreground

        // Calculate Between Class Variance
        double varBetween = (double)wB * (double)wF * (mB - mF) * (mB - mF);

        // Check if new maximun found
        if (varBetween > varMax){
            varMax = varBetween;
            threshold = i;
        }

    }

    for(int i = 0; i < w ; i++){
        for(int j = 0; j < h; j++){
            int pixel;
            if(QColor(image->pixel(i,j)).red() < threshold){
                pixel = 0;
            }else{
                pixel = 255;
            }

            image->setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }


}
