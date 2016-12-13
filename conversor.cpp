#include "conversor.h"
#include "ui_conversor.h"
#include "convolution.h"
#include "colorspace.h"
#include "contrast.h"

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
        imageChannelRHisto.append(0);
        imageChannelGHisto.append(0);
        imageChannelBHisto.append(0);
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

// Evento encargado de seleccionar un canal para la convolucion
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

//        int max = *std::min_element(imageChannelRHisto.begin(), imageChannelRHisto.end());

        renderHistogram(ui->plotHistogram, imageChannelRHisto, 10);
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
        renderHistogram(ui->plotHistogram, imageChannelBHisto, 10);
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
        renderHistogram(ui->plotHistogram, imageChannelGHisto, 10);
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
        renderHistogram(ui->plotHistogram, imageTransformadaHisto, 10);
        imageChoosed = imageTrasformada;
        channel = GREY;
    }
}
// Evento encargado de hacer la convolucion
void Conversor::on_buttonApplyConvolution_clicked(){
    // imageConvolution = imageChoosed;
    if(ui->comboConvolution->currentIndex() == 0){ // Average filter
        Convolution().averageFilter(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 1){ // Minimum filter
        Convolution().minimumFilter(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 2){ // Maximum filter
        Convolution().maximumFilter(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 3){ // Middle filter
        Convolution().middleFilter(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 4){ // Gaussian filter x3
        Convolution().gaussianFilterx3(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 5){ // Gaussian filter x5
        Convolution().gaussianFilterx5(&imageChoosed, channel);

    }else if(ui->comboConvolution->currentIndex() == 6){ // Nagao filter
        Convolution().nagaoFilter(&imageChoosed, channel);

    }

    int wx = ui->labelImageConvFilt->width();
    int hx = ui->labelImageConvFilt->height();
    ui->labelImageConvFilt->setPixmap(QPixmap::fromImage(imageChoosed).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageConvFilt->setStyleSheet("border: 0px solid");

}


void Conversor::on_buttonApplyContrast_clicked(){
    // imageContrast = imageChoosed;

    if(ui->comboContrast->currentIndex() == 0){ // Gamma correction
        Contrast().gammaCorrection(&imageChoosed, channel, 0.6);
        
    }else if(ui->comboContrast->currentIndex() == 1){ // Histogram equalization
        Contrast().histogramEqualization(&imageChoosed, channel);

    }else if(ui->comboContrast->currentIndex() == 2){ // Contrast stretching
        Contrast().contrastStretching(&imageChoosed, channel);

    }

//    setupBarChartDemo(ui->plotHistogram);

    int wx = ui->labelImageContTrans->width();
    int hx = ui->labelImageContTrans->height();
    ui->labelImageContTrans->setPixmap(QPixmap::fromImage(imageChoosed).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageContTrans->setStyleSheet("border: 0px solid");
}

void Conversor::on_buttonEdges_clicked()
{
    imageEdges = imageChoosed;
    int threshold = ui->spinThreshold->value();

    if(ui->comboEdges->currentIndex() == 0){ // sobel
        int kernel1[3][3] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};
        int kernel2[3][3] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}};
        int w = imageChoosed.width();
        int h = imageChoosed.height();
        int kernelMiddle = (sizeof(kernel1) / sizeof(*kernel1)) / 2;
        int kernelSize = sizeof(kernel1) / sizeof(*kernel1);


        for(int i = kernelMiddle; i < w - kernelMiddle; i++){
            for(int j = kernelMiddle; j < h - kernelMiddle; j++){
                double matriz1PixelR = 0;
                double matriz1PixelG = 0;
                double matriz1PixelB = 0;

                double matriz2PixelR = 0;
                double matriz2PixelG = 0;
                double matriz2PixelB = 0;

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

                int matrizPixelR = abs(matriz1PixelR) + abs(matriz2PixelR);
                int matrizPixelG = abs(matriz1PixelG) + abs(matriz2PixelG);
                int matrizPixelB = abs(matriz1PixelB) + abs(matriz2PixelB);

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

                imageEdges.setPixel(i, j, qRgb(matrizPixelG, matrizPixelG, matrizPixelG));
            }
        }
    }
    int wx = ui->labelImageEdgTrasf->width();
    int hx = ui->labelImageEdgTrasf->height();
    ui->labelImageEdgTrasf->setPixmap(QPixmap::fromImage(imageEdges).scaled(wx, hx, Qt::KeepAspectRatio));
    ui->labelImageEdgTrasf->setStyleSheet("border: 0px solid");
}


void Conversor::renderHistogram(QCustomPlot *customPlot, QVector<double> pixelData, int maxPixel)
{
    QString demoName = "Bar Chart Demo";
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *numPixels = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    numPixels->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    numPixels->setStackingGap(10);

    numPixels->setName("pixels");
    numPixels->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    numPixels->setBrush(QColor(0, 168, 140));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
//    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    for(int i = 0; i < 256; i++){
        ticks.append(i);
        labels.append(QString::number(i));
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(90);
    customPlot->xAxis->setSubTicks(false);
  //  customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 255);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(false);
  //  customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, maxPixel);
    customPlot->yAxis->setPadding(1.5); // a bit more space to the left border
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    numPixels->setData(ticks, pixelData);

    // setup legend:
    customPlot->legend->setVisible(false);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
//    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
//    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

