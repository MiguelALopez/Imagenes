#include "convolution.h"

Convolution::Convolution()
{

}

void Convolution::averageFilter(QImage *imageOriginal, int window){
    QImage resultImage = *imageOriginal;
    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (window / 2);

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 0;

           for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                }
            }
            pixel = pixel / (window * window); // Se saca el promedio de todos los pixeles
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::minimumFilter(QImage *imageOriginal, int window){
    QImage resultImage = *imageOriginal;

    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (window / 2);

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int min = 255;

            for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() < min){
                        min = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
            }
            resultImage.setPixel(i, j, qRgb(min, min, min));
        }
    }

    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::maximumFilter(QImage *imageOriginal, int window){
    QImage resultImage = *imageOriginal;
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (window / 2);

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int max = 0;

            for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() > max){
                        max = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
            }
            resultImage.setPixel(i, j, qRgb(max, max, max));
        }
    }

    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::middleFilter(QImage *imageOriginal, int window){
    QImage resultImage = *imageOriginal;

    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (window / 2);


    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 0;

            QList<int> list;

            for(int x = 0; x < window; x++){
                for(int y = 0; y < window; y++){
                    list << QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                }
            }
            qSort(list.begin(), list.end());

            pixel = list.at(list.length() / 2);

            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::gaussianFilterx3(QImage *imageOriginal){
    QImage resultImage = *imageOriginal;
    int commonFilter[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 0;

            int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                }
            }
            pixel = pixel / 16;

            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::gaussianFilterx5(QImage *imageOriginal){
    QImage resultImage = *imageOriginal;
    int commonFilter[5][5] = {{1, 4, 7, 4, 1},{4, 16, 26, 16, 4},{7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            int pixel = 0;

            int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                }
            }
            pixel = pixel / 273;

            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }
    }


    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::gaussianFilterx7(QImage *imageOriginal){
    QImage resultImage = *imageOriginal;
    double commonFilter[7][7] = {{0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036},
                              {0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363},
                              {0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446},
                              {0.002291, 0.023226, 0.092651, 0.146768, 0.092651, 0.023226, 0.002291},
                              {0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446},
                              {0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363},
                              {0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    for(int i = middle; i < w - middle; i++){
        for(int j = middle; j < h - middle; j++){
            double pixel = 0;

            int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    pixel += (double)QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                }
            }
//            pixel = pixel / 273;

            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }
    }


    // Save the result
    *imageOriginal = resultImage;
}

