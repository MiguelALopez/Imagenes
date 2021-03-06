#include "conversor.h"
#include "ui_conversor.h"
#include "convolution.h"
#include "colorspace.h"
#include "contrast.h"
#include "edges.h"
#include "threshold.h"
#include "morphologicaloperators.h"
#include "error.h"

Conversor::Conversor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conversor)
{
    ui->setupUi(this);
}

Conversor::~Conversor()
{
    delete ui;
}

void Conversor::initVector(){
    for(int i = 0; i < 256; i++){
        imageTransformadaHisto.append(0);
    }
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

        // Imagen Threshold original
        ui->labelImageThresOrigi->setPixmap(QPixmap::fromImage(imageChoosed).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageThresOrigi->setStyleSheet("border: 0px solid");

    }

    if(!imageConvolution.isNull()){ // Redimenciona el campo de la imagen con el filtro
        int w = ui->labelImageConvFilt->width();
        int h = ui->labelImageConvFilt->width();
        ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageConvolution).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvFilt->setStyleSheet("border: 0px solid");
    }

    if(!imageContrast.isNull()){ // Redimenciona el campo de la imagen con el nuevo contraste
        int w = ui->labelImageContTrans->width();
        int h = ui->labelImageContTrans->width();
        ui->labelImageContTrans->setPixmap(QPixmap::fromImage(imageContrast).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContTrans->setStyleSheet("border: 0px solid");
    }

    if(!imageEdges.isNull()){
        int w = ui->labelImageEdgTrasf->width();
        int h = ui->labelImageEdgTrasf->width();
        ui->labelImageEdgTrasf->setPixmap(QPixmap::fromImage(imageEdges).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgTrasf->setStyleSheet("border: 0px solid");
    }

    if(!imageThres.isNull()){
        int w = ui->labelImageThresTrans->width();
        int h = ui->labelImageThresTrans->width();
        ui->labelImageThresTrans->setPixmap(QPixmap::fromImage(imageThres).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageThresTrans->setStyleSheet("border: 0px solid");
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
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/miguel/Imágenes/Retina/DRIVE/test/images/", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){

        std::cout << filename.toStdString() << std::endl;
        ui->lineURL->setText(filename);

        QPixmap image(filename);
        imageOriginal.load(filename);
        int w = ui->labelImageOriginal->width();
        //        int h = ui->labelImage1->height();
        int h = ui->labelImageOriginal->width();

        // Escala la imagen original
        if(imageOriginal.width() > ui->spinResize->value() && ui->checkResize->isChecked()){
            double imageWidth = imageOriginal.width();
            double imageHeigth = imageOriginal.height();
            double proportion = imageWidth / ui->spinResize->value();
            imageOriginal = imageOriginal.scaled(imageWidth / proportion, imageHeigth / proportion);
            std::cout << imageOriginal.width() << " - " << imageOriginal.height() << std::endl;
        }


        ui->labelImageOriginal->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageOriginal->setStyleSheet("border: 0px solid");

        //        imageOriginal.load(filename);
        //        imageOriginal = imageOriginal.scaled(750, 600);

    }else{
        QMessageBox::information(this, "Error","Por favor seleccione una imagen");
    }
}

// Evento encargado de pasar una imagen a un espacio de color
void Conversor::on_buttonConvert_clicked(){
    if(!imageOriginal.isNull()){
        initVector();
        imageTrasformada = imageOriginal;
        imageChannelR = imageOriginal;
        imageChannelG = imageOriginal;
        imageChannelB = imageOriginal;
        if(ui->comboFinal->currentIndex() == 0){ // RGB to Grayscale
            transform = GRAYSCALE;
            ColorSpace().convertToGrayscale(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
        }else if(ui->comboFinal->currentIndex() == 1){ // RGB to HSV
            ColorSpace().convertToHSV(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
            transform = HSV;
        }else if(ui->comboFinal->currentIndex() == 2){ // RGB to HSL
            ColorSpace().convertToHSL(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
            transform = HSL;
        }else if(ui->comboFinal->currentIndex() == 3){ // RGB to Opponent
            ColorSpace().convertToOpponet(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
            transform = OPPONENT;
        }else if(ui->comboFinal->currentIndex() == 4){ // RGB to CMY
            ColorSpace().convertToCMY(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
            transform = CMY;
        }else if(ui->comboFinal->currentIndex() == 5){ // RGB to Invertidos
            ColorSpace().convertToInverted(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
            transform = INVERTIDOS;
        }else if(ui->comboFinal->currentIndex() == 6){ // RGB to RGB
            ColorSpace().convertToRGB(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
        }
        

        int w = ui->labelImageTransformed->width();
        int h = ui->labelImageTransformed->width();
        ui->labelImageTransformed->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageTransformed->setStyleSheet("border: 0px solid");

        w = ui->labelChannelR->width();
        h = ui->labelChannelR->height();
        ui->labelChannelR->setPixmap(QPixmap::fromImage(imageChannelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelR->setStyleSheet("border: 0px solid");

        w = ui->labelChannelG->width();
        h = ui->labelChannelG->height();
        ui->labelChannelG->setPixmap(QPixmap::fromImage(imageChannelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelG->setStyleSheet("border: 0px solid");

        w = ui->labelChannelB->width();
        h = ui->labelChannelB->height();
        ui->labelChannelB->setPixmap(QPixmap::fromImage(imageChannelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelChannelB->setStyleSheet("border: 0px solid");
    }else{
        QMessageBox::information(this, "Error","Por favor seleccione una imagen");
    }

}

// Evento encargado de seleccionar un canal
void Conversor::on_buttonSelectChannel_clicked()
{
    int w = ui->labelImageConvOrig->width();
    int h = ui->labelImageConvOrig->height();
    if (ui->comboChannel->currentIndex() == 0){ // Channel 1
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChannelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChannelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChannelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        ui->labelImageThresOrigi->setPixmap(QPixmap::fromImage(imageChannelR).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageThresOrigi->setStyleSheet("border: 0px solid");

        //        int max = *std::min_element(imageChannelRHisto.begin(), imageChannelRHisto.end());

        imageChoosed = imageChannelR;
        channel = RED;

    }else if (ui->comboChannel->currentIndex() == 1){ // Channel 2
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChannelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChannelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChannelG).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        //        int max = *std::min_element(imageChannelBHisto.begin(), imageChannelBHisto.end());
        imageChoosed = imageChannelG;
        channel = GREEN;

    }else if(ui->comboChannel->currentIndex() == 2){ // Chanel 3
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageChannelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageChannelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageChannelB).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        //        int max = *std::min_element(imageChannelGHisto.begin(), imageChannelGHisto.end());
        imageChoosed = imageChannelB;
        channel = BLUE;

    }else if(ui->comboChannel->currentIndex() == 3){ // Grey scale
        ui->labelImageConvOrig->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageConvOrig->setStyleSheet("border: 0px solid");

        ui->labelImageContOriginal->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageContOriginal->setStyleSheet("border: 0px solid");

        ui->labelImageEdgOrigi->setPixmap(QPixmap::fromImage(imageTrasformada).scaled(w, h, Qt::KeepAspectRatio));
        ui->labelImageEdgOrigi->setStyleSheet("border: 0px solid");

        //        int max = *std::min_element(imageTransformadaHisto.begin(), imageTransformadaHisto.end());
//        renderHistogram(ui->plotHistogram, imageTransformadaHisto, 10);
        channel = GREY;
    }
}
// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked(){
    imageConvolution = imageChoosed;
    int window = ui->spinConvolution->value();
    if(ui->comboConvolution->currentIndex() == 0){ // Average filter
        Convolution().averageFilter(&imageConvolution, window);

    }else if(ui->comboConvolution->currentIndex() == 1){ // Minimum filter
        Convolution().minimumFilter(&imageConvolution, window);

    }else if(ui->comboConvolution->currentIndex() == 2){ // Maximum filter
        Convolution().maximumFilter(&imageConvolution, window );

    }else if(ui->comboConvolution->currentIndex() == 3){ // Middle filter
        Convolution().middleFilter(&imageConvolution, window);

    }else if(ui->comboConvolution->currentIndex() == 4){ // Gaussian filter x3
        Convolution().gaussianFilterx3(&imageConvolution);

    }else if(ui->comboConvolution->currentIndex() == 5){ // Gaussian filter x5
        Convolution().gaussianFilterx5(&imageConvolution);

    }else if(ui->comboConvolution->currentIndex() == 6){ // Gaussian filter x7
        Convolution().gaussianFilterx7(&imageConvolution);

    }else if(ui->comboConvolution->currentIndex() == 7){ // Nagao filter
        Convolution().nagaoFilter(&imageConvolution);

    }

    int wx = ui->labelImageConvFilt->width();
    int hx = ui->labelImageConvFilt->height();
    ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageConvolution).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageConvFilt->setStyleSheet("border: 0px solid");

}


void Conversor::on_buttonApplyContrast_clicked(){
    imageContrast = imageChoosed;

    if(ui->comboContrast->currentIndex() == 0){ // Gamma correction
        double value = ui->spinGamma->value();
        Contrast().gammaCorrection(&imageContrast, channel, value);
        
    }else if(ui->comboContrast->currentIndex() == 1){ // Histogram equalization
        Contrast().histogramEqualization(&imageContrast, channel);

    }else if(ui->comboContrast->currentIndex() == 2){ // Contrast stretching
        Contrast().contrastStretching(&imageContrast, channel);

    }

    //    setupBarChartDemo(ui->plotHistogram);

    int wx = ui->labelImageContTrans->width();
    int hx = ui->labelImageContTrans->height();
    ui->labelImageContTrans->setPixmap(QPixmap::fromImage(imageContrast).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageContTrans->setStyleSheet("border: 0px solid");
}

void Conversor::on_buttonEdges_clicked()
{
    imageEdges = imageChoosed;
    int threshold = ui->spinThresholdEdges->value();

    if(ui->comboEdges->currentIndex() == 0){ // sobel
        bool autoThres = ui->checkAutoThreshold->isChecked();
        Edges().sobelOperator(&imageEdges, autoThres, threshold);
    }
    int wx = ui->labelImageEdgTrasf->width();
    int hx = ui->labelImageEdgTrasf->height();
    ui->labelImageEdgTrasf->setPixmap(QPixmap::fromImage(imageEdges).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageEdgTrasf->setStyleSheet("border: 0px solid");
}






void Conversor::on_bUseConv_clicked()
{
    imageChoosed = imageConvolution;
    resizeWindow();
}

void Conversor::on_bSaveconv_clicked()
{
    QVector<double> histogram(QVector<double>(256));

    for(int i = 0; i < imageChoosed.width(); i++){
        for(int j = 0; j < imageChoosed.height(); j++){
            histogram[QColor(imageChoosed.pixel(i, j)).red()]++;
        }
    }

    HistogramView *h = new HistogramView(histogram, 10);
    h->show();
}

void Conversor::on_bUseContrast_clicked()
{
    imageChoosed = imageContrast;
    resizeWindow();
}

void Conversor::on_bSaveContrast_clicked()
{
    QVector<double> histogram(QVector<double>(256));

    for(int i = 0; i < imageChoosed.width(); i++){
        for(int j = 0; j < imageChoosed.height(); j++){
            histogram[QColor(imageChoosed.pixel(i, j)).red()]++;
        }
    }

    HistogramView *h = new HistogramView(histogram, 10);
    h->show();
}

void Conversor::on_bUseEdges_clicked()
{
    imageChoosed = imageEdges;
    resizeWindow();
}

void Conversor::on_bSaveEdges_clicked()
{
    QVector<double> histogram(QVector<double>(256));

    for(int i = 0; i < imageChoosed.width(); i++){
        for(int j = 0; j < imageChoosed.height(); j++){
            histogram[QColor(imageChoosed.pixel(i, j)).red()]++;
        }
    }

    HistogramView *h = new HistogramView(histogram, 10);
    h->show();
}

void Conversor::on_bApplyGlobalThres_clicked()
{
    imageThres = imageChoosed;
    if(ui->comboGlobalThres->currentIndex() == 0){// Otsu Thresholding
        Threshold().otsuGlobalThreshold(&imageThres);
    }else if(ui->comboGlobalThres->currentIndex() == 1){ // Manual Thresholding
        Threshold().manualThreshold(&imageThres, ui->spinThreshold->value());
    }else if(ui->comboGlobalThres->currentIndex() == 2){ // Triangle Thresholding
        Threshold().triangleThreshold(&imageThres);
    }

    int wx = ui->labelImageThresTrans->width();
    int hx = ui->labelImageThresTrans->height();
    ui->labelImageThresTrans->setPixmap(QPixmap::fromImage(imageThres).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageThresTrans->setStyleSheet("border: 0px solid");

}

void Conversor::on_bUseThres_clicked()
{
    imageChoosed = imageThres;
    resizeWindow();
}

void Conversor::on_bSaveThres_clicked()
{
    QVector<double> histogram(QVector<double>(256));

    for(int i = 0; i < imageChoosed.width(); i++){
        for(int j = 0; j < imageChoosed.height(); j++){
            histogram[QColor(imageChoosed.pixel(i, j)).red()]++;
        }
    }

    HistogramView *h = new HistogramView(histogram, 10);
    h->show();
}

void Conversor::on_bApplyMorph_clicked()
{
     imageThres = imageChoosed;
     if(ui->comboMorph->currentIndex() == 0){ // Dilate Operator
         MorphologicalOperators().dilate(&imageThres);
     }else if(ui->comboMorph->currentIndex() == 1){ // Erosion Operator
        MorphologicalOperators().erosion(&imageThres);
     }

     int wx = ui->labelImageThresTrans->width();
     int hx = ui->labelImageThresTrans->height();
     ui->labelImageThresTrans->setPixmap(QPixmap::fromImage(imageThres).scaled(wx, hx, Qt::KeepAspectRatio));
     ui->labelImageThresTrans->setStyleSheet("border: 0px solid");
}

void Conversor::on_buttonSave_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/miguel/Imágenes/Retina/resultados/", "Image (*.png)");
    imageChoosed.save(file, "png");
}

void Conversor::on_bApplyLocalThres_clicked()
{
    imageThres = imageChoosed;
    int window = ui->spinLocalThres->value();
    if(ui->comboLocalThres->currentIndex() == 0){ // Mean Thresholding
        Threshold().meanLocalThreshold(&imageThres, window);
//        Threshold().otsuThreshold(&imageThres, channel);
    }else if(ui->comboLocalThres->currentIndex() == 1){ // Otsu Thresholding
        Threshold().otsuLocalThreshold(&imageThres, window);
//        Threshold().manualThreshold(&imageThres, ui->spinThreshold1->value(), ui->spinThreshold2->value());
    }

    int wx = ui->labelImageThresTrans->width();
    int hx = ui->labelImageThresTrans->height();
    ui->labelImageThresTrans->setPixmap(QPixmap::fromImage(imageThres).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageThresTrans->setStyleSheet("border: 0px solid");
}

void Conversor::on_bDeleteMask_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/miguel/Imágenes/Retina/DRIVE/test/mask", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){
        QImage image;
        image.load(filename);



        imageThres = imageChoosed;
        int x = imageThres.width();
        int y = imageThres.height();

        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                if(QColor(image.pixel(i,j)).red() == 0){
                    imageThres.setPixel(i, j, qRgb(0, 0, 0));
                }
            }
        }

        int wx = ui->labelImageThresTrans->width();
        int hx = ui->labelImageThresTrans->height();
        ui->labelImageThresTrans->setPixmap(QPixmap::fromImage(imageThres).scaled(wx, hx, Qt::KeepAspectRatio));
        ui->labelImageThresTrans->setStyleSheet("border: 0px solid");
    }

}

void Conversor::on_bErrorConv_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/miguel/Imágenes/Retina/DRIVE/test/1st_manual", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){
        QImage image;
        image.load(filename);
        Error().ConfusionMatix(&image, &imageConvolution);
    }
}

void Conversor::on_bError_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/miguel/Imágenes/Retina/DRIVE/test/1st_manual/", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){
        QImage image;
        image.load(filename);
        Error().ConfusionMatix(&image, &imageChoosed);
    }
}

void Conversor::on_bAuto_clicked()
{
//    ColorSpace().convertToRGB(&imageTrasformada, &imageChannelR, &imageChannelG, &imageChannelB);
//    imageChoosed = imageChannelG;
    Convolution().gaussianFilterx5(&imageChoosed);
//    Threshold().meanLocalThreshold(&imageChoosed, 3);
    Threshold().otsuLocalThreshold(&imageChoosed, 3);

    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/miguel/Imágenes/Retina/DRIVE/test/mask", "All Files (*.*);;Image (*.png)");

    if(filename != NULL){
        QImage image;
        image.load(filename);

        int x = imageChoosed.width();
        int y = imageChoosed.height();

        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                if(QColor(image.pixel(i,j)).red() == 0){
                    imageChoosed.setPixel(i, j, qRgb(0, 0, 0));
                }
            }
        }

    }

    Convolution().middleFilter(&imageChoosed, 3);
    resizeWindow();
}
