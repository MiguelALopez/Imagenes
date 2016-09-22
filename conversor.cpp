#include "conversor.h"
#include "ui_conversor.h"

Conversor::Conversor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conversor)
{
    ui->setupUi(this);
//    ui->labelImage1->setStyleSheet("border: 0.5px solid grey");
//    ui->labelImage2->setStyleSheet("border: 0.5px solid grey");

}

Conversor::~Conversor()
{
    delete ui;
}

// Evento encargado de capturar el redimencinamiento de la ventana
void Conversor::resizeEvent(QResizeEvent * event){
    QMainWindow::resizeEvent(event);
    if(!imageOriginal.isNull()){ // Redimenciona el campo de la imagen origina
        int w = ui->labelImageOriginal->width();
        int h = ui->labelImageOriginal->width();
        ui->labelImageOriginal->setPixmap(QPixmap::fromImage(imageOriginal).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageOriginal->setStyleSheet("border: 0px solid");
    }

    if(!imageTrasformada.isNull()){ // Redimenciona el campo de la imagen trasformada
        int w = ui->labelImageTransformed->width();
        int h = ui->labelImageTransformed->width();
        ui->labelImageTransformed->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageTransformed->setStyleSheet("border: 0px solid");
    }

    if(!imageFiltered.isNull()){ // Redimenciona el campo de la imagen con el filtro
        int w = ui->labelImageConvFilt->width();
        int h = ui->labelImageConvFilt->width();
        ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageFiltered).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvFilt->setStyleSheet("border: 0px solid");
    }

    if(!imageChoosed.isNull()){
            int w = ui->labelImageConvOrig->width();
            int h = ui->labelImageConvOrig->width();
            ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        }
}

void Conversor::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
            if(!imageChoosed.isNull()){
                int w = ui->labelImageConvOrig->width();
                int h = ui->labelImageConvOrig->width();
                ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
                ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
            }
        }
}

// Evento encargado de cargar la imagen desde una ubicacion
void Conversor::on_buttonLoad_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){

        std::cout << filename.toStdString() << std::endl;
        ui->lineURL->setText(filename);

        QPixmap image(filename);
        int w = ui->labelImageOriginal->width();
//        int h = ui->labelImage1->height();
        int h = ui->labelImageOriginal->width();
        ui->labelImageOriginal->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageOriginal->setStyleSheet("border: 0px solid");

        imageOriginal.load(filename);

    }else{
        QMessageBox::information(this, "Error","Por favor seleccione un tiki");
    }
}

