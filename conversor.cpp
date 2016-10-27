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

void Conversor::resizeWindow(){
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

    if(!imageChoosed.isNull()){
            int w = ui->labelImageConvOrig->width();
            int h = ui->labelImageConvOrig->width();

            // Imagen convolucion original
            ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

            // Imagen Contraste original
            ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

            // Imagen Bordes original
            ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
            ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");
    }

    if(!imageConvolution.isNull()){ // Redimenciona el campo de la imagen con el filtro
        int w = ui->labelImageConvFilt->width();
        int h = ui->labelImageConvFilt->width();
        ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageConvolution).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvFilt->setStyleSheet("border: 0px solid");
    }

    if(!imageContrast.isNull()){ // Redimenciona el campo de la imagen con el nuevo contraste

    }

    if(!imageEdges.isNull()){
        int w = ui->labelImageEdgTrasf->width();
        int h = ui->labelImageEdgTrasf->width();
        ui->labelImageEdgTrasf->setPixmap(QPixmap::fromImage(imageEdges).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgTrasf->setStyleSheet("border: 0px solid");
    }
}

// Evento encargado de capturar el redimencinamiento de la ventana
void Conversor::resizeEvent(QResizeEvent * event){
    QMainWindow::resizeEvent(event);
    resizeWindow();

}

void Conversor::on_tabWidget_currentChanged(int index){
   resizeWindow();
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

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChanelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        imageChoosed = imageChanelR;
        channel = RED;

    }else if (ui->comboChannel->currentIndex() == 1){ // Channel 2
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChanelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        imageChoosed = imageChanelG;
        channel = GREEN;

    }else if(ui->comboChannel->currentIndex() == 2){ // Chanel 3
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChanelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        imageChoosed = imageChanelB;
        channel = BLUE;

    }else if(ui->comboChannel->currentIndex() == 3){ // All the channels
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        imageChoosed = imageTrasformada;
        channel = ALL;
    }else if(ui->comboChannel->currentIndex() == 4){ // Grey scale
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        imageChoosed = imageTrasformada;
        channel = GREY;
    }
}
// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked(){
    imageConvolution = imageChoosed;
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), pixel, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), pixel));
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
                    imageConvolution.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
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
                    imageConvolution.setPixel(i, j, qRgb(min, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), min, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), min));
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
                    imageConvolution.setPixel(i, j, qRgb(minR, minG, minB));
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
                    imageConvolution.setPixel(i, j, qRgb(max, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), max, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), max));
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
                    imageConvolution.setPixel(i, j, qRgb(maxR, maxG, maxB));
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), pixel, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), pixel));
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

                    imageConvolution.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), pixel, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), pixel));
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
                    pixelR = pixelR / 16;
                    pixelG = pixelG / 16;
                    pixelB = pixelB / 16;
                    imageConvolution.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), pixel, QColor(imageConvolution.pixel(i, j)).blue()));
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), pixel));
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
                    imageConvolution.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
                }
            }
        }

    }else if(ui->comboConvolution->currentIndex() == 6){ // Nagao filter
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



        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int middleNagao = (sizeof(nagaoC) / sizeof(*nagaoC)) / 2;

        if (channel == RED){ // Nagao filter for the RED channel
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
                            pixelW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y], 2);
                            pixelAverW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y];

                            pixelNW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y], 2);
                            pixelAverNW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y];

                            pixelN += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y], 2);
                            pixelAverN += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y];

                            pixelNE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y], 2);
                            pixelAverNE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y];

                            pixelE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y], 2);
                            pixelAverE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y];

                            pixelSE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y], 2);
                            pixelAverSE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y];

                            pixelS += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y], 2);
                            pixelAverS += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y];

                            pixelSW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y], 2);
                            pixelAverSW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                            pixelC += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y], 2);
                            pixelAverC += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y];
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
                }
            }
        }else if (channel == GREEN){ // Nagao filter for the GREEN channel
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
                            pixelW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoW[x][y], 2);
                            pixelAverW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoW[x][y];

                            pixelNW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNW[x][y], 2);
                            pixelAverNW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNW[x][y];

                            pixelN += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoN[x][y], 2);
                            pixelAverN += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoN[x][y];

                            pixelNE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNE[x][y], 2);
                            pixelAverNE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoNE[x][y];

                            pixelE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoE[x][y], 2);
                            pixelAverE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoE[x][y];

                            pixelSE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSE[x][y], 2);
                            pixelAverSE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSE[x][y];

                            pixelS += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoS[x][y], 2);
                            pixelAverS += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoS[x][y];

                            pixelSW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSW[x][y], 2);
                            pixelAverSW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoSW[x][y];

                            pixelC += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoC[x][y], 2);
                            pixelAverC += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).green() * nagaoC[x][y];
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), pixel, QColor(imageConvolution.pixel(i, j)).blue()));
                }
            }
        }else if (channel == BLUE){ // Nagao filter for the BLUE channel
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
                            pixelW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y], 2);
                            pixelAverW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y];

                            pixelNW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y], 2);
                            pixelAverNW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y];

                            pixelN += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y], 2);
                            pixelAverN += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y];

                            pixelNE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y], 2);
                            pixelAverNE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y];

                            pixelE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y], 2);
                            pixelAverE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y];

                            pixelSE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y], 2);
                            pixelAverSE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y];

                            pixelS += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y], 2);
                            pixelAverS += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y];

                            pixelSW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSW[x][y], 2);
                            pixelAverSW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                            pixelC += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y], 2);
                            pixelAverC += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y];
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
                    imageConvolution.setPixel(i, j, qRgb(QColor(imageConvolution.pixel(i, j)).red(), QColor(imageConvolution.pixel(i, j)).green(), pixel));
                }
            }
        }else if (channel == ALL){ // Nagao filter for the GREEN channel
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
                            // RED channel ------------------------------
                            pixelW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y], 2);
                            pixelAverW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoW[x][y];

                            pixelNW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y], 2);
                            pixelAverNW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNW[x][y];

                            pixelN += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y], 2);
                            pixelAverN += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoN[x][y];

                            pixelNE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y], 2);
                            pixelAverNE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoNE[x][y];

                            pixelE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y], 2);
                            pixelAverE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoE[x][y];

                            pixelSE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y], 2);
                            pixelAverSE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSE[x][y];

                            pixelS += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y], 2);
                            pixelAverS += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoS[x][y];

                            pixelSW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y], 2);
                            pixelAverSW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                            pixelC += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y], 2);
                            pixelAverC += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoC[x][y];


                            // Pendiente terminar

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
                    imageConvolution.setPixel(i, j, qRgb(pixel, QColor(imageConvolution.pixel(i, j)).green(), QColor(imageConvolution.pixel(i, j)).blue()));
                }
            }
        }else if (channel == GREY){ // Nagao filter for the GREY scale
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
                            pixelW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y], 2);
                            pixelAverW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoW[x][y];

                            pixelNW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y], 2);
                            pixelAverNW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNW[x][y];

                            pixelN += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y], 2);
                            pixelAverN += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoN[x][y];

                            pixelNE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y], 2);
                            pixelAverNE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoNE[x][y];

                            pixelE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y], 2);
                            pixelAverE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoE[x][y];

                            pixelSE += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y], 2);
                            pixelAverSE += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSE[x][y];

                            pixelS += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y], 2);
                            pixelAverS += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoS[x][y];

                            pixelSW += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoSW[x][y], 2);
                            pixelAverSW += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).red() * nagaoSW[x][y];

                            pixelC += pow(QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y], 2);
                            pixelAverC += QColor(imageChoosed.pixel(i - middleNagao + x, j - middleNagao + y)).blue() * nagaoC[x][y];
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
                    imageConvolution.setPixel(i, j, qRgb(pixel, pixel, pixel));
                }
            }
        }
    }


    int wx = ui->labelImageConvFilt->width();
    int hx = ui->labelImageConvFilt->height();
    ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageConvolution).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageConvFilt->setStyleSheet("border: 0px solid");

}



