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
}

void Conversor::on_pushButton_2_clicked(){
    //std::cout << ui->comboInicial->currentIndex() << " - " << ui->comboFinal->cu << std::endl;
    for(int i = 0; i < imageOriginal.width(); i++){
        for(int j = 0; j < imageOriginal.height(); j++){

            if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 1){
                int color = imageOriginal.pixelColor(i, j).red() * 0.299 + imageOriginal.pixelColor(i, j).green() * 0.587 + imageOriginal.pixelColor(i, j).blue() * 0.114;
                imageOriginal.setPixelColor(i, j, QColor(color, color, color));
            }else if(ui->comboInicial->currentIndex() == 0 && ui->comboFinal->currentIndex() == 2){
                double H;
                double S;
                double V;

                double var_R = ( imageOriginal.pixelColor(i, j).red() / 255 );
                double var_G = ( imageOriginal.pixelColor(i, j).green() / 255 );
                double var_B = ( imageOriginal.pixelColor(i, j).blue() / 255 );

                double var_Min = std::min( var_R, var_G, var_B );
//                double var_Max = std::max( var_R, var_G, var_B );
//                double del_Max = var_Max - var_Min;

//                V = var_Max;

//                if ( del_Max == 0 )
//                {
//                   H = 0;
//                   S = 0;
//                }
//                else
//                {
//                   S = del_Max / var_Max;

//                   double del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
//                   double del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
//                   double del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / del_Max;

//                   if( var_R == var_Max ) {
//                       H = del_B - del_G;
//                   }
//                   else if ( var_G == var_Max ){
//                       H = ( 1 / 3 ) + del_R - del_B;
//                   }
//                   else if ( var_B == var_Max ){
//                       H = ( 2 / 3 ) + del_G - del_R;
//                   }

//                   if ( H < 0 ) {
//                       H += 1;
//                   }
//                   if ( H > 1 ){
//                       H -= 1;
//                   }
//                }

                imageOriginal.setPixelColor(i, j, QColor((int)H, (int)S, (int)V));
                std::cout << "jojojojo" << std::endl;
            }

        }
    }

    int w = ui->labelImage2->width();
    int h = ui->labelImage2->height();
    ui->labelImage2->setPixmap(QPixmap::fromImage(imageOriginal).scaled(w, h, Qt::KeepAspectRatio));
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
