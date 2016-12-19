#include "morphologicaloperators.h"

MorphologicalOperators::MorphologicalOperators()
{

}

void MorphologicalOperators::dilate(QImage *image){
    QImage resultImage = *image;
    int commonFilter[3][3] = {{0,1,0},{1,1,1},{0,1,0}};
    int w = image->width();
    int h = image->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 255;

            int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    if (commonFilter[x][y] == 1 &&
                            QColor(image->pixel(i - middle + x, j - middle + y)).red() != 255){
                        pixel = 0;
                    }
                }
            }
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }
    }

    // Save the result
    *image = resultImage;
}

void MorphologicalOperators::erosion(QImage *image){
    QImage resultImage = *image;
    int commonFilter[3][3] = {{0,1,0},{1,1,1},{0,1,0}};
    int w = image->width();
    int h = image->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 0;

            int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    if (commonFilter[x][y] == 0 &&
                            QColor(image->pixel(i - middle + x, j - middle + y)).red() != 0){
                        pixel = 255;
                    }
                }
            }
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *image = resultImage;

}