void Conversor::on_buttonApplyContrast_clicked(){
    imageContrast = imageChoosed;

    if(ui->comboContrast->currentIndex() == 0){ // Gamma correction
        double rate = 0.6;
        int w = imageChoosed.width();
        int h = imageChoosed.height();

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                double pixelR = 255.0 * pow(double(QColor(imageChoosed.pixel(i, j)).red()) / 255.0, rate);
                double pixelG = 255.0 * pow(double(QColor(imageChoosed.pixel(i, j)).green()) / 255.0, rate);
                double pixelB = 255.0 * pow(double(QColor(imageChoosed.pixel(i, j)).blue()) / 255.0, rate);

                imageContrast.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
            }
        }
    }else if(ui->comboContrast->currentIndex() == 1){ // Histogram equalization
        int histogramR[256];
        int histogramG[256];
        int histogramB[256];
        int w = imageChoosed.width();
        int h = imageChoosed.height();

        for(int i = 0; i < 256; i++){
            histogramR[i] = 0;
            histogramG[i] = 0;
            histogramB[i] = 0;
        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                histogramR[QColor(imageChoosed.pixel(i, j)).red()]++;
                histogramG[QColor(imageChoosed.pixel(i, j)).green()]++;
                histogramB[QColor(imageChoosed.pixel(i, j)).blue()]++;
            }
        }

        for(int i = 1; i < 256; i++){
            histogramR[i] += histogramR[i-1];
            histogramG[i] += histogramG[i-1];
            histogramB[i] += histogramB[i-1];
        }

        for(int i = 0; i < 256; i++){
            histogramR[i] = round(((255.0)/(double(w*h)))*histogramR[i]);
            histogramG[i] = round(((255.0)/(double(w*h)))*histogramG[i]);
            histogramB[i] = round(((255.0)/(double(w*h)))*histogramB[i]);
        }

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                int pixelR = histogramR[QColor(imageChoosed.pixel(i, j)).red()];
                int pixelG = histogramG[QColor(imageChoosed.pixel(i, j)).green()];
                int pixelB = histogramB[QColor(imageChoosed.pixel(i, j)).blue()];

                imageContrast.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
            }
        }


    }else if(ui->comboContrast->currentIndex() == 2){ // Contrast stretching
        int w = imageChoosed.width();
        int h = imageChoosed.height();

        double maxR = 0;
        double maxG = 0;
        double maxB = 06;

        double minR = 255;
        double minG = 255;
        double minB = 255;

        double newMax = 255;
        double newMin = 0;

        for(int i = 0; i < w ; i++){
            for(int j = 0; j < h; j++){
                if(QColor(imageChoosed.pixel(i, j)).red() > maxR){
                    maxR = double(QColor(imageChoosed.pixel(i, j)).red());
                }
                if(QColor(imageChoosed.pixel(i, j)).green() > maxG){
                    maxG = double(QColor(imageChoosed.pixel(i, j)).green());
                }
                if(QColor(imageChoosed.pixel(i, j)).blue() > maxB){
                    maxB = double(QColor(imageChoosed.pixel(i, j)).blue());
                }


                if(QColor(imageChoosed.pixel(i, j)).red() < minR){
                    minR = double(QColor(imageChoosed.pixel(i, j)).red());
                }
                if(QColor(imageChoosed.pixel(i, j)).green() < minG){
                    minG = double(QColor(imageChoosed.pixel(i, j)).green());
                }
                if(QColor(imageChoosed.pixel(i, j)).blue() < minB){
                    minB = double(QColor(imageChoosed.pixel(i, j)).blue());
                }
            }
        }

        std::cout << "min " << minR << " max " << maxR << std::endl;

        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                double pixelR = ((double(QColor(imageChoosed.pixel(i, j)).red()) - minR) * ((newMax - newMin)/(maxR - minR))) + newMin;
                double pixelG = ((double(QColor(imageChoosed.pixel(i, j)).red()) - minR) * ((newMax - newMin)/(maxR - minR))) + newMin;
                double pixelB = ((double(QColor(imageChoosed.pixel(i, j)).red()) - minR) * ((newMax - newMin)/(maxR - minR))) + newMin;
                imageContrast.setPixel(i, j, qRgb(pixelR, pixelG, pixelB));
            }
        }
    }

    setupBarChartDemo(ui->plotHistogram);

    int wx = ui->labelImageContTrans->width();
    int hx = ui->labelImageContTrans->height();
    ui->labelImageContTrans->setPixmap(QPixmap::fromImage(imageContrast).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageContTrans->setStyleSheet("border: 0px solid");
}

