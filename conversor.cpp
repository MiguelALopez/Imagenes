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

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelR;
        channel = RED;

    }else if (ui->comboChannel->currentIndex() == 1){ // Channel 2
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelG;
        channel = GREEN;

    }else if(ui->comboChannel->currentIndex() == 2){ // Chanel 3
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");
        imageChoosed = imageChanelB;
        channel = BLUE;

    }else if(ui->comboChannel->currentIndex() == 3){ // All the channels
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageFiltered).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageFiltered).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");
        imageChoosed = imageTrasformada;
        channel = ALL;
    }
}
// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked(){
    imageFiltered = imageChoosed;
    if(ui->comboConvolution->currentIndex() == 0){ // Average filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

        if (channel == RED){ // Average filter for the RED channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                        }
                    }
                    pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                    imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == BLUE){ // Average filter for the GREEN channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                    pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), pixel, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == GREEN){ // Average filter for the BLUE channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                        }
                    }
                    pixel = pixel / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), pixel));
                }
            }
        }else if(channel == ALL){ // Average filter for ALL channels
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixelR = 0;
                    int pixelG = 0;
                    int pixelB = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixelR += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            pixelG += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            pixelB += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                    pixelR = pixelR / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles RED
                    pixelG = pixelG / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles GREEN
                    pixelB = pixelB / (kernelSize * kernelSize); // Se saca el primedio de todos los pixeles BLUE
                    imageFiltered.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
                }
            }
        }


    }else if(ui->comboConvolution->currentIndex() == 1){ // Minimum filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

        if(channel == RED){ // Minumun filter for the RED channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int min = 255;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() < min){
                                min = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(min, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        } else if (channel == GREEN){ // Minumun filter for the GREEN channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int min = 255;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() < min){
                                min = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), min, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if (channel == BLUE){ // Minimun filter for the BLUE channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int min = 255;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() < min){
                                min = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), min));
                }
            }
        }else if (channel == ALL){ // Minimun filter for the ALL channels
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int minR = 255;
                    int minG = 255;
                    int minB = 255;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() < minR){
                                minR = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            }
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green() < minG){
                                minG = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            }
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue() < minB){
                                minB = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(minR, minG, minB));
                }
            }
        }

    }else if(ui->comboConvolution->currentIndex() == 2){ // Maximum filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;

        if(channel == RED){ // Maximun filter for the RED channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int max = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > max){
                                max = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(max, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == GREEN){ // Maximum filter for the GREEN channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int max = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > max){
                                max = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), max, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if (channel == BLUE){ // Maximum filter for the BLUE channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int max = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > max){
                                max = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), max));
                }
            }
        }else if(channel == ALL){ // Maximum filter for ALL channels
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int maxR = 0;
                    int maxG = 0;
                    int maxB = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > maxR){
                                maxR = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            }
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > maxG){
                                maxG = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            }
                            if(QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() > maxB){
                                maxB = QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                            }
                        }
                    }
                    imageFiltered.setPixel(i, j, qRgb(maxR, maxG, maxB));
                }
            }
        }

    }else if(ui->comboConvolution->currentIndex() == 3){ // Middle filter
        int commonFilter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;


        if(channel == RED){ // Middle filter for the RED channel
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
                    imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == GREEN){ // Middle filter for the GREEN channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    QList<int> list;
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            list << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                        }
                    }
                    qSort(list.begin(), list.end());
                    pixel = list.at(list.length() / 2);
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), pixel, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == BLUE){ // Middle filter for the BLUE channel
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    QList<int> list;
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            list << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                    qSort(list.begin(), list.end());
                    pixel = list.at(list.length() / 2);
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), pixel));
                }
            }
        }else if(channel == ALL){ // middle filter for ALL channels
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixelR = 0;
                    int pixelG = 0;
                    int pixelB = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    QList<int> listR;
                    QList<int> listG;
                    QList<int> listB;
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            listR << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red();
                            listG << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green();
                            listB << QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue();
                        }
                    }
                    qSort(listR.begin(), listR.end());
                    qSort(listG.begin(), listG.end());
                    qSort(listB.begin(), listB.end());
                    pixelR = listR.at(listR.length() / 2);
                    pixelG = listG.at(listG.length() / 2);
                    pixelB = listB.at(listB.length() / 2);

                    imageFiltered.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
                }
            }
        }
    }else if(ui->comboConvolution->currentIndex() == 4){ // Gaussian filter x3
        int commonFilter[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        if(channel == RED){
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
                    imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if (channel == GREEN){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                        }
                    }
                    pixel = pixel / 16;
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), pixel, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if (channel == BLUE){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                        }
                    }
                    pixel = pixel / 16;
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), pixel));
                }
            }
        }else if(channel = ALL){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixelR = 0;
                    int pixelG = 0;
                    int pixelB = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixelR += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                            pixelG += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                            pixelB += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                        }
                    }
                    pixelR = pixelR / 16;
                    pixelG = pixelG / 16;
                    pixelB = pixelB / 16;
                    imageFiltered.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
                }
            }
        }

    }else if(ui->comboConvolution->currentIndex() == 5){ // Gaussian filter x5
        int commonFilter[5][5] = {{1, 4, 7, 4, 1},{4, 16, 26, 16, 4},{7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middle = (sizeof(commonFilter) / sizeof(*commonFilter)) / 2;
        if(channel == RED){
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
                    imageFiltered.setPixel(i, j, qRgb(pixel, imageFiltered.pixelColor(i, j).green(), imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == GREEN){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                        }
                    }
                    pixel = pixel / 273;
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), pixel, imageFiltered.pixelColor(i, j).blue()));
                }
            }
        }else if(channel == BLUE){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixel = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixel += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                        }
                    }
                    pixel = pixel / 273;
                    imageFiltered.setPixel(i, j, qRgb(imageFiltered.pixelColor(i, j).red(), imageFiltered.pixelColor(i, j).green(), pixel));
                }
            }
        }else if(channel == ALL){
            for(int i = middle; i < w - middle; i++){
                for(int j = middle; j < h - middle; j++){
                    int pixelR = 0;
                    int pixelG = 0;
                    int pixelB = 0;
                    int kernelSize = sizeof(commonFilter) / sizeof(*commonFilter);
                    for(int x = 0; x < kernelSize; x++){
                        for(int y = 0; y < kernelSize; y++){
                            pixelR += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).red() * commonFilter[x][y];
                            pixelG += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).green() * commonFilter[x][y];
                            pixelB += QColor(imageChoosed.pixel(i - middle + x, j - middle + y)).blue() * commonFilter[x][y];
                        }
                    }
                    pixelR = pixelR / 273;
                    pixelG = pixelG / 273;
                    pixelB = pixelB / 273;
                    imageFiltered.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
                }
            }
        }

    }


    int wx = ui->labelImageConvFilt->width();
    int hx = ui->labelImageConvFilt->height();
    ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageFiltered).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageConvFilt->setStyleSheet("border: 0px solid");

}



void Conversor::on_buttonApplyContrast_clicked(){

}
