#include "threshold.h"

Threshold::Threshold()
{

}

int Threshold::otsu(int total, int histogram[]){
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

    return threshold;
}

void Threshold::otsuGlobalThreshold(QImage *image){
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

    // Total number of pixels
    int total = image->height() * image->width();

    int threshold = otsu(total, histogram);

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

void Threshold::manualThreshold(QImage *image, int threshold){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int pixel = 0;
            if(QColor(image->pixel(i, j)).red() > threshold){
                pixel = 255;
            }
            image->setPixel(i, j, qRgb(pixel, pixel, pixel));
        }
    }
}

void Threshold::triangleThreshold(QImage *image){
    int threshold = triangleThresholdAux(image);
    std::cout << threshold << std::endl;
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int pixel = 0;
            if(QColor(image->pixel(i, j)).red() > threshold){
                pixel = 255;
            }
            image->setPixel(i, j, qRgb(pixel, pixel, pixel));
        }
    }
}

int Threshold::triangleThresholdAux(QImage *image){
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
            //            if (QColor(image->pixel(i, j)).red()  > tiki){
            histogram[QColor(image->pixel(i, j)).red()]++;
            //            }
        }
    }

    int min = 0;
    int dmax = 0;
    int max = 0;
    int min2 = 0;
    for(int i = 0; i < 256; i++){
        if (histogram[i] > 0){
            min = i;
            break;
        }
    }

    if(min > 0){
        min--;
    }

    for (int i = 255; i > 0; i--){
        if(histogram[i] > 0){
            min2 = i;
            break;
        }
    }

    if (min2 < 255) min2++;

    for(int i=0; i < 256; i++){
        if (histogram[i] > dmax){
            max = i;
            dmax = histogram[i];
        }
    }

    bool inverted = false;
    if((max-min)<(min2-max)){
        inverted = true;
        int left = 0;
        int right = 255;
        while(left < right){
            int temp = histogram[left];
            histogram[left] = histogram[right];
            histogram[right] = temp;

            left++;
            right--;
        }
        min = 255 - min2;
        max = 256 - max;
    }

    if(min == max){
        return min;
    }

    double nx, ny, d;
    nx = histogram[max];   //-min; // data[min]; //  lowest value bmin = (p=0)% in the image
    ny = min - max;
    d = sqrt(nx * nx + ny * ny);
    nx /= d;
    ny /= d;
    d = nx * min + ny * histogram[min];

    // find split point
    int split = min;
    double splitDistance = 0;
    for (int i = min + 1; i <= max; i++) {
        double newDistance = nx * i + ny * histogram[i] - d;
        if (newDistance > splitDistance) {
            split = i;
            splitDistance = newDistance;
        }
    }
    split--;

    if (inverted) {
        // The histogram might be used for something else, so let's reverse it back
        int left  = 0;
        int right = 255;
        while (left < right) {
            int temp = histogram[left];
            histogram[left]  = histogram[right];
            histogram[right] = temp;
            left++;
            right--;
        }
        return (255-split);
    }
    else
        return split;
}

void Threshold::meanLocalThreshold(QImage *image, int window){
    QImage resultImage = *image;
//    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = image->width();
    int h = image->height();
//    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
    int middle = (window / 2);

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int max = 0;
            int min = 255;

            for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    if(QColor(image->pixel(i - middle + x, j - middle + y)).red() > max){
                        max = QColor(image->pixel(i - middle + x, j - middle + y)).red();
                    }

                    if(QColor(image->pixel(i - middle + x, j - middle + y)).red() < min){
                        min = QColor(image->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
            }
            int pixel = 0;
            int threshold = (max + min) / 2;
            if(QColor(image->pixel(i, j)).red() < threshold){
                pixel = 255;
            }
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *image = resultImage;
}

void Threshold::otsuLocalThreshold(QImage *image, int window){
    QImage resultImage = *image;

    int w = image->width();
    int h = image->height();
//    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
    int middle = (window / 2);

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){

            int histogram[256];

            // Se inicializa el arreglo en 0
            for(int i = 0; i < 256; i++){
                histogram[i] = 0;
            }

            for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    histogram[QColor(image->pixel(i - middle + x, j - middle + y)).red()]++;

                }
            }
            int pixel = 0;
            int total = window * window;
            int threshold = otsu(total, histogram);
            if(QColor(image->pixel(i, j)).red() < threshold){
                pixel = 255;
            }
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *image = resultImage;
}
