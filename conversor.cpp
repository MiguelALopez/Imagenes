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

void Conversor::on_pushButton_2_clicked()
{
    convertRGBtoYue();

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