// Evento encargado de pasar una imagen a un espacio de color
void Conversor::on_buttonConvert_clicked(){
    if(!imageOriginal.isNull()){
        imageTrasformada = imageOriginal;
        imageChanelR = imageOriginal;
        imageChanelG = imageOriginal;
        imageChanelB = imageOriginal;


        for(int i = 0; i < imageOriginal.width(); i++){
            for(int j = 0; j < imageOriginal.height(); j++){
                if(ui->comboFinal->currentIndex() == 0){ // RGB to RGB

                    int R = QColor(imageOriginal.pixel(i, j)).red();
                    int G = QColor(imageOriginal.pixel(i, j)).green();
                    int B = QColor(imageOriginal.pixel(i, j)).blue();


                    imageTrasformada.setPixel(i, j, qRgb(R, G, B));
                    imageChanelR.setPixel(i, j, qRgb(R, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, G, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, B));
                    transform = RGB;

                }else if(ui->comboFinal->currentIndex() == 1){ // RGB to Grayscale
                    int color = QColor(imageOriginal.pixel(i, j)).red() * 0.299 + QColor(imageOriginal.pixel(i, j)).green() * 0.587 + QColor(imageOriginal.pixel(i, j)).blue() * 0.114;
                    imageTrasformada.setPixel(i, j, qRgb(color, color, color));

                    imageChanelR.setPixel(i, j, qRgb(color, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, color, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, color));
                    transform = GRAYSCALE;

                }else if(ui->comboFinal->currentIndex() == 2){// RGB yo HSV
                    int H = QColor(imageOriginal.pixel(i, j)).hue();
                    int S = QColor(imageOriginal.pixel(i, j)).saturation();
                    int V = QColor(imageOriginal.pixel(i, j)).value();
    //                imageOriginal.setPixelColor(i, j, QColor(H, S, V));
                    imageTrasformada.setPixel(i, j, qRgb(H, S, V));
                    imageChanelR.setPixel(i, j, qRgb(H, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, S, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, V));
                    transform = HSV;
    //                std::cout << "R: " << imageOriginal.pixelColor(i, j).red() << " G: " << imageOriginal.pixelColor(i, j).green() << " B: " << imageOriginal.pixelColor(i, j).blue() << std::endl;
    //                std::cout << "hue: " << H << " saturation: " << S <<  " Value: " << V << std::endl;

                }else if(ui->comboFinal->currentIndex() == 3){ // RGB to HSL
                    int H = QColor(imageOriginal.pixel(i, j)).hue();
                    int S = QColor(imageOriginal.pixel(i, j)).saturation();
                    int L = QColor(imageOriginal.pixel(i, j)).lightness();
                    imageTrasformada.setPixel(i, j, qRgb(H, S, L));
                    imageChanelR.setPixel(i, j, qRgb(H, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, S, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, L));
                    transform = HSL;

                }else if(ui->comboFinal->currentIndex() == 4){ // RGB to Opponent Color
    //                int O1 = imageOriginal.pixelColor(i, j).red() * 0.06 + imageOriginal.pixelColor(i, j).green() * 0.63 + imageOriginal.pixelColor(i, j).blue() * 0.27;
    //                int O2 = imageOriginal.pixelColor(i, j).red() * 0.3 + imageOriginal.pixelColor(i, j).green() * 0.04 + imageOriginal.pixelColor(i, j).blue() * -0.35;
    //                int O3 = imageOriginal.pixelColor(i, j).red() * 0.34 + imageOriginal.pixelColor(i, j).green() * -0.6 + imageOriginal.pixelColor(i, j).blue() * 0.17;
                    int R = QColor(imageOriginal.pixel(i, j)).red();
                    int G = QColor(imageOriginal.pixel(i, j)).green();
                    int B = QColor(imageOriginal.pixel(i, j)).blue();
                    double O1 = (R - G) / sqrt(2);
                    double O2 = (R + G - 2*B) / sqrt(6);
                    double O3 = (R + G + B) / sqrt(3);
                    imageTrasformada.setPixel(i, j, qRgb(O1, O2, O3));
                    imageChanelR.setPixel(i, j, qRgb(O1, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, O2, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, O2));
                    transform = OPPONENT;

                }else if(ui->comboFinal->currentIndex() == 5){ // RGB to CMY
                    int C = QColor(imageOriginal.pixel(i, j)).cyan();
                    int M = QColor(imageOriginal.pixel(i, j)).magenta();
                    int Y = QColor(imageOriginal.pixel(i, j)).yellow();
                    imageTrasformada.setPixel(i, j, qRgb(C, M, Y));
                    imageChanelR.setPixel(i, j, qRgb(C, 255, 255));
                    imageChanelG.setPixel(i, j, qRgb(255, M, 255));
                    imageChanelB.setPixel(i, j, qRgb(255, 255, Y));
                    transform = CMY;

                }else if(ui->comboFinal->currentIndex() == 6){ // RGB to R
                    imageTrasformada.setPixel(i, j, qRgb(QColor(imageOriginal.pixel(i, j)).red(), 0, 0));

                }else if(ui->comboFinal->currentIndex() == 7){ // RGB to G
                    imageTrasformada.setPixel(i, j, qRgb(0, QColor(imageOriginal.pixel(i, j)).green(), 0));

                }else if(ui->comboFinal->currentIndex() == 8){ // RGB to B
                    imageTrasformada.setPixel(i, j, qRgb(0, 0, QColor(imageOriginal.pixel(i, j)).blue()));

                }else if(ui->comboFinal->currentIndex() == 9){ // RGB to RGB invertidos
                    int R = 255 - QColor(imageOriginal.pixel(i, j)).red();
                    int G = 255 - QColor(imageOriginal.pixel(i, j)).green();
                    int B = 255 - QColor(imageOriginal.pixel(i, j)).blue();

                    imageTrasformada.setPixel(i, j, qRgb(R, G, B));
                    imageChanelR.setPixel(i, j, qRgb(R, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, G, 0));
                    imageChanelB.setPixel(i, j, qRgb(B, 0, B));
                    transform = INVERTIDOS;

                }
            }
        }

        int w = ui->labelImageTransformed->width();
        int h = ui->labelImageTransformed->width();
        ui->labelImageTransformed->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageTransformed->setStyleSheet("border: 0px solid");

        w = ui->labelChannelR->width();
        h = ui->labelChannelR->height();
        ui->labelChannelR->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelR->setStyleSheet("border: 0px solid");

        w = ui->labelChannelG->width();
        h = ui->labelChannelG->height();
        ui->labelChannelG->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelG->setStyleSheet("border: 0px solid");

        w = ui->labelChannelB->width();
        h = ui->labelChannelB->height();
        ui->labelChannelB->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelB->setStyleSheet("border: 0px solid");
    }else{
        QMessageBox::information(this, "Error","Por favor seleccione un tiki");
    }

}

