#include "convolution.h"

Convolution::Convolution()
{

}

void Convolution::averageFilter(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    if (channel == Conversor::RED){ // Average filter for the RED channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
                pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                imageResult.setPixel(i, j, qRgb(pixel, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::BLUE){ // Average filter for the GREEN channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue();
                    }
                }
                pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), pixel, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::GREEN){ // Average filter for the BLUE channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green();
                    }
                }
                pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), pixel));
            }
        }
    }else if(channel == Conversor::GREY){ // Average filter for GREY channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;

                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
                pixel = pixel / (kernelSize * kernelSize); // Se saca el promedio de todos los pixeles 
                imageResult.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::minimumFilter(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    if(channel == Conversor::RED){ // Minumun filter for the RED channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int min = 255;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() < min){
                            min = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(min, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    } else if (channel == Conversor::GREEN){ // Minumun filter for the GREEN channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int min = 255;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() < min){
                            min = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), min, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::BLUE){ // Minimun filter for the BLUE channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int min = 255;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() < min){
                            min = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), min));
            }
        }
    }else if (channel == Conversor::GREY){ // Minimun filter for the ALL channels
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int min = 255;

                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() < min){
                            min = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(min, min, min));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::maximumFilter(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

    if(channel == Conversor::RED){ // Maximun filter for the RED channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int max = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() > max){
                            max = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(max, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::GREEN){ // Maximum filter for the GREEN channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int max = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() > max){
                            max = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), max, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::BLUE){ // Maximum filter for the BLUE channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int max = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() > max){
                            max = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), max));
            }
        }
    }else if(channel == Conversor::GREY){ // Maximum filter for ALL channels
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int max = 0;

                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red() > max){
                            max = QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageResult.setPixel(i, j, qRgb(max, max, max));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::middleFilter(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;


    if(channel == Conversor::RED){ // Middle filter for the RED channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                QList<int> list;
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        list << QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
                qSort(list.begin(), list.end());
                pixel = list.at(list.length() / 2);
                imageResult.setPixel(i, j, qRgb(pixel, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::GREEN){ // Middle filter for the GREEN channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                QList<int> list;
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        list << QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green();
                    }
                }
                qSort(list.begin(), list.end());
                pixel = list.at(list.length() / 2);
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), pixel, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::BLUE){ // Middle filter for the BLUE channel
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                QList<int> list;
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        list << QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue();
                    }
                }
                qSort(list.begin(), list.end());
                pixel = list.at(list.length() / 2);
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), pixel));
            }
        }
    }else if(channel == Conversor::GREY){ // middle filter for ALL channels
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;

                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                QList<int> list;

                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        list << QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).red();
                    }
                }
                qSort(list.begin(), list.end());

                pixel = list.at(list.length() / 2);

                imageResult.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::gaussianFilterx3(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
    if(channel == Conversor::RED){
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
                imageResult.setPixel(i, j, qRgb(pixel, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::GREEN){
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 16;
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), pixel, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::BLUE){
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 16;
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), pixel));
            }
        }
    }else if(channel == Conversor::GREY){
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

                imageResult.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::gaussianFilterx5(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
    int commonFilter[5][5] = {{1, 4, 7, 4, 1},{4, 16, 26, 16, 4},{7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    int w = imageOriginal->width();
    int h = imageOriginal->height();
    int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
    if(channel == Conversor::RED){
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
                imageResult.setPixel(i, j, qRgb(pixel, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::GREEN){
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 273;
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), pixel, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if(channel == Conversor::BLUE){
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageOriginal->pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 273;
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), pixel));
            }
        }
    }else if(channel == Conversor::GREY){
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

                imageResult.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;
}

void Convolution::nagaoFilter(QImage *imageOriginal, Conversor::ChannelFilter channel){
    QImage imageResult = *imageOriginal;
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

    if (channel == Conversor::RED){ // Nagao filter for the RED channel
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
                        pixelW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y], 2);
                        pixelAverW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y];

                        pixelNW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y], 2);
                        pixelAverNW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y];

                        pixelN += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y], 2);
                        pixelAverN += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y];

                        pixelNE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y], 2);
                        pixelAverNE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y];

                        pixelE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y], 2);
                        pixelAverE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y];

                        pixelSE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y], 2);
                        pixelAverSE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y];

                        pixelS += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y], 2);
                        pixelAverS += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y];

                        pixelSW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y], 2);
                        pixelAverSW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                        pixelC += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y], 2);
                        pixelAverC += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y];
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
                imageResult.setPixel(i, j, qRgb(pixel, QColor(imageResult.pixel(i, j)).green(), QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::GREEN){ // Nagao filter for the GREEN channel
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
                        pixelW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoW[x][y], 2);
                        pixelAverW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoW[x][y];

                        pixelNW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNW[x][y], 2);
                        pixelAverNW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNW[x][y];

                        pixelN += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoN[x][y], 2);
                        pixelAverN += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoN[x][y];

                        pixelNE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNE[x][y], 2);
                        pixelAverNE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNE[x][y];

                        pixelE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoE[x][y], 2);
                        pixelAverE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoE[x][y];

                        pixelSE += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSE[x][y], 2);
                        pixelAverSE += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSE[x][y];

                        pixelS += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoS[x][y], 2);
                        pixelAverS += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoS[x][y];

                        pixelSW += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSW[x][y], 2);
                        pixelAverSW += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSW[x][y];

                        pixelC += pow(QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoC[x][y], 2);
                        pixelAverC += QColor(imageOriginal->pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoC[x][y];
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
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), pixel, QColor(imageResult.pixel(i, j)).blue()));
            }
        }
    }else if (channel == Conversor::BLUE){ // Nagao filter for the BLUE channel
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
                imageResult.setPixel(i, j, qRgb(QColor(imageResult.pixel(i, j)).red(), QColor(imageResult.pixel(i, j)).green(), pixel));
            }
        }
    }else if (channel == Conversor::GREY){ // Nagao filter for the GREY scale
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
                imageResult.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }

    // Save the result
    *imageOriginal = imageResult;

}
