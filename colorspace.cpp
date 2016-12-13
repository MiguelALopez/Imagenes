#include "colorspace.h"

ColorSpace::ColorSpace()
{

}

void ColorSpace::convertToGrayscale(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int color = QColor(image->pixel(i, j)).red() * 0.299 + QColor(image->pixel(i, j)).green() * 0.587 + QColor(image->pixel(i, j)).blue() * 0.114;

            image->setPixel(i, j, qRgb(color, color, color));

            channelR->setPixel(i, j, qRgb(color, 0, 0));
            channelG->setPixel(i, j, qRgb(0, color, 0));
            channelB->setPixel(i, j, qRgb(0, 0, color));
        }
    }
}

void ColorSpace::convertToHSV(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int H = QColor(image->pixel(i, j)).hue();
            int S = QColor(image->pixel(i, j)).saturation();
            int V = QColor(image->pixel(i, j)).value();

            image->setPixel(i, j, qRgb(H, S, V));

            channelR->setPixel(i, j, qRgb(H, 0, 0));
            channelG->setPixel(i, j, qRgb(0, S, 0));
            channelB->setPixel(i, j, qRgb(0, 0, V));
        }
    }
}

void ColorSpace::convertToHSL(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int H = QColor(image->pixel(i, j)).hue();
            int S = QColor(image->pixel(i, j)).saturation();
            int L = QColor(image->pixel(i, j)).lightness();

            image->setPixel(i, j, qRgb(H, S, L));

            channelR->setPixel(i, j, qRgb(H, 0, 0));
            channelG->setPixel(i, j, qRgb(0, S, 0));
            channelB->setPixel(i, j, qRgb(0, 0, L));
        }
    }
}

void ColorSpace::convertToOpponet(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int R = QColor(image->pixel(i, j)).red();
            int G = QColor(image->pixel(i, j)).green();
            int B = QColor(image->pixel(i, j)).blue();

            double O1 = (R - G) / sqrt(2);
            double O2 = (R + G - 2*B) / sqrt(6);
            double O3 = (R + G + B) / sqrt(3);

            image->setPixel(i, j, qRgb(O1, O2, O3));

            channelR->setPixel(i, j, qRgb(O1, 0, 0));
            channelG->setPixel(i, j, qRgb(0, O2, 0));
            channelB->setPixel(i, j, qRgb(0, 0, O2));
        }
    }
}

void ColorSpace::convertToCMY(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int C = QColor(image->pixel(i, j)).cyan();
            int M = QColor(image->pixel(i, j)).magenta();
            int Y = QColor(image->pixel(i, j)).yellow();

            image->setPixel(i, j, qRgb(C, M, Y));

            channelR->setPixel(i, j, qRgb(C, 255, 255));
            channelG->setPixel(i, j, qRgb(255, M, 255));
            channelB->setPixel(i, j, qRgb(255, 255, Y));
        }
    }
}

void ColorSpace::convertToInverted(QImage *image, QImage *channelR, QImage *channelG, QImage *channelB){
    for(int i = 0; i < image->width(); i++){
        for(int j = 0; j < image->height(); j++){
            int R = 255 - QColor(image->pixel(i, j)).red();
            int G = 255 - QColor(image->pixel(i, j)).green();
            int B = 255 - QColor(image->pixel(i, j)).blue();

            image->setPixel(i, j, qRgb(R, G, B));

            channelR->setPixel(i, j, qRgb(R, 0, 0));
            channelG->setPixel(i, j, qRgb(0, G, 0));
            channelB->setPixel(i, j, qRgb(B, 0, B));
        }
    }
}
