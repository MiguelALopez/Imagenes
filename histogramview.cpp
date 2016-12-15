#include "histogramview.h"
#include "ui_histogramview.h"

HistogramView::HistogramView(QVector<double> pixelData, int maxPixel):ui(new Ui::HistogramView){
    ui->setupUi(this);
    renderHistogram(ui->plotHistogram, pixelData, maxPixel);
}

HistogramView::HistogramView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistogramView)
{
    ui->setupUi(this);
}

HistogramView::~HistogramView()
{
    delete ui;
}


void HistogramView::renderHistogram(QCustomPlot *customPlot, QVector<double> pixelData, int maxPixel)
{
//    std::cout << "raffo" << std::endl;
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
