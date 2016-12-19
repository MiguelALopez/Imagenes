#include "edges.h"
#include "threshold.h"

Edges::Edges()
{

}


void Edges::sobelOperator(QImage *image, int threshold){
    QImage resultImage = *image;

    int kernel1[3][3] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};
    int kernel2[3][3] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}};
    int w = image->width();
    int h = image->height();
    int kernelMiddle = (sizeof(kernel1) / sizeof(*kernel1)) / 2;
    int kernelSize = sizeof(kernel1) / sizeof(*kernel1);


        for(int i = kernelMiddle; i < w - kernelMiddle; i++){
            for(int j = kernelMiddle; j < h - kernelMiddle; j++){
                double matriz1Pixel = 0;
                double matriz2Pixel = 0;

                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        matriz1Pixel += QColor(image->pixel(i - kernelMiddle + x, j - kernelMiddle + y)).red() * kernel1[x][y];
                        matriz2Pixel += QColor(image->pixel(i - kernelMiddle + x, j - kernelMiddle + y)).red() * kernel2[x][y];
                    }
                }

                int matrizPixel = abs(matriz1Pixel) + abs(matriz2Pixel);



//                if(matrizPixel < threshold){
//                    matrizPixel = 0;
//                }else{
//                    matrizPixel = 255;
//                }

                resultImage.setPixel(i, j, qRgb(matrizPixel, matrizPixel, matrizPixel));
            }
        }

        Threshold().otsuThreshold(&resultImage);
//        Threshold().manualThreshold(&resultImage, 0,0);


    *image = resultImage;
}