void Conversor::on_buttonEdges_clicked()
{
    imageEdges = imageChoosed;
    QImage matrizY = imageChoosed;
    QImage matrizX = imageChoosed;
    int threshold = ui->spinThreshold->value();

    if(ui->comboEdges->currentIndex() == 0){ // sobel
        int kernel1[3][3] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};
        int kernel2[3][3] = {{1, 0,-1},{2, 0,-2},{1, 0,-1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int kernelMiddle = (sizeof(kernel1) / sizeof(*kernel1)) / 2;


        for(int i = kernelMiddle; i < w - kernelMiddle; i++){
            for(int j = kernelMiddle; j < h - kernelMiddle; j++){
                double matriz1PixelR = 0;
                double matriz1PixelG = 0;
                double matriz1PixelB = 0;

                double matriz2PixelR = 0;
                double matriz2PixelG = 0;
                double matriz2PixelB = 0;

                int kernelSize = sizeof(kernel1) / sizeof(*kernel1);
                for(int x = 0; x < kernelSize; x++){
                    for(int y = 0; y < kernelSize; y++){
                        matriz1PixelR += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).red() * kernel1[x][y];
                        matriz1PixelG += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).green() * kernel1[x][y];
                        matriz1PixelB += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).blue() * kernel1[x][y];

                        matriz2PixelR += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).red() * kernel2[x][y];
                        matriz2PixelG += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).green() * kernel2[x][y];
                        matriz2PixelB += QColor(imageChoosed.pixel(i - kernelMiddle + x, j - kernelMiddle + y)).blue() * kernel2[x][y];
                    }
                }

