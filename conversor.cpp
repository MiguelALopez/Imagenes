#include "conversor.h"
#include "ui_conversor.h"

Conversor::Conversor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conversor)
{
    ui->setupUi(this);
    ui->labelImage1->setStyleSheet("border: 0.5px solid grey");
    ui->labelImage2->setStyleSheet("border: 0.5px solid grey");

}

Conversor::~Conversor()
{
    delete ui;
}

void Conversor::on_buttomCargar_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", "All Files (*.*);;Image (*.png)");

    std::cout << filename.toStdString() << std::endl;
    ui->lineURL->setText(filename);

    QPixmap image(filename);
    int w = ui->labelImage1->width();
    int h = ui->labelImage1->height();
    ui->labelImage1->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
    ui->labelImage1->setStyleSheet("border: 0px solid");

    imageOriginal.load(filename);
    imageTrasformada.load(filename);
}

void Conversor::on_pushButton_2_clicked(){
    //std::cout << ui->comboInicial->currentIndex() << " - " << ui->comboFinal->cu << std::endl;
    for(int i = 0; i < imageOriginal.width(); i++){
        for(int j = 0; j < imageOriginal.height(); j++){

            if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 0){ // RGB to RGB
                int R = imageOriginal.pixelColor(i, j).red();
                int G = imageOriginal.pixelColor(i, j).green();
                int B = imageOriginal.pixelColor(i, j).blue();
                imageTrasformada.setPixel(i, j, qRgb(R, G, B));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 1){ // RGB to Yub
                int color = imageOriginal.pixelColor(i, j).red() * 0.299 + imageOriginal.pixelColor(i, j).green() * 0.587 + imageOriginal.pixelColor(i, j).blue() * 0.114;
                imageTrasformada.setPixelColor(i, j, QColor(color, color, color));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 2){// RGB yo HSV
                int H = imageOriginal.pixelColor(i, j).hue();
                int S = imageOriginal.pixelColor(i, j).saturation();
                int V = imageOriginal.pixelColor(i, j).value();
//                imageOriginal.setPixelColor(i, j, QColor(H, S, V));
                imageTrasformada.setPixel(i, j, qRgb(H, S, V));
//                std::cout << "R: " << imageOriginal.pixelColor(i, j).red() << " G: " << imageOriginal.pixelColor(i, j).green() << " B: " << imageOriginal.pixelColor(i, j).blue() << std::endl;
//                std::cout << "hue: " << H << " saturation: " << S <<  " Value: " << V << std::endl;

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 3){ // RGB to HSL
                int H = imageOriginal.pixelColor(i, j).hue();
                int S = imageOriginal.pixelColor(i, j).saturation();
                int L = imageOriginal.pixelColor(i, j).lightness();
                imageTrasformada.setPixel(i, j, qRgb(H, S, L));
            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 4){ // RGB to Opponent Color
                int O1 = imageOriginal.pixelColor(i, j).red() * 0.06 + imageOriginal.pixelColor(i, j).green() * 0.63 + imageOriginal.pixelColor(i, j).blue() * 0.27;
                int O2 = imageOriginal.pixelColor(i, j).red() * 0.3 + imageOriginal.pixelColor(i, j).green() * 0.04 + imageOriginal.pixelColor(i, j).blue() * -0.35;
                int O3 = imageOriginal.pixelColor(i, j).red() * 0.34 + imageOriginal.pixelColor(i, j).green() * -0.6 + imageOriginal.pixelColor(i, j).blue() * 0.17;
                imageTrasformada.setPixel(i, j, qRgb(O1, O2, O3));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 5){ // RGB to CMY
                int C = imageOriginal.pixelColor(i, j).cyan();
                int M = imageOriginal.pixelColor(i, j).magenta();
                int Y = imageOriginal.pixelColor(i, j).yellow();
                imageTrasformada.setPixel(i, j, qRgb(C, M, Y));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 6){ // RGB to R
                imageTrasformada.setPixel(i, j, qRgb(imageOriginal.pixelColor(i, j).red(), 0, 0));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 7){ // RGB to G
                imageTrasformada.setPixel(i, j, qRgb(0, imageOriginal.pixelColor(i, j).green(), 0));

            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 8){ // RGB to B
                imageTrasformada.setPixel(i, j, qRgb(0, 0, imageOriginal.pixelColor(i, j).blue()));
            }

        }
    }

    int w = ui->labelImage2->width();
    int h = ui->labelImage2->height();
    ui->labelImage2->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
    ui->labelImage2->setStyleSheet("border: 0px solid");

}

void Conversor::convertRGBtoYue(){
    for(int i = 0; i < imageOriginal.width(); i++){
        for(int j = 0; j < imageOriginal.height(); j++){
            int color = imageOriginal.pixelColor(i, j).red() * 0.299 + imageOriginal.pixelColor(i, j).green() * 0.587 + imageOriginal.pixelColor(i, j).blue() * 0.114;
            imageOriginal.setPixelColor(i, j, QColor(color, color, color));
        }
    }

    int w = ui->labelImage2->width();
    int h = ui->labelImage2->height();
    ui->labelImage2->setPixmap(QPixmap::fromImage(imageOriginal).scaled(w, h, Qt::KeepAspectRatio));
    ui->labelImage2->setStyleSheet("border: 0px solid");
}

void Conversor::convertRGBtoHSV(){
    //for(int i = 0; i < )
}
