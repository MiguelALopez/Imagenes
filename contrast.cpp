#include "contrast.h"

Contrast::Contrast()
{

}

void Contrast::gammaCorrection(QImage *image, Conversor::ChannelFilter channel, double rate){
    if(channel == Conversor::RED){
        int w = image->width();
        int h = image->height();

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                double pixel = 255.0 * pow(double(QColor(image->pixel(i, j)).red()) / 255.0, rate);

                image->setPixel(i, j, qRgb(pixel, 0, 0));
            }
        }
    }else if(channel == Conversor::GREEN){
        int w = image->width();
        int h = image->height();

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                double pixel = 255.0 * pow(double(QColor(image->pixel(i, j)).green()) / 255.0, rate);

                image->setPixel(i, j, qRgb(0, pixel, 0));
            }
        }
    }else if(channel == Conversor::BLUE){
        int w = image->width();
        int h = image->height();

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                double pixel = 255.0 * pow(double(QColor(image->pixel(i, j)).blue()) / 255.0, rate);

                image->setPixel(i, j, qRgb(0, 0, pixel));
            }
        }
    }else if(channel == Conversor::GREY){
        int w = image->width();
        int h = image->height();

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                double pixel = 255.0 * pow(double(QColor(image->pixel(i, j)).red()) / 255.0, rate);

                image->setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }
}

void Contrast::histogramEqualization(QImage *image, Conversor::ChannelFilter channel){
    int histogram[256];
    int w = image->width();
    int h = image->height();

    // Se inicializa el arreglo en 0
    for(int i = 0; i < 256; i++){
        histogram[i] = 0;
    }

    if(channel == Conversor::RED){

        // Se llena el histograma con los valores correspondientes
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                histogram[QColor(image->pixel(i, j)).red()]++;
            }
        }

        for(int i = 1; i < 256; i++){
            histogram[i] += histogram[i-1];
        }

        for(int i = 0; i < 256; i++){
            histogram[i] = round(((255.0)/(double(w*h)))*histogram[i]);

        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                int pixel = histogram[QColor(image->pixel(i, j)).red()];

                image->setPixel(i, j, qRgb(pixel, 0, 0));
            }
        }
    }else if(channel == Conversor::GREEN){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                histogram[QColor(image->pixel(i, j)).green()]++;
            }
        }

        for(int i = 1; i < 256; i++){
            histogram[i] += histogram[i-1];
        }

        for(int i = 0; i < 256; i++){
            histogram[i] = round(((255.0)/(double(w*h)))*histogram[i]);
        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                int pixel = histogram[QColor(image->pixel(i, j)).green()];

                image->setPixel(i, j, qRgb(0, pixel, 0));
            }
        }

    }else if(channel == Conversor::BLUE){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                histogram[QColor(image->pixel(i, j)).blue()]++;
            }
        }

        for(int i = 1; i < 256; i++){
            histogram[i] += histogram[i-1];
        }

        for(int i = 0; i < 256; i++){
            histogram[i] = round(((255.0)/(double(w*h)))*histogram[i]);
        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                int pixel = histogram[QColor(image->pixel(i, j)).blue()];

                image->setPixel(i, j, qRgb(0, 0, pixel));
            }
        }

    }else if(channel == Conversor::GREY){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                histogram[QColor(image->pixel(i, j)).red()]++;
            }
        }

        for(int i = 1; i < 256; i++){
            histogram[i] += histogram[i-1];
        }

        for(int i = 0; i < 256; i++){
            histogram[i] = round(((255.0)/(double(w*h)))*histogram[i]);
        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                int pixel = histogram[QColor(image->pixel(i, j)).red()];

                image->setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }
}

void Contrast::contrastStretching(QImage *image, Conversor::ChannelFilter channel){
    int w = image->width();
    int h = image->height();

    double max = 0;
    double min = 255;

    double newMax = 255;
    double newMin = 0;
    if (channel == Conversor::RED){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                if(QColor(image->pixel(i, j)).red() > max){
                    max = double(QColor(image->pixel(i, j)).red());
                }
                if(QColor(image->pixel(i, j)).red() < min){
                    min = double(QColor(image->pixel(i, j)).red());
                }
            }
        }

        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                double pixel = ((double(QColor(image->pixel(i, j)).red()) - min) * ((newMax - newMin)/(max - min))) + newMin;
                image->setPixel(i, j, qRgb(pixel, 0, 0));
            }
        }
    }else if(channel == Conversor::GREEN){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                if(QColor(image->pixel(i, j)).green() > max){
                    max = double(QColor(image->pixel(i, j)).green());
                }
                if(QColor(image->pixel(i, j)).green() < min){
                    min = double(QColor(image->pixel(i, j)).green());
                }
            }
        }

        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                double pixel = ((double(QColor(image->pixel(i, j)).red()) - min) * ((newMax - newMin)/(max - min))) + newMin;
                image->setPixel(i, j, qRgb(0, pixel, 0));
            }
        }
    }else if(channel == Conversor::BLUE){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                if(QColor(image->pixel(i, j)).blue() > max){
                    max = double(QColor(image->pixel(i, j)).blue());
                }
                if(QColor(image->pixel(i, j)).blue() < min){
                    min = double(QColor(image->pixel(i, j)).blue());
                }
            }
        }

        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                double pixel = ((double(QColor(image->pixel(i, j)).red()) - min) * ((newMax - newMin)/(max - min))) + newMin;
                image->setPixel(i, j, qRgb(0, 0, pixel));
            }
        }
    }else if(channel == Conversor::GREY){
        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                if(QColor(image->pixel(i, j)).red() > max){
                    max = double(QColor(image->pixel(i, j)).red());
                }
                if(QColor(image->pixel(i, j)).red() < min){
                    min = double(QColor(image->pixel(i, j)).red());
                }
            }
        }

        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                double pixel = ((double(QColor(image->pixel(i, j)).red()) - min) * ((newMax - newMin)/(max - min))) + newMin;
                image->setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }
}