// Evento encargado de seleccionar un canal para la convolucion
void Conversor::on_buttonSelectChannel_clicked()
{
    int w = ui->labelImageConvOrig->width();
    int h = ui->labelImageConvOrig->height();
    if (ui->comboChannel->currentIndex() == 0){ // Channel 1
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelR;

    }else if (ui->comboChannel->currentIndex() == 1){ // Channel 2
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelG;

    }else if(ui->comboChannel->currentIndex() == 2){ // Chanel 3
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelB;
    }else if(ui->comboChannel->currentIndex() == 3){ // All the channels
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageFiltered).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        imageChoosed = imageFiltered;
    }
}

// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked()
{
    imageFiltered = imageChoosed;
    if(ui->comboConvolution->currentIndex() == 0){ // Average filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                    }
                }
                pixel = pixel / (kernelSize * kernelSize);
    //                imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                imageFiltered.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }

    }else if(ui->comboConvolution->currentIndex() == 1){ // Minimum filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int min = 255;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageChanelR.pixel(i - middle + x, j - middle + y)).red() < min){
                            min = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageFiltered.setPixel(i, j, qRgb(min, min, min));
            }
        }
    }else if(ui->comboConvolution->currentIndex() == 2){ // Maximum filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int max = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        if(QColor(imageChanelR.pixel(i - middle + x, j - middle + y)).red() > max){
                            max = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                }
                imageFiltered.setPixel(i, j, qRgb(max, max, max));
            }
        }
    }else if(ui->comboConvolution->currentIndex() == 3){ // Middle filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

            int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        if(transform == GRAYSCALE){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    QList<int> list;
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            list << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();

                        }
                    }

                    qSort(list.begin(), list.end());
                    pixel = list.at(list.length() / 2);
                    imageFiltered.setPixel(i, j, qRgb(pixel, pixel, pixel));
                }
            }
        }else{
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){

                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();

                        }
                    }
                    pixel = pixel / (kernelSize * kernelSize);
                    imageFiltered.setPixel(i, j, qRgb(pixel, QColor(imageFiltered.pixel(i, j)).green(), QColor(imageFiltered.pixel(i, j)).blue()));
                }
            }
        }
    }else if(ui->comboConvolution->currentIndex() == 4){ // Gaussian filter x3
        int commonFilter[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 16;
                imageFiltered.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }else if(ui->comboConvolution->currentIndex() == 5){ // Gaussian filter x5
        int commonFilter[5][5] = {{1, 4, 7, 4, 1},{4, 16, 26, 16, 4},{7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
        int w = imageChanelR.width();
        int h = imageChanelR.height();

        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        for(int i = middle; i < w - middle; i++){
            for(int j = middle; j < h - middle; j++){
                int pixel = 0;
                int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                    }
                }
                pixel = pixel / 273;
                imageFiltered.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
    }


    int wx = ui->labelImageConvFilt->width();
    int hx = ui->labelImageConvFilt->height();
    ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageFiltered).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageConvFilt->setStyleSheet("border: 0px solid");

}