//                for(int x = -1; x < kernelSize-1; x++){
//                    for(int y= -1; y < kernelSize-1; y++){
//                        matriz1PixelR += (QColor(imageChoosed.pixel(i + x, j + y)).red() * kernel1[x+1][y+1]);
//                        matriz1PixelG += (QColor(imageChoosed.pixel(i + x, j + y)).green() * kernel1[x+1][y+1]);
//                        matriz1PixelB += (QColor(imageChoosed.pixel(i + x, j + y)).blue() * kernel1[x+1][y+1]);

//                        matriz2PixelR += (QColor(imageChoosed.pixel(i + x, j + y)).red() * kernel2[x+1][y+1]);
//                        matriz2PixelG += (QColor(imageChoosed.pixel(i + x, j + y)).green() * kernel2[x+1][y+1]);
//                        matriz2PixelB += (QColor(imageChoosed.pixel(i + x, j + y)).blue() * kernel2[x+1][y+1]);
//                    }
//                }

                int matrizPixelR = abs(matriz1PixelR) + abs(matriz2PixelR);
                int matrizPixelG = abs(matriz1PixelG) + abs(matriz2PixelG);
                int matrizPixelB = abs(matriz1PixelB) + abs(matriz2PixelB);

//                double matrizPixelR = sqrt(pow(matriz1PixelR, 2) + pow(matriz2PixelR, 2));
//                double matrizPixelG = sqrt(pow(matriz1PixelR, 2) + pow(matriz2PixelR, 2));
//                double matrizPixelB = sqrt(pow(matriz1PixelR, 2) + pow(matriz2PixelR, 2));

                if(matrizPixelR > threshold){
                    matrizPixelR = 0;
                }else{
                    matrizPixelR = 255;
                }
                if(matrizPixelG > threshold){
                    matrizPixelG = 0;
                }else{
                    matrizPixelG = 255;
                }
                if(matrizPixelB > threshold){
                    matrizPixelB = 0;
                }else{
                    matrizPixelB = 255;
                }

                imageEdges.setPixel(i, j, qRgb(matrizPixelR, matrizPixelG, matrizPixelB));
            }
        }
    }
    int wx = ui->labelImageEdgTrasf->width();
    int hx = ui->labelImageEdgTrasf->height();
    ui->labelImageEdgTrasf->setPixmap(QPixmap::fromImage(imageEdges).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageEdgTrasf->setStyleSheet("border: 0px solid");
}


void Conversor::setupBarChartDemo(QCustomPlot *customPlot)
{
    std::cout << "tiki" << std::endl;
    QString demoName = "Bar Chart Demo";
    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *nuclear = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(regen);
    customPlot->addPlottable(nuclear);
    customPlot->addPlottable(fossil);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    fossil->setName("Fossil fuels");
    pen.setColor(QColor(255, 131, 0));
    fossil->setPen(pen);
    fossil->setBrush(QColor(255, 131, 0, 50));
    nuclear->setName("Nuclear");
    pen.setColor(QColor(1, 92, 191));
    nuclear->setPen(pen);
    nuclear->setBrush(QColor(1, 92, 191, 50));
    regen->setName("Regenerative");
    pen.setColor(QColor(150, 222, 0));
    regen->setPen(pen);
    regen->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->setRange(0, 8);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 12.1);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
    nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
    nuclear->setData(ticks, nuclearData);
    regen->setData(ticks, regenData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
