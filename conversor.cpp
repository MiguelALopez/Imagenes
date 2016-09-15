#include "conversor.h"
#include "ui_conversor.h"

Conversor::Conversor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conversor)
{
    ui->setupUi(this);
    selectedFlag = -1;
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

    switch (selectedFlag) { // Redimenciona el campo de la imagen original de covolucion
    case 0:{
        int w = ui->labelImageConvOrig->width();
        int h = ui->labelImageConvOrig->width();
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
    }break;
    case 1:{
        int w = ui->labelImageConvOrig->width();
        int h = ui->labelImageConvOrig->width();
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
    }break;
    case 2:{
        int w = ui->labelImageConvOrig->width();
        int h = ui->labelImageConvOrig->width();
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
    }
    default:{
    }break;
    }
}

void Conversor::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        switch (selectedFlag) { // Redimenciona el campo de la imagen original de covolucion
        case 0:{
            int w = ui->labelImageConvOrig->width();
            int h = ui->labelImageConvOrig->width();
            ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        }break;
        case 1:{
            int w = ui->labelImageConvOrig->width();
            int h = ui->labelImageConvOrig->width();
            ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        }break;
        case 2:{
            int w = ui->labelImageConvOrig->width();
            int h = ui->labelImageConvOrig->width();
            ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        }
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
                    int R = imageOriginal.pixelColor(i, j).red();
                    int G = imageOriginal.pixelColor(i, j).green();
                    int B = imageOriginal.pixelColor(i, j).blue();


                    imageTrasformada.setPixel(i, j, qRgb(R, G, B));
                    imageChanelR.setPixel(i, j, qRgb(R, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, G, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, B));

                }else if(ui->comboFinal->currentIndex() == 1){ // RGB to Grayscale
                    int color = imageOriginal.pixelColor(i, j).red() * 0.299 + imageOriginal.pixelColor(i, j).green() * 0.587 + imageOriginal.pixelColor(i, j).blue() * 0.114;
                    imageTrasformada.setPixelColor(i, j, QColor(color, color, color));

                    imageChanelR.setPixel(i, j, qRgb(color, color, color));
                    imageChanelG.setPixel(i, j, qRgb(color, color, color));
                    imageChanelB.setPixel(i, j, qRgb(color, color, color));

                }else if(ui->comboFinal->currentIndex() == 2){// RGB yo HSV
                    int H = imageOriginal.pixelColor(i, j).hue();
                    int S = imageOriginal.pixelColor(i, j).saturation();
                    int V = imageOriginal.pixelColor(i, j).value();
    //                imageOriginal.setPixelColor(i, j, QColor(H, S, V));
                    imageTrasformada.setPixel(i, j, qRgb(H, S, V));
                    imageChanelR.setPixel(i, j, qRgb(H, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, S, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, V));
    //                std::cout << "R: " << imageOriginal.pixelColor(i, j).red() << " G: " << imageOriginal.pixelColor(i, j).green() << " B: " << imageOriginal.pixelColor(i, j).blue() << std::endl;
    //                std::cout << "hue: " << H << " saturation: " << S <<  " Value: " << V << std::endl;

                }else if(ui->comboFinal->currentIndex() == 3){ // RGB to HSL
                    int H = imageOriginal.pixelColor(i, j).hue();
                    int S = imageOriginal.pixelColor(i, j).saturation();
                    int L = imageOriginal.pixelColor(i, j).lightness();
                    imageTrasformada.setPixel(i, j, qRgb(H, S, L));
                    imageChanelR.setPixel(i, j, qRgb(H, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, S, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, L));

                }else if(ui->comboFinal->currentIndex() == 4){ // RGB to Opponent Color
    //                int O1 = imageOriginal.pixelColor(i, j).red() * 0.06 + imageOriginal.pixelColor(i, j).green() * 0.63 + imageOriginal.pixelColor(i, j).blue() * 0.27;
    //                int O2 = imageOriginal.pixelColor(i, j).red() * 0.3 + imageOriginal.pixelColor(i, j).green() * 0.04 + imageOriginal.pixelColor(i, j).blue() * -0.35;
    //                int O3 = imageOriginal.pixelColor(i, j).red() * 0.34 + imageOriginal.pixelColor(i, j).green() * -0.6 + imageOriginal.pixelColor(i, j).blue() * 0.17;
                    int R = imageOriginal.pixelColor(i, j).red();
                    int G = imageOriginal.pixelColor(i, j).green();
                    int B = imageOriginal.pixelColor(i, j).blue();
                    double O1 = (R - G) / sqrt(2);
                    double O2 = (R + G - 2*B) / sqrt(6);
                    double O3 = (R + G + B) / sqrt(3);
                    imageTrasformada.setPixel(i, j, qRgb(O1, O2, O3));
                    imageChanelR.setPixel(i, j, qRgb(O1, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, O2, 0));
                    imageChanelB.setPixel(i, j, qRgb(0, 0, O2));

                }else if(ui->comboFinal->currentIndex() == 5){ // RGB to CMY
                    int C = imageOriginal.pixelColor(i, j).cyan();
                    int M = imageOriginal.pixelColor(i, j).magenta();
                    int Y = imageOriginal.pixelColor(i, j).yellow();
                    imageTrasformada.setPixel(i, j, qRgb(C, M, Y));
                    imageChanelR.setPixel(i, j, qRgb(C, 255, 255));
                    imageChanelG.setPixel(i, j, qRgb(255, M, 255));
                    imageChanelB.setPixel(i, j, qRgb(255, 255, Y));

                }else if(ui->comboFinal->currentIndex() == 6){ // RGB to R
                    imageTrasformada.setPixel(i, j, qRgb(imageOriginal.pixelColor(i, j).red(), 0, 0));

                }else if(ui->comboFinal->currentIndex() == 7){ // RGB to G
                    imageTrasformada.setPixel(i, j, qRgb(0, imageOriginal.pixelColor(i, j).green(), 0));

                }else if(ui->comboFinal->currentIndex() == 8){ // RGB to B
                    imageTrasformada.setPixel(i, j, qRgb(0, 0, imageOriginal.pixelColor(i, j).blue()));

                }else if(ui->comboFinal->currentIndex() == 9){ // RGB to RGB invertidos
                    int R = 255 - imageOriginal.pixelColor(i, j).red();
                    int G = 255 - imageOriginal.pixelColor(i, j).green();
                    int B = 255 - imageOriginal.pixelColor(i, j).blue();

                    imageTrasformada.setPixel(i, j, qRgb(R, G, B));
                    imageChanelR.setPixel(i, j, qRgb(R, 0, 0));
                    imageChanelG.setPixel(i, j, qRgb(0, G, 0));
                    imageChanelB.setPixel(i, j, qRgb(B, 0, B));

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
        selectedFlag = 0;

    }else if (ui->comboChannel->currentIndex() == 1){ // Channel 2
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        selectedFlag = 1;

    }else if(ui->comboChannel->currentIndex() == 2){
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");
        selectedFlag = 2;

    }
}

// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked()
{

    switch (selectedFlag) {
    case 0:{ // Filtro promedio
        imageFiltered = imageChanelR;
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

                        pixel += imageChanelR.pixelColor(i - middle + x, j - middle + y).red();

                    }
                }
                pixel = pixel / (kernelSize * kernelSize);
//                imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                imageFiltered.setPixel(i, j, qRgb(pixel, pixel, pixel));
            }
        }
        int wx = ui->labelImageConvFilt->width();
        int hx = ui->labelImageConvFilt->height();
        ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageFiltered).scaled(wx, hx, Qt::KeepAspectRatio));
        ui->labelImageConvFilt->setStyleSheet("border: 0px solid");
//            std::cout << "tiki termino" << std::endl;
    }break;
    case 1:{ // Filtro Gaussiano

    }
    default:{

    }break;
    }
}