void Convolution::nagaoFilter(QImage *imageOriginal){
    QImage resultImage = *imageOriginal;
    int nagaoW[5][5] = {{1,0,0,0,0},
                        {1,1,0,0,0},
                        {1,1,1,0,0},
                        {1,1,0,0,0},
                        {1,0,0,0,0}};

    int nagaoNW[5][5] = {{1,1,1,0,0},
                         {1,1,1,0,0},
                         {1,1,1,0,0},
                         {0,0,0,0,0},
                         {0,0,0,0,0}};

    int nagaoN[5][5] = {{1,1,1,1,1},
                        {0,1,1,1,0},
                        {0,0,1,0,0},
                        {0,0,0,0,0},
                        {0,0,0,0,0}};

    int nagaoNE[5][5] = {{0,0,1,1,1},
                         {0,0,1,1,1},
                         {0,0,1,1,1},
                         {0,0,0,0,0},
                         {0,0,0,0,0}};

    int nagaoE[5][5] = {{0,0,0,0,1},
                        {0,0,0,1,1},
                        {0,0,1,1,1},
                        {0,0,0,1,1},
                        {0,0,0,0,1}};

    int nagaoSE[5][5] = {{0,0,0,0,0},
                         {0,0,0,0,0},
                         {0,0,1,1,1},
                         {0,0,1,1,1},
                         {0,0,1,1,1}};

    int nagaoS[5][5] = {{0,0,0,0,0},
                        {0,0,0,0,0},
                        {0,0,1,0,0},
                        {0,1,1,1,0},
                        {1,1,1,1,1}};

    int nagaoSW[5][5] = {{0,0,0,0,0},
                         {0,0,0,0,0},
                         {1,1,1,0,0},
                         {1,1,1,0,0},
                         {1,1,1,0,0}};

    int nagaoC[5][5] = {{0,0,0,0,0},
                        {0,1,1,1,0},
                        {0,1,1,1,0},
                        {0,1,1,1,0},
                        {0,0,0,0,0}};



    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middleNagao = (sizeof(nagaoC) / sizeof(*nagaoC)) / 2;


    for(int i = middleNagao; i < w - middleNagao; i++){
        for(int j = middleNagao; j < h - middleNagao; j++){

            int pixelW = 0; int pixelAverW = 0;
            int pixelNW = 0; int pixelAverNW = 0;
            int pixelN = 0; int pixelAverN = 0;
            int pixelNE = 0; int pixelAverNE = 0;
            int pixelE = 0; int pixelAverE = 0;
            int pixelSE = 0; int pixelAverSE = 0;
            int pixelS = 0; int pixelAverS = 0;
            int pixelSW = 0; int pixelAverSW = 0;
            int pixelC = 0; int pixelAverC = 0;

            int kernelSize = sizeof(nagaoC) / sizeof(*nagaoC);
            for(int x = 0; x < kernelSize; x++){
                for(int y = 0; y < kernelSize; y++){
                    pixelW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y], 2);
                    pixelAverW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y];

                    pixelNW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y], 2);
                    pixelAverNW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y];

                    pixelN += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y], 2);
                    pixelAverN += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y];

                    pixelNE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y], 2);
                    pixelAverNE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y];

                    pixelE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y], 2);
                    pixelAverE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y];

                    pixelSE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y], 2);
                    pixelAverSE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y];

                    pixelS += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y], 2);
                    pixelAverS += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y];

                    pixelSW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSW[x][y], 2);
                    pixelAverSW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                    pixelC += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y], 2);
                    pixelAverC += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y];
                }
            }
            double varPixelW = (double(pixelW)/9.0) - pow(double(pixelAverW)/9.0, 2);
            double varPixelNW = (double(pixelNW)/9.0) - pow(double(pixelAverNW)/9.0, 2);
            double varPixelN = (double(pixelN)/9.0)- pow(double(pixelAverN)/9.0, 2);
            double varPixelNE = (double(pixelNE)/9.0) - pow(double(pixelAverNE)/9.0, 2);
            double varPixelE = (double(pixelE)/9.0) - pow(double(pixelAverE)/9.0, 2);
            double varPixelSE = (double(pixelSE)/9.0) - pow(double(pixelAverSE)/9.0, 2);
            double varPixelS = (double(pixelS)/9.0) - pow(double(pixelAverS)/9.0, 2);
            double varPixelSW = (double(pixelSW)/9.0) - pow(double(pixelAverSW)/9.0, 2);
            double varPixelC = (double(pixelC)/9.0) - pow(double(pixelAverC)/9.0, 2);

            double array[9] = {varPixelW, varPixelNW, varPixelN, varPixelNE, varPixelE, varPixelSE, varPixelS, varPixelSW, varPixelC};
            double minVar = varPixelW;
            for(int i = 1; i < 9; i++){
                if(array[i] < minVar){
                    minVar = array[i];
                }
            }
            int pixel = 255;
            if(minVar == varPixelW){
                pixel = pixelAverW / 9;
            }else if(minVar == varPixelNW){
                pixel = pixelAverNW / 9;
            }else if(minVar == varPixelN){
                pixel = pixelAverN / 9;
            }else if (minVar == varPixelNE){
                pixel = pixelAverNE / 9;
            }else if (minVar == varPixelE){
                pixel = pixelAverE / 9;
            }else if (minVar == varPixelSE){
                pixel = pixelAverSE / 9;
            }else if (minVar == varPixelS){
                pixel = pixelAverS / 9;
            }else if (minVar == varPixelSW){
                pixel = pixelAverSW / 9;
            }else if (minVar == varPixelC){
                pixel = pixelAverC / 9;
            }
            resultImage.setPixel(i, j, qRgb(pixel, pixel, pixel));
        }

    }

    // Save the result
    *imageOriginal = resultImage;

}
